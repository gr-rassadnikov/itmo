import org.antlr.v4.runtime.tree.ParseTree
import java.text.ParseException

class MathExprCalculateVisitor(private val logger: LogMathExprResult) : MathExprBaseVisitor<Int>() {
    private val storage = mutableMapOf<String, Int>()

    override fun visit(tree: ParseTree?): Int {
        if (tree == null) {
            throw ParseException("ERROR: incorrect token at tree.", -1)
        }
        try {
            return super.visit(tree)
        } catch (e: NullPointerException) {
            throw ParseException("ERROR: incorrect visiting child by lexer.", -1)
        }
    }

    override fun visitNewState(ctx: MathExprParser.NewStateContext): Int {
        val variable = ctx.VAR().text
        val value = visit(ctx.expr())
        storage[variable] = value
        logger.println("$variable = $value\n")
        return value
    }

    override fun visitExprCnk(ctx: MathExprParser.ExprCnkContext): Int {
        val n = visit(ctx.expr(0))
        val k = visit(ctx.expr(1))

        return binomialCoeff(n, k)
    }

    override fun visitExprMulDiv(ctx: MathExprParser.ExprMulDivContext): Int {
        val l = visit(ctx.expr(0))
        val r = visit(ctx.expr(1))

        return when (val token = ctx.op.type) {
            MathExprParser.MUL -> l * r
            MathExprParser.DIV -> l / r
            else -> throw ParseException("ERROR: expected '*' or '/' token, but found: $token", ctx.ruleIndex)
        }
    }

    override fun visitExprAddSub(ctx: MathExprParser.ExprAddSubContext): Int {
        val l = visit(ctx.expr(0))
        val r = visit(ctx.expr(1))

        return when (val token = ctx.op.type) {
            MathExprParser.ADD -> l + r
            MathExprParser.SUB -> l - r
            else -> throw ParseException("ERROR: expected '+' or '-' token, but found: $token", ctx.ruleIndex)
        }
    }

    override fun visitExprParens(ctx: MathExprParser.ExprParensContext): Int =
        visit(ctx.expr())

    override fun visitExprInt(ctx: MathExprParser.ExprIntContext): Int = try {
        ctx.INT().text.toInt()
    } catch (e: NumberFormatException) {
        throw ParseException("ERROR: can't cast ${ctx.INT().text}to Int.", ctx.ruleIndex)
    }

    override fun visitExprVar(ctx: MathExprParser.ExprVarContext): Int =
        storage[ctx.VAR().text] ?: throw ParseException("ERROR: can't find variable ${ctx.VAR().text}", ctx.ruleIndex)

    @Throws(ParseException::class)
    private fun binomialCoeff(n: Int, k: Int): Int {
        if (n < 0 || k < 0) {
            throw ParseException("ERROR: binomialCoeff must have positive arguments.", -1)
        }
        val result = multiplyFromTo(n - k + 1, n) / multiplyFromTo(1, k)
        if (result * multiplyFromTo(1, k) != multiplyFromTo (n - k + 1, n)) {
            throw ParseException("ERROR: can' cast to Int, value is bigger then Int.MAX_VALUE.", -1)
        }
        return result
    }

    @Throws(ParseException::class)
    private fun multiplyFromTo(from: Int, to: Int): Int {
        var result = 1
        for (i in from..to) {
            if (Int.MAX_VALUE / i < result) {
                throw ParseException("ERROR: can' cast to Int, value is bigger then Int.MAX_VALUE.", -1)
            }
            result *= i
        }
        return result
    }

}
