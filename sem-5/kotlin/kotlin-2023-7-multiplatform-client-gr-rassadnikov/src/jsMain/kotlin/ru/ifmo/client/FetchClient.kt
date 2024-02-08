package ru.ifmo.client

import org.w3c.fetch.RequestInit

// TODO: Implement a wrapper around fetch
//
// Hint: Use org.w3c.fetch.RequestInit
// Hint: Use org.khronos.webgl.Int8Array

private enum class Platform { Node, Browser }

private val platform: Platform
    get() {
        val hasNodeApi = js(
            """
            (typeof process !== 'undefined' 
                && process.versions != null 
                && process.versions.node != null) ||
            (typeof window !== 'undefined' 
                && typeof window.process !== 'undefined' 
                && window.process.versions != null 
                && window.process.versions.node != null)
            """
        ) as Boolean
        return if (hasNodeApi) Platform.Node else Platform.Browser
    }

private val nodeFetch: dynamic
    get() = js("eval('require')('node-fetch')")

private fun RequestInit.asNodeOptions(): dynamic =
    js("Object").assign(js("Object").create(null), this)
