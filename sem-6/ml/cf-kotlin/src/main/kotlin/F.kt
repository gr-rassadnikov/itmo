fun main() {
    val k = readln().toInt()
    val cm: Array<IntArray> = Array(k) { readln().split(" ").map { it.toInt() }.toIntArray() }

    val precision = DoubleArray(k)
    val rec = DoubleArray(k)
    val f1 = DoubleArray(k)
    var f1w = 0.0
    var pw = 0.0
    var rw = 0.0
    var tp = 0.0
    var fp = 0.0
    var fn = 0.0
    var samples = 0.0
    for (i in 0..<k) {
        var col = 0
        var row = 0
        for (j in 0..<k) {
            col += cm[j][i]
            row += cm[i][j]
        }
        rec[i] = (if (row == 0) 0.0 else 1.0 * cm[i][i] / row)
        precision[i] = (if (col == 0) 0.0 else 1.0 * cm[i][i] / col)
        f1[i] =
            (if (precision[i] + rec[i] == 0.0) 0.0 else 2 * precision[i] * rec[i] / (precision[i] + rec[i]))
        f1w += f1[i] * row
        tp += cm[i][i] * row
        fp += (col - cm[i][i]) * row
        fn += (row  - cm[i][i]) * row
        pw += precision[i] * row
        rw += rec[i] * row

        samples += row.toDouble()
    }
    pw /= samples
    rw /= samples
    f1w /= samples
    tp /= samples
    fp /= samples
    fn /= samples

    println(if (tp + 0.5 * (fp + fn) == 0.0) 0 else tp / (tp + 0.5 * (fp + fn)))
    println(if (pw + rw < 1e-10) 0.0 else 2 * pw * rw / (pw + rw))
    println(f1w)
}
