### Лабораторная работа №2. Ручное построение нисходящих синтаксических анализаторов

### Вариант 12. Оператор for в Си

Примитивная версия оператора `for` в `Си`. Оператор начинается ключевым словом `for`, далее в скобках три параметра,
разделенные точкой с запятой. Первый параметр: имя типа, имя переменной, начальное значение. Второй параметр: имя
переменной, знак сравнения, число. Третий параметр: имя переменной, операция инкремента/декремента.

Используйте один терминал для всех имен переменных и имен типов. Используйте один терминал для ключевого
слова `for (не несколько ‘f’, ‘o’, ‘r’)`. Используйте один терминал для оператора `++` (не два плюса).

Пример: `for (int x = 0; x < 10; x++)`

## Токенизация

Проведем разбеения исходной строчки на токены. Для этого будем использовать enums из kotlin и написанный класс
`LexicalAnalyzer`. Если строка состоит из корректных токенов - то разъбиение завершится успешно, если встречается
неизвестный токен, то будет выбрашена ошибка `ParseException`.

| Токен       | Терминал    |
|-------------|-------------|
| `FOR`       | `for`       |
| `LE`        | `<=`        |
| `LT`        | `<`         |
| `GE`        | `>=`        |
| `GT`        | `>`         |
| `EQ`        | `==`        |
| `NEQ`       | `!=`        |
| `INC`       | `++`        |
| `DEC`       | `--`        |
| `LPAREN`    | `(`         |
| `RPAREN`    | `)`         |
| `VAR`       | `type/name` |
| `ASSIGN`    | `=`         |
| `SEPARATOR` | `;`         |
| `END`       | `$`         |
| `NUMBER`    | `number`    |

За окончание - будем считать символ `$` - который добавится в строку в момент, когда строка закончится.
(можно и добавить символ окончание самостоятельно - тогда все эл-ты после симвоа конца будут проигнорированы)

## Parser и Терминальные состояния

Построим таблицу выводов

| P (вывод)                            |                                                             |
|--------------------------------------|-------------------------------------------------------------|
| `S -> for (T T = N I; T OP N; T NC)` | Базовая конструкция цикла `for` в `C`                       |
| `N -> 'number'`                      | Число - удовлятворяет корректному базовому типу числа в `C` |
| `T -> 'indeficator'`                 | Корректное имя типа или название переменной                 |
| `OP -> <, <=, >, >=, ==, !=`         | Один из операторов для сравнения чисел                      |
| `NC -> ++, --`                       | Префиксный инкремент/декримент                              |
| `I -> ,I`                            |                                                             |

Видим, что грамматика не имеет левой рекурсии и правого ветвленения, что означает, что наша грамматика является
`LL-1 грамматикой`. Значит уже можно строить `Parser`, однако в задании простя построить мн-ва
`First, Follow` - построим их, однако в этов варианте они не несут инфомативный смысл.

| Нетерминал | First                            | Follow |
|------------|----------------------------------|--------|
| `S`        | `for`                            | `$`    |
| `N`        | `'number'`                       | `$`    |
| `T`        | `'indeficator'`                  | `$`    |
| `OP`       | `<`, `<=`, `>`, `>=`, `==`, `!=` | `$`    |
| `NC`       | `++`, `--`                       | `$`    |

Решение покроем тестами.
Отдельно будем тестировать разбиение на токены и Парсинг.

