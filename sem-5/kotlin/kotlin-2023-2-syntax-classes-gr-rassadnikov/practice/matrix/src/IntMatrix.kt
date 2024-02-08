class IntMatrix(val rows: Int, val columns: Int) {
    private val matrix: IntArray

    init {
        checkCorrectInput()
        matrix = IntArray(rows * columns)
    }

    operator fun get(row: Int, colum: Int): Int {
        checkCorrectInput(row, colum)
        return matrix[row * columns + colum]
    }

    operator fun set(row: Int, colum: Int, value: Int) {
        checkCorrectInput(row, colum)
        matrix[row * columns + colum] = value
    }

    private fun checkCorrectInput(row: Int = rows - 1, column: Int = columns - 1) {
        if (row !in 0..<rows || column !in 0..<columns)
            throw IllegalArgumentException("Incorrect number of rows/columns")
    }

}
