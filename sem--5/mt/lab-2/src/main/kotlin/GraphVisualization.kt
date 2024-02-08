import java.io.PrintWriter

class GraphVisualization(
    private val root: Node,
    private val file: String = "out-graph"
) {
    private val sb = StringBuilder("digraph G {\n")
    fun run() {
        root.toGraph(0, sb)
        sb.append("}\n")
        createFile()
    }

    private fun createFile() {
        PrintWriter("$file.dot").use {
            it.println(sb.toString())
        }
    }

}
