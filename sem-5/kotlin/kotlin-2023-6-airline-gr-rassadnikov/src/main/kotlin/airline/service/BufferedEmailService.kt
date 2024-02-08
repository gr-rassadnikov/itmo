package airline.service

import airline.EmailData
import kotlinx.coroutines.channels.Channel

class BufferedEmailService(private val emailService: EmailService) : EmailService {
    private val bufferedEmailChannel: Channel<EmailData> = Channel()

    override suspend fun send(to: String, text: String) {
        bufferedEmailChannel.send(EmailData(to, text))
    }

    suspend fun run() {
        while (true) {
            val data = bufferedEmailChannel.receive()
            emailService.send(data.to, data.text)
        }
    }
}
