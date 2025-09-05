fun main() {
    val (n, m, k) = readln().split(" ").map { it.toInt() }

    val a: MutableList<MutableList<Int>> = mutableListOf()
    val ans: MutableList<MutableList<Int>> = mutableListOf()
    repeat(n) {
        a.add(mutableListOf())
        ans.add(mutableListOf())
    }

    readln().split(" ").mapIndexed { index, s -> a[s.toInt() - 1].add(index + 1) }

    var C = 0
    for (i in 0..<m) {
        while (a[i].isNotEmpty()) {
            ans[C].add(a[i].last())
            a[i].removeAt(a[i].size - 1)
            C++
            C %= k
        }
    }

    for (i in 0..<k) {
        print("${ans[i].size} ")
        ans[i].forEach { print("$it ") }
        println()
    }
}