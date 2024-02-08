import kotlin.text.StringBuilder

class LogMathExprResult {

    private val sb = StringBuilder()

    fun println(str: String) {
        sb.append(str)
    }

    fun result(): String = sb.toString()
}
