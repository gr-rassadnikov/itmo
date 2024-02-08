/**
 * @author : Rassadnikov Grigorii
 *
 */
class Solution : MonotonicClock {
    private var c1 by RegularInt(0)
    private var c2 by RegularInt(0)
    private var c3 by RegularInt(0)

    private var e1 by RegularInt(0)
    private var e2 by RegularInt(0)

    private var e1N by RegularInt(0)
    private var e2N by RegularInt(0)
    private var c3N by RegularInt(0)
    private var c2N by RegularInt(0)
    private var c1N by RegularInt(0)

    override fun write(time: Time) {
        c1 = time.d1
        c2 = time.d2
        c3 = time.d3
        e2 = time.d2
        e1 = time.d1
    }

    override fun read(): Time {
        e1N = e1
        e2N = e2
        c3N = c3
        c2N = c2
        c1N = c1

        return if (c1N == e1N && c2N == e2N) {
            Time(c1N, c2N, c3N)
        } else if (c1N == e1N) {
            Time(c1N, c2N, 0)
        } else {
            Time(c1N, 0, 0)
        }
    }
}
