package expression;

import java.math.BigDecimal;

public class UnMinus implements ExpressionMy {
    ExpressionMy a;

    int priority = 3;
    int wasExpression = 0;


    public int getPriority() {
        return priority;
    }

    public int getWasExpression() {
        return wasExpression;
    }

    public String getCh() {
        return "u";
    }

    @Override
    public String getVar() {
        return null;
    }

    @Override
    public Number getConstant() {
        return 0;
    }

    @Override
    public ExpressionMy getA() {
        return a;
    }

    @Override
    public ExpressionMy getB() {
        return null;
    }

    public UnMinus(ExpressionMy a) {
        this.a = a;
        this.wasExpression = getWasExpression();
    }

    public String toString() {
        return "-(" + a.toString() + ")";
    }

    public String toMiniString() {
        if (priority > a.getPriority()) {
            return "-(" + a.toMiniString() + ")";
        }
        return "- " + a.toMiniString();
    }

    @Override
    public int evaluate(int value) {
        return a.evaluate(value) * (-1);
    }

    public int evaluate(int x, int y, int z) {
        return a.evaluate(x, y, z) * (-1);
    }

    public BigDecimal evaluate(BigDecimal value) {
        return BigDecimal.ZERO.subtract(a.evaluate(value));
    }


    public boolean equals(Object c) {
        return (c != null && c.getClass() == this.getClass() && ((Const) c).getConstant().equals(getConstant()));
    }

    @Override
    public int hashCode() {
        return a.hashCode() * 17 + 'u';
    }

}
