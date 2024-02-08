# Задание 7. Multiplatform HTTP Client

Вам требуется реализовать мультиплатформенную обёртку над платформенными http клиентами.

В `commonMain`, в пакете `ru.ifmo.client` предоставлен интерфейс HTTP клиента.

_Rem. Менять каким либо образом эти файлы нельзя._

Необходимо поддержать следующие платформы: JVM, JS (NodeJS, Browser), Native.

Платформенные клиенты:

* JVM - [Java HTTP Client](https://openjdk.org/groups/net/httpclient/intro.html)
* Native - [libcurl](https://curl.se/libcurl/)
* Browser JS - [Fetch API](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API)
* Node JS - [node-fetch](https://www.npmjs.com/package/node-fetch)

Все необходимые зависимости уже настроены.

Hint: При решении задания советую изучить то, как реализованы подобные обёртки
в [Ktor Client](https://github.com/ktorio/ktor/tree/main/ktor-client)

## Зависимости

Для решения задания необходимо установить на компьютер libcurl. Рекомендуемые способы:
* Windows - библиотека скомпилирована и есть в репозитории
* Mac OS - `brew install curl`
* Linux - `apt-get install libcurl4-gnutls-dev` или аналогичное для вашего дистрибутива

Для запуска тестов вам необходимо установить Chrome Browser.
