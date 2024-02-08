package chatbot.dsl

import chatbot.api.*

@DslMarker
annotation class DSL

typealias MessageProcessor<C> = MessageProcessorContext<C>.() -> Unit

@DSL
class MessageProcessorContext<C : ChatContext?>(
    val message: Message,
    val client: Client,
    val context: C,
    val setContext: (c: ChatContext?) -> Unit,
) {
    @Deprecated("onMessage can't be call form this context", level = DeprecationLevel.ERROR)
    fun onMessage(
        @Suppress("UNUSED_PARAMETER") ignored: MessageProcessor<C>,
    ) {
    }

    private val keyboardProcess = KeyboardProcess()
    fun sendMessage(chatId: ChatId, configure: (KeyboardProcess) -> Unit) {
        configure(keyboardProcess)
        if (
            (
                keyboardProcess.keyboard.isNotEmpty() && keyboardProcess.keyboard.last().isNotEmpty()
                ) || replyTo != null || keyboardProcess.keyboardState == Keyboard.Remove
        ) {
            client.sendMessage(chatId, text, keyboardProcess.keyboardState, replyTo)
        }
    }

    fun withKeyboard(configure: KeyboardProcess.() -> Unit) {
        configure(keyboardProcess)
        keyboardProcess.keyboardState = Keyboard.Markup(keyboardProcess.oneTime, keyboardProcess.keyboard)
    }

    fun removeKeyboard() {
        keyboardProcess.keyboardState = Keyboard.Remove
        text = ""
        keyboardProcess.oneTime = false
        replyTo = null
    }

    var text: String = ""
    var replyTo: MessageId? = null

    class KeyboardProcess {
        var oneTime = false
        var keyboard: MutableList<MutableList<Keyboard.Button>> = mutableListOf()

        var keyboardState: Keyboard? = null

        fun row(configure: KeyboardProcess.() -> Unit) {
            keyboard.add(mutableListOf())
            configure(this)
        }

        fun button(text: String) {
            addToList(text)
        }

        operator fun String.unaryMinus() {
            addToList(this)
        }

        private fun addToList(str: String) {
            keyboard.last().add(Keyboard.Button(str))
        }
    }
}

@DSL
class ConfigBuilder(val client: Client) : ChatBot {

    var behaviour = Behaviour<ChatContext?>(this)
    var chatContextsManager: ChatContextsManager? = null

    override fun processMessages(message: Message) {
        behaviour.run(message)
    }

    override var logLevel = LogLevel.ERROR
        private set

    fun use(logLevel: LogLevel) {
        this.logLevel = logLevel
    }

    operator fun LogLevel.unaryPlus() = use(this)

    fun use(chatContextsManager: ChatContextsManager) {
        this.chatContextsManager = chatContextsManager
    }

    fun behaviour(configure: Behaviour<ChatContext?>.() -> Unit) {
        configure(behaviour)
    }

    inline infix fun <reified C : ChatContext?> C.into(configure: Behaviour<C>.() -> Unit) {
        intoImpl<C>(configure)
    }

    inline fun <reified C : ChatContext> into(configure: Behaviour<C>.() -> Unit) {
        intoImpl<C>(configure)
    }

    inline fun <reified C : ChatContext?> intoImpl(configure: Behaviour<C>.() -> Unit) {
        val behaviourForContext = Behaviour<C>(this)
        configure(behaviourForContext)
        val predicate: (ChatContext?) -> Boolean = { context ->
            if (context != null) {
                when (C::class) {
                    context::class -> true
                    else -> false
                }
            } else {
                false
            }
        }
        for (e in behaviourForContext.list) {
            behaviour.list.add(Behaviour.PredicateAction(predicate, e.action))
        }
    }
}

fun chatBot(client: Client, configure: ConfigBuilder.() -> Unit): ChatBot {
    val builder = ConfigBuilder(client)
    configure(builder)
    return builder
}
