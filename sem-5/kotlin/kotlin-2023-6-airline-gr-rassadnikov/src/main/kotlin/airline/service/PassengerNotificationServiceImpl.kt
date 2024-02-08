package airline.service

import airline.api.*
import airline.util.EmailTextBot
import kotlinx.coroutines.channels.Channel
import kotlinx.datetime.Instant

class PassengerNotificationServiceImpl(
    private val bufferedEmailService: BufferedEmailService,
) :
    PassengerNotificationService {
        private val passengerNotificationChannel: Channel<PassengerNotificationServiceAction> = Channel()
        override suspend fun delayFlight(passengers: Map<String, Ticket>, actualDepartureTime: Instant) {
            passengerNotificationChannel.send(DelayFlightPNSAction(passengers, actualDepartureTime))
        }

        override suspend fun cancelFlight(passengers: Map<String, Ticket>) {
            passengerNotificationChannel.send(CancelFlightPNSAction(passengers))
        }

        override suspend fun setCheckInNumber(passengers: Map<String, Ticket>, checkInNumber: String) {
            passengerNotificationChannel.send(SetCheckInPNSAction(passengers, checkInNumber))
        }

        override suspend fun setGateNumber(passengers: Map<String, Ticket>, gateNumber: String) {
            passengerNotificationChannel.send(SetGatePNSAction(passengers, gateNumber))
        }

        override suspend fun run() {
            while (true) {
                when (val data = passengerNotificationChannel.receive()) {
                    is DelayFlightPNSAction -> {
                        for (passenger in data.passengers) {
                            val email = passenger.value.passengerEmail
                            bufferedEmailService.send(
                                email,
                                EmailTextBot.delayFlight(passenger.value, data.actualDepartureTime),
                            )
                        }
                    }

                    is CancelFlightPNSAction -> {
                        for (passenger in data.passengers) {
                            val email = passenger.value.passengerEmail
                            bufferedEmailService.send(
                                email,
                                EmailTextBot.cancelFlight(passenger.value),
                            )
                        }
                    }

                    is SetCheckInPNSAction -> {
                        for (passenger in data.passengers) {
                            val email = passenger.value.passengerEmail
                            bufferedEmailService.send(
                                email,
                                EmailTextBot.setCheckIntNumber(passenger.value, data.checkInNumber),
                            )
                        }
                    }

                    is SetGatePNSAction -> {
                        for (passenger in data.passengers) {
                            val email = passenger.value.passengerEmail
                            bufferedEmailService.send(
                                email,
                                EmailTextBot.setGateNumber(passenger.value, data.gateNumber),
                            )
                        }
                    }
                }
            }
        }
    }
