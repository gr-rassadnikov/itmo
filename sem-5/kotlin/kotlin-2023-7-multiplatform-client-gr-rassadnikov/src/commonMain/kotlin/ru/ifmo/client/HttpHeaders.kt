package ru.ifmo.client

import kotlin.jvm.JvmInline

@JvmInline
value class HttpHeaders(val value: Map<String, String> = mapOf())
