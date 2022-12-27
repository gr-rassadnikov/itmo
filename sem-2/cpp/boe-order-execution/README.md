# BOE декодеры

## Декодирование сообщения OrderExecution
### Идея
Когда какой-то заказ исполняется на бирже, то есть обнаруживается встречный заказ и биржа регистрирует сделку, участник, отправивший
заказ, получает уведомление о свершившейся сделке - исполнение заказа, order execution.
Заказ может быть исполнен полностью или частично, по указанной в нём цене или по более лучшей.

Обычно информация о заказе хранится в системе участника и не требуется получать с биржи параметры исходного заказа.
Однако, возможна ситуация, когда по какой-то причине участник получает уведомление о сделке по неизвестному ему заказу - обычно это
свидетельствует об ошибке либо на стороне участника, либо биржи. В этом случае полезно понимать, на какой инструмент была
зарегистрирована сделка, поэтому полезно получать идентификацию инструмента, хоть её и можно извлечь из параметров исходного заказа.

Особенность протокола BOE: в сообщении, отправляемом для установления сессии (LoginRequest), для каждого типа входящего сообщения
участник указывает, какие опциональные поля он желает получать. В рамках установленной сессии биржа не включает в сообщения к
участнику те опциональные поля, которые не были указаны в LoginRequest.

Например, для сообщения OrderAcknowledgment есть 11 групп опциональных полей, соответственно, нужно перечислить 11 байтов битовых
масок. Если требуется получать только поля OrigClOrdID и SecondaryOrderID, то нужно указать маски 1-4 пустыми (нулевые значения),
маску 5 со значением 1, маску 6 со значением 1, а маски 7-11 - можно не указывать (в качестве числа битовых масок в LoginRequest
при этом нужно указать число посылаемых масок, а не число возможных масок).
Тогда декодер сообщения OrderAcknowledgment может рассчитывать на то, что в сообщении будет ровно 2 опциональных поля (указанные
выше). Однако, при этом во входящем сообщении будут присутствовать все битовые маски и декодер должен уметь обрабатывать их
произвольное количество.
При этом, "заказанное" поле отправляется в сообщении с биржи всегда, даже если оно пустое. Пустое значение поля кодируется
заполнением всех байтов поля нулями.

### Задание
Требуется реализовать декодер для сообщения OrderExecution (см. [protocol specifications](doc/BATS_Europe_BOE2_Specification.pdf)) имеющий следующий интерфейс:
```cpp
enum class ResponseType {
    OrderExecution,
    OrderRestatement
};

std::vector<unsigned char> request_optional_fields_for_message(ResponseType);

enum class LiquidityIndicator {
    Added,
    Removed
};

struct ExecutionDetails
{
    std::string cl_ord_id;
    std::string exec_id;
    double filled_volume;
    double active_volume;
    double price;
    LiquidityIndicator liquidity_indicator;
    std::string symbol;
    std::string last_mkt;
    std::string fee_code;
};

ExecutionDetails decode_order_execution(const std::vector<unsigned char> & message)
{
    ExecutionDetails exec_details;
    // fill exec_details fields
    //   exec_details.cl_ord_id.assign(char_ptr, length);
    // or
    //   exec_details.cl_ord_id = std::string{char_ptr, length};
    // ...
    //   exec_details.filled_volume = x;
    // ...
    return exec_details;
}
```

Чтобы получить указатель на `char`, требуемый для присваивания в строки, из вектора `unsigned char`, можно:
```cpp
const char * str = reinterpret_cast<const char *>(&message[n]);
```
где `n` - индекс первого символа строки внутри сообщения.

Обратите внимание, что метод `std::string::assign` или конструктор `std::string(consr char *, std::size_t length)` не проверяют наличие нулевых символов в
строке. Поэтому, если скопировать в объект `std::string` массив символов, включающий нулевые символы в конце, то длина строки будет не соответствовать
логической длине - количеству ненулевых символов.
Например, в сообщении закодирована строка в поле, по спецификации имеющему размер 10 символов. Однако, сама строка состоит из 5 символов. Оставшиеся 5
байт поля будут заполнены нулями.
Если выполнить такой код:
```cpp
std::string str;
str.assign(reinterpret_cast<const char *>(&message[n], 10)); // contains "ITMO!\0\0\0\0\0"
std::cout << str.size() << std::endl; // prints out 10
std::cout << str << std::endl; // prints out "ITMO!"
```
Поэтому нужно проверить степень заполненности поля, чтобы скопировать в выходную строку только ненулевые символы.

Требуемые поля:
* ClOrdID -> cl_ord_id
* ExecID -> exec_id число нужно закодировать в строку в кодировке [base36](https://en.wikipedia.org/wiki/Base36)
* LastShares -> filled_volume
* LastPx -> price
* LeavesQty -> active_volume
* BaseLiquidityIndicator -> liquidity_indicator : 'A' -> Added, 'R' -> Removed, остальные значения игнорировать
* Symbol -> symbol
* LastMkt -> last_mkt
* FeeCode -> fee_code

## Декодирование сообщения OrderRestated
### Идея
Иногда активный заказ на бирже может меняться по инициативе самой биржи. Одним из таких примеров является обновление обновление Iceberg заказа (т.е. заказа,
у которого публично видимый объём меньше реального объёма, соответственно, когда весь видимый объём оказывается сторгован, он возобновляется из реального
без потери приоритета заказа).
Для уведомления о таком событии, биржа посылает участнику сообщение OrderRestated, содержащее актуальные параметры заказа.

Подробности про опциональные поля описаны в разделе про OrderExecuted.

### Задание
Требуется реализовать декодер для сообщения OrderRestated (см. [protocol specifications](doc/BATS_Europe_BOE2_Specification.pdf)) имеющий следующий интерфейс:
```cpp
enum class RestatementReason {
    Reroute,
    LockedInCross,
    Wash,
    Reload,
    LiquidityUpdated,
    Unknown
};

struct RestatementDetails
{
    std::string cl_ord_id;
    RestatementReason reason;
    double active_volume;
    std::string secondary_order_id;
};

RestatementDetails decode_order_restatement(const std::vector<unsigned char> & message)
{
    RestatementDetails restatement_details;
    // ...
    return restatement_details;
}
```
Обратите внимание, что `secondary_order_id` является строкой, получаемой в результате base36 кодирования 8-байтного числа, приходящего в качестве `SecondaryOrderID`
в протоколе.

## Общие соображения
Не обязательно использовать подход, продемонстрированный в примере про NewOrder, однако нужно предусмотреть возможность лёгкого
изменения списка интересующих полей.

Функция `request_optional_fields_for_message` должна возвращать массив байтов, представляющих собой битовые маски опциональных
полей, которые используются для указанного типа входящего сообщения. При этом в результирующий массив нужно поместить все маски вплоть до последней ненулевой.
