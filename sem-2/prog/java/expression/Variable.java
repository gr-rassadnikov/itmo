package expression;

import java.math.BigDecimal;

public class Variable implements ExpressionMy {

    String var;
    int priority = 3;
    int wasExpression = 0;

    public int getPriority() {
        return priority;
    }

    public int getWasExpression() {
        return wasExpression;
    }

    public String getCh() {
        return "v";
    }

    public String getVar() {
        return var;
    }

    public Number getConstant() {
        return -1;
    }

    public ExpressionMy getA() {
        return null;
    }

    public ExpressionMy getB() {
        return null;
    }

    public Variable(String var) {
        this.var = var;
    }

    public String toString() {
        return var;
    }

    public String toMiniString() {
        return var;
    }

    public int evaluate(int value) {
        return value;
    }

    public int evaluate(int x, int y, int z) {
        if (var.equals("x")) {
            return x;
        }
        if (var.equals("y")) {
            return y;
        }
        return z;
    }

    public BigDecimal evaluate(BigDecimal value) {
        return value;
    }


    public boolean equals(Object c) {
        return (c != null && c.getClass() == this.getClass() && ((Variable) c).getVar().equals(getVar()));

    }

    @Override
    public int hashCode() {
        return var.charAt(0);
    }
}
