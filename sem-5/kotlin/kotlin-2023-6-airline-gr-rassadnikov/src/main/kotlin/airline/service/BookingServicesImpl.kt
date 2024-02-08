package airline.service

import airline.api.*
import kotlinx.coroutines.flow.MutableSharedFlow
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.datetime.Instant

class BookingServicesImpl(
    private val updateFlightsFlow: MutableSharedFlow<FlightServiceAction>,
    private val flights: MutableStateFlow<List<Flight>>,
    private val callbackGetList: () -> List<FlightInfo>,
) : BookingServices {

    override val flightSchedule: List<FlightInfo>
        get() = callbackGetList()

    override fun freeSeats(flightId: String, departureTime: Instant): Set<String> {
        val flight = findInList(flights.value, flightId, departureTime)
        return flight?.plane?.seats ?: emptySet()
    }

    override suspend fun buyTicket(
        flightId: String,
        departureTime: Instant,
        seatNo: String,
        passengerId: String,
        passengerName: String,
        passengerEmail: String,
    ) {
        updateFlightsFlow.emit(
            ByTicketFlightBSAction(
                flightId,
                departureTime,
                seatNo,
                passengerId,
                passengerName,
                passengerEmail,
            ),
        )
    }

    private fun findInList(list: List<Flight>, flightId: String, departureTime: Instant): Flight? {
        return list.firstOrNull { it.flightId == flightId && it.departureTime == departureTime }
    }
}
