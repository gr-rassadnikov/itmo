import java.lang.StringBuilder

class Writer {

    private var level = 0

    var result = StringBuilder()

    fun scope(code: Writer.() -> Unit) {
        level++
        code()
        level--
    }

    fun newLine() {
        result.append("\n")
    }

    fun line(string: String) {
        result.append(tabs() + string + "\n")
    }

    private fun tabs(cnt: Int = level) = "\t".repeat(cnt)

}