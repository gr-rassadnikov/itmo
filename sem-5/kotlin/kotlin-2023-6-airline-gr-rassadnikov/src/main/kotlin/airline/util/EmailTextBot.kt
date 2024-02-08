package airline.util

import airline.api.Ticket
import kotlinx.datetime.Instant

class EmailTextBot {
    companion object {
        fun byTicketSuccess(
            flightId: String,
            departureTime: Instant,
            seatNo: String,
            passengerName: String,
        ): String =
            "Dear $passengerName, you successfully bought ticket on the plane.\n" +
                "Flight id: $flightId\n" +
                "Departure Time: $departureTime\n" +
                "Seat number: $seatNo"

        fun byTicketWithError(
            flightId: String,
            departureTime: Instant,
            seatNo: String,
            passengerName: String,
        ): String =
            "<Failed to buy. Dear $passengerName, sorry you can't buy ticket at plane.\n" +
                "Flight id: $flightId\n" +
                "Departure Time: $departureTime\n" +
                "Seat number: $seatNo"

        fun delayFlight(ticket: Ticket, actualDepartureTime: Instant): String =
            "Dear ${ticket.passengerName}, sorry your plane with Flight id: ${ticket.flightId} was delayed to" +
                "$actualDepartureTime"

        fun cancelFlight(ticket: Ticket): String =
            "Dear ${ticket.passengerName}, sorry your plane with Flight id: ${ticket.flightId} was cancelled"

        fun setCheckIntNumber(ticket: Ticket, checkInNumber: String): String =
            "Dear ${ticket.passengerName}, your number of checkIn on board ${ticket.flightId} is $checkInNumber"

        fun setGateNumber(ticket: Ticket, gateNumber: String): String =
            "Dear ${ticket.passengerName}, your number of gate on board ${ticket.flightId} is $gateNumber"
    }
}
