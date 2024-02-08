package chatbot.dsl

import chatbot.api.*

class Behaviour<C : ChatContext?>(private val chatBot: ConfigBuilder) {

    class PredicateAction(
        val predicate: (ChatContext?) -> Boolean,
        val action: (Message) -> Boolean,
    )

    var list: MutableList<PredicateAction> = mutableListOf()

    fun run(message: Message) {
        val manager = chatBot.chatContextsManager
        val chatId = message.chatId
        val context = manager?.getContext(chatId)
        for (worker in list) {
            if (worker.predicate(context)) {
                if (worker.action(message)) break
            }
        }
    }

    fun onCommand(command: String, messageProcessor: MessageProcessor<C>) {
        list.add(
            PredicateAction(
                { _: ChatContext? -> true },
                { message: Message -> commandCondition(message, command, messageProcessor) },
            ),
        )
    }

    fun onMessage(predicate: ChatBot.(Message) -> Boolean, messageProcessor: MessageProcessor<C>) {
        list.add(
            PredicateAction(
                { _: ChatContext? -> true },
                { message: Message ->
                    predicateCondition(
                        message,
                        predicate,
                        messageProcessor,
                    )
                },
            ),
        )
    }

    fun onMessagePrefix(prefix: String, messageProcessor: MessageProcessor<C>) {
        list.add(
            PredicateAction(
                { _: ChatContext? -> true },
                { message: Message -> prefixCondition(message, prefix, messageProcessor) },
            ),
        )
    }

    fun onMessageContains(text: String, messageProcessor: MessageProcessor<C>) {
        list.add(
            PredicateAction(
                { _: ChatContext? -> true },
                { message: Message -> textCondition(message, text, messageProcessor) },
            ),
        )
    }

    fun onMessage(messageTextExactly: String, messageProcessor: MessageProcessor<C>) {
        list.add(
            PredicateAction(
                { _: ChatContext? -> true },
                { message: Message ->
                    messageTextExactlyCondition(
                        message,
                        messageTextExactly,
                        messageProcessor,
                    )
                },
            ),
        )
    }

    fun onMessage(messageProcessor: MessageProcessor<C>) {
        list.add(
            PredicateAction(
                { _: ChatContext? -> true },
                { message: Message -> messageCondition(message, messageProcessor) },
            ),
        )
    }

    @Deprecated("behaviour can't be call form this context\"", level = DeprecationLevel.ERROR)
    fun behaviour(
        @Suppress("UNUSED_PARAMETER") ignored: Behaviour<ChatContext?>.() -> Unit,
    ) {
    }

    @Suppress("UNCHECKED_CAST")
    private fun getProcessor(message: Message): MessageProcessorContext<C> {
        val manager = chatBot.chatContextsManager
        val chatId = message.chatId
        val context = manager?.getContext(chatId)

        val setContext: (ChatContext?) -> Unit = { cnt ->
            chatBot.chatContextsManager?.setContext(chatId, cnt)
        }
        return MessageProcessorContext(message, chatBot.client, context as C, setContext)
    }

    private fun commandCondition(message: Message, command: String, messageProcessor: MessageProcessor<C>): Boolean {
        if (message.text.startsWith("/$command")) {
            messageProcessor.invoke(getProcessor(message))
            return true
        }
        return false
    }

    private fun predicateCondition(
        message: Message,
        predicate: ChatBot.(Message) -> Boolean,
        messageProcessor: MessageProcessor<C>,
    ): Boolean {
        if (predicate.invoke(chatBot, message)) {
            messageProcessor.invoke(getProcessor(message))
            return true
        }
        return false
    }

    private fun prefixCondition(message: Message, prefix: String, messageProcessor: MessageProcessor<C>): Boolean {
        if (message.text.startsWith(prefix)) {
            messageProcessor.invoke(getProcessor(message))
            return true
        }
        return false
    }

    private fun textCondition(message: Message, text: String, messageProcessor: MessageProcessor<C>): Boolean {
        if (message.text.contains(text)) {
            messageProcessor.invoke(getProcessor(message))
            return true
        }
        return false
    }

    private fun messageTextExactlyCondition(
        message: Message,
        messageTextExactly: String,
        messageProcessor: MessageProcessor<C>,
    ): Boolean {
        if (message.text == messageTextExactly) {
            messageProcessor.invoke(getProcessor(message))
            return true
        }
        return false
    }

    private fun messageCondition(message: Message, messageProcessor: MessageProcessor<C>): Boolean {
        messageProcessor.invoke(getProcessor(message))
        return true
    }
}
