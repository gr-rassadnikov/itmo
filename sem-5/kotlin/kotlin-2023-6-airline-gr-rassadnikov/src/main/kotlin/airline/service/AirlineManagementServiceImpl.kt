package airline.service

import airline.api.*
import kotlinx.coroutines.flow.MutableSharedFlow
import kotlinx.datetime.Instant

class AirlineManagementServiceImpl(private val updatesFlow: MutableSharedFlow<FlightServiceAction>) :
    AirlineManagementService {
        override suspend fun scheduleFlight(flightId: String, departureTime: Instant, plane: Plane) {
            updatesFlow.emit(ScheduleFlightAMSAction(flightId, departureTime, plane))
        }

        override suspend fun delayFlight(flightId: String, departureTime: Instant, actualDepartureTime: Instant) {
            updatesFlow.emit(DelayFlightAMSAction(flightId, departureTime, actualDepartureTime))
        }

        override suspend fun cancelFlight(flightId: String, departureTime: Instant) {
            updatesFlow.emit(CancelFlightAMSAction(flightId, departureTime))
        }

        override suspend fun setCheckInNumber(flightId: String, departureTime: Instant, checkInNumber: String) {
            updatesFlow.emit(SetCheckFlightAMSAction(flightId, departureTime, checkInNumber))
        }

        override suspend fun setGateNumber(flightId: String, departureTime: Instant, gateNumber: String) {
            updatesFlow.emit(SetGateFlightAMSAction(flightId, departureTime, gateNumber))
        }
    }
