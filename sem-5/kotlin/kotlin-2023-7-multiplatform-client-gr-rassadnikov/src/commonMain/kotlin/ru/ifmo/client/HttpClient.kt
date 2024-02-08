package ru.ifmo.client

@OptIn(ExperimentalStdlibApi::class)
interface HttpClient : AutoCloseable {
    suspend fun request(method: HttpMethod, request: HttpRequest): HttpResponse
}

expect fun HttpClient(): HttpClient