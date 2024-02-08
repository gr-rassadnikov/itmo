package airline

import airline.api.*
import airline.service.*
import airline.util.EmailTextBot
import kotlin.time.Duration.Companion.minutes
import kotlinx.coroutines.*
import kotlinx.coroutines.flow.*
import kotlinx.datetime.Clock
import kotlinx.datetime.Instant

data class EmailData(val to: String, val text: String)

class AirlineApplication(private val config: AirlineConfig, emailService: EmailService) {
    private val updateFlightsFlow = MutableSharedFlow<FlightServiceAction>()
    private var flights = MutableStateFlow<List<Flight>>(emptyList())

    val bookingService = BookingServicesImpl(updateFlightsFlow, flights) {
        flights.value
            .filter { flight ->
                flight.departureTime - config.ticketSaleEndTime > currentTime()
            }
            .map { flight ->
                flight.toFlightInfo()
            }
    }

    val managementService: AirlineManagementService = AirlineManagementServiceImpl(updateFlightsFlow)
    val airportAudioAlerts: Flow<AudioAlerts> = flow {
        while (true) {
            delay(config.audioAlertsInterval)
            for (flight in flights.value) {
                if (flight.checkInNumber != null) {
                    val registrationOpeningTime = flight.actualDepartureTime - config.registrationOpeningTime
                    if (checkOpenRulesForAudioAlert(registrationOpeningTime)) {
                        emit(AudioAlerts.RegistrationOpen(flight.flightId, flight.checkInNumber))
                    }

                    val registrationClosingTime = flight.actualDepartureTime - config.registrationClosingTime
                    if (checkCloseRulesForAudioAlert(registrationClosingTime)) {
                        emit(AudioAlerts.RegistrationClosing(flight.flightId, flight.checkInNumber))
                    }
                }
                if (flight.gateNumber != null) {
                    val boardingOpeningTime = flight.actualDepartureTime - config.boardingOpeningTime
                    if (checkOpenRulesForAudioAlert(boardingOpeningTime)) {
                        emit(AudioAlerts.BoardingOpened(flight.flightId, flight.gateNumber))
                    }

                    val boardingClosingTime = flight.actualDepartureTime - config.boardingClosingTime
                    if (checkCloseRulesForAudioAlert(boardingClosingTime)) {
                        emit(AudioAlerts.BoardingClosing(flight.flightId, flight.gateNumber))
                    }
                }
            }
        }
    }

    private val bufferedEmailService = BufferedEmailService(emailService)
    private val passengerNotificationService: PassengerNotificationService =
        PassengerNotificationServiceImpl(bufferedEmailService)

    @OptIn(FlowPreview::class)
    fun airportInformationDisplay(coroutineScope: CoroutineScope): StateFlow<InformationDisplay> = runBlocking {
        flights
            .sample(config.displayUpdateInterval)
            .map { list: List<Flight> ->
                InformationDisplay(
                    list.map { flight ->
                        flight.toFlightInfo()
                    },
                )
            }.stateIn(coroutineScope)
    }

    suspend fun run() {
        coroutineScope {
            launch {
                passengerNotificationService.run()
            }
            launch {
                bufferedEmailService.run()
            }
            launch {
                observeUpdatesFlow()
            }
        }
    }

    private suspend fun observeUpdatesFlow() {
        updateFlightsFlow.collect {
            val list = flights.value.toMutableList()
            when (it) {
                is ScheduleFlightAMSAction -> {
                    list.add(Flight(it.flightId, it.departureTime, plane = it.plane))
                }

                is DelayFlightAMSAction -> {
                    val flight = findInList(list, it.flightId, it.departureTime)
                    list.remove(flight)
                    val copy = flight?.copy(actualDepartureTime = it.actualDepartureTime)
                    if (copy != null) {
                        list.add(copy)
                        passengerNotificationService.delayFlight(copy.tickers, it.actualDepartureTime)
                    }
                }

                is CancelFlightAMSAction -> {
                    val flight = findInList(list, it.flightId, it.departureTime)
                    list.remove(flight)
                    val copy = flight?.copy(isCancelled = true)
                    if (copy != null) {
                        list.add(copy)
                        passengerNotificationService.cancelFlight(copy.tickers)
                    }
                }

                is SetCheckFlightAMSAction -> {
                    val flight = findInList(list, it.flightId, it.departureTime)
                    list.remove(flight)
                    val copy = flight?.copy(checkInNumber = it.checkInNumber)
                    if (copy != null) {
                        list.add(copy)
                        passengerNotificationService.setCheckInNumber(copy.tickers, it.checkInNumber)
                    }
                }

                is SetGateFlightAMSAction -> {
                    val flight = findInList(list, it.flightId, it.departureTime)
                    list.remove(flight)
                    val copy = flight?.copy(gateNumber = it.gateNumber)
                    if (copy != null) {
                        list.add(copy)
                        passengerNotificationService.setGateNumber(copy.tickers, it.gateNumber)
                    }
                }

                is ByTicketFlightBSAction -> {
                    val flight = findInList(list, it.flightId, it.departureTime)
                    val text: String
                    if (flight != null && !flight.isCancelled && flight.plane.seats.contains(it.seatNo) &&
                        flight.departureTime - config.ticketSaleEndTime > currentTime()
                    ) {
                        val plane = flight.plane
                        val seats = plane.seats
                        val copySeats: MutableSet<String> = seats.toMutableSet()
                        copySeats.remove(it.seatNo)
                        list.remove(flight)

                        val flightCopy = flight.copy(plane = Plane(plane.planeId, copySeats))
                        flightCopy.tickers[it.passengerId] = Ticket(
                            it.flightId,
                            it.departureTime,
                            it.seatNo,
                            it.passengerId,
                            it.passengerName,
                            it.passengerEmail,
                        )
                        list.add(flightCopy)
                        text = EmailTextBot.byTicketSuccess(
                            it.flightId,
                            it.departureTime,
                            it.seatNo,
                            it.passengerName,
                        )
                    } else {
                        text = EmailTextBot.byTicketWithError(
                            it.flightId,
                            it.departureTime,
                            it.seatNo,
                            it.passengerName,
                        )
                    }
                    bufferedEmailService.send(
                        it.passengerEmail,
                        text,
                    )
                }
            }
            flights.emit(ArrayList(list))
        }
    }

    private fun checkOpenRulesForAudioAlert(eventTime: Instant): Boolean {
        val current = currentTime()
        return eventTime <= current && current <= eventTime + 3.minutes
    }

    private fun checkCloseRulesForAudioAlert(eventTime: Instant): Boolean {
        val current = currentTime()
        return eventTime - 3.minutes <= current && current <= eventTime
    }

    private fun currentTime() = Clock.System.now()

    private fun findInList(list: List<Flight>, flightId: String, departureTime: Instant): Flight? {
        return list.firstOrNull { it.flightId == flightId && it.departureTime == departureTime }
    }
}
