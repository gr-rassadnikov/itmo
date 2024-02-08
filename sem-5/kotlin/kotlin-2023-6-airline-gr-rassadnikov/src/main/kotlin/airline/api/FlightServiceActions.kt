package airline.api

import kotlinx.datetime.Instant

sealed class FlightServiceAction
class ScheduleFlightAMSAction(val flightId: String, val departureTime: Instant, val plane: Plane) :
    FlightServiceAction()

class DelayFlightAMSAction(val flightId: String, val departureTime: Instant, val actualDepartureTime: Instant) :
    FlightServiceAction()

class CancelFlightAMSAction(val flightId: String, val departureTime: Instant) : FlightServiceAction()
class SetCheckFlightAMSAction(val flightId: String, val departureTime: Instant, val checkInNumber: String) :
    FlightServiceAction()

class SetGateFlightAMSAction(val flightId: String, val departureTime: Instant, val gateNumber: String) :
    FlightServiceAction()

class ByTicketFlightBSAction(
    val flightId: String,
    val departureTime: Instant,
    val seatNo: String,
    val passengerId: String,
    val passengerName: String,
    val passengerEmail: String,
) : FlightServiceAction()
