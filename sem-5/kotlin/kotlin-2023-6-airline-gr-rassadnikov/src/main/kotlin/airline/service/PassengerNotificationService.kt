package airline.service

import airline.api.Ticket
import kotlinx.datetime.Instant

interface PassengerNotificationService {
    suspend fun delayFlight(passengers: Map<String, Ticket>, actualDepartureTime: Instant)

    suspend fun cancelFlight(passengers: Map<String, Ticket>)

    suspend fun setCheckInNumber(passengers: Map<String, Ticket>, checkInNumber: String)

    suspend fun setGateNumber(passengers: Map<String, Ticket>, gateNumber: String)

    suspend fun run()
}
