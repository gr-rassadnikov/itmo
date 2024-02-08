
fun main() {
    val parser = Parser("for (int x = 0, y = 1, z = 2, w = 3; x < 100; x++)")
    val tree = parser.parse()
    val g = GraphVisualization(tree, "graph")
    g.run()
}
