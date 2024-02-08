package airline.api

import kotlinx.datetime.Instant

sealed class PassengerNotificationServiceAction
class DelayFlightPNSAction(val passengers: Map<String, Ticket>, val actualDepartureTime: Instant) :
    PassengerNotificationServiceAction()

class CancelFlightPNSAction(val passengers: Map<String, Ticket>) : PassengerNotificationServiceAction()
class SetCheckInPNSAction(
    val passengers: Map<String, Ticket>,
    val checkInNumber: String,
) : PassengerNotificationServiceAction()
class SetGatePNSAction(
    val passengers: Map<String, Ticket>,
    val gateNumber: String,
) : PassengerNotificationServiceAction()
