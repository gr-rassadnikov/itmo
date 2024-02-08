private class Constants {
    companion object {
        const val S = 1000
        const val M = 60
        const val H = 3600
    }
}

val Int.milliseconds: Time
    get() = toLong().milliseconds

val Long.milliseconds: Time
    get() = Time(this / Constants.S, this.toInt() % Constants.S)

val Int.seconds: Time
    get() = toLong().seconds

val Long.seconds: Time
    get() = Time(this, 0)

val Int.minutes: Time
    get() = toLong().minutes

val Long.minutes: Time
    get() = Time(this * Constants.M, 0)

val Int.hours: Time
    get() = toLong().hours

val Long.hours: Time
    get() = Time(this * Constants.H, 0)

operator fun Time.plus(other: Time): Time {
    val totalMilliseconds = this.milliseconds + other.milliseconds
    return Time(
        this.seconds + other.seconds + totalMilliseconds / Constants.S,
        totalMilliseconds % Constants.S)
}

operator fun Time.minus(other: Time): Time {
    val totalMilliseconds = Constants.S + this.milliseconds - other.milliseconds
    return Time(
        this.seconds - (other.seconds + 1) + totalMilliseconds / Constants.S,
        totalMilliseconds % Constants.S)
}
