package expression;


import java.math.BigDecimal;
import java.util.List;

public abstract class Binary implements ExpressionMy {
    private ExpressionMy a;
    private ExpressionMy b;
    private String ch;
    private int priority;
    private int wasExpression;

    public int getPriority() {
        return priority;
    }

    public int getWasExpression() {
        return wasExpression;
    }

    @Override
    public String getVar() {
        return null;
    }

    @Override
    public Number getConstant() {
        return -1;
    }

    @Override
    public ExpressionMy getA() {
        return a;
    }

    @Override
    public ExpressionMy getB() {
        return b;
    }

    public String getCh() {
        return ch;
    }

    public void set(String ch, ExpressionMy a, ExpressionMy b, int priority, int was) {
        this.a = a;
        this.b = b;
        this.ch = ch;
        this.priority = priority;
        this.wasExpression = was;
    }

    @Override
    public String toString() {

        return "(" + a.toString() + " " + ch + " " + b.toString() + ")";
    }

    @Override
    public String toMiniString() {
        StringBuilder result = new StringBuilder("");
        if (a.getPriority() < priority) {
            result.append("(").append(a.toMiniString()).append(")");
        } else {
            result.append(a.toMiniString());
        }
        result.append(" ").append(ch).append(" ");

        if (b.getPriority() == 0 && priority == 1) {
            result.append("(").append(b.toMiniString()).append(")");
        } else if (priority < b.getPriority() ||
                !(priority == 2 && (b.getWasExpression() == 1 ||
                        b.getPriority() == 1) || wasExpression == 1)) {
            result.append(b.toMiniString());
        } else {
            result.append("(").append(b.toMiniString()).append(")");
        }

        return result.toString();

    }

    public Number operation(Object value) {
        return 0;
    }

    public int operation(int x, int y, int z) {
        return 0;
    }

    @Override
    public int evaluate(int value) {
        return (int) operation(value);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        if (a == null) {
            return 0;
        }
        return operation(x, y, z);
    }

    @Override
    public BigDecimal evaluate(BigDecimal value) {
        return (BigDecimal) operation(value);
    }

    @Override
    public boolean equals(Object c) {
        return (c != null && c.getClass() == this.getClass() && ((Binary) c).getA().equals(getA())
                && ((Binary) c).getB().equals(getB()));
    }


    @Override
    public int hashCode() {
        return (a.hashCode() * 17 + b.hashCode()) * 17 + ch.hashCode();
    }
}
