package expression;

import java.math.BigDecimal;

public class UnT0 implements ExpressionMy {
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
        return "t";
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

    public UnT0(ExpressionMy a) {
        this.a = a;
        this.wasExpression = getWasExpression();
    }

    public String toString() {
        return "t0(" + a.toString() + ")";
    }

    public String toMiniString() {
        if (priority > a.getPriority()) {
            return "t0(" + a.toMiniString() + ")";
        }
        return "t0 " + a.toMiniString();
    }

    @Override
    public int evaluate(int value) {
        int result = a.evaluate(value);
        String resultStr = String.format("%32s", Integer.toBinaryString(result)).replaceAll(" ", "0");
        resultStr = new StringBuilder(resultStr).reverse().toString();
        int cnt = 0;
        while (cnt < 32 && resultStr.charAt(cnt) == '0') {
            cnt++;
        }
        return cnt;
    }

    public int evaluate(int x, int y, int z) {
        int result = a.evaluate(x, y, z);
        String resultStr = String.format("%32s", Integer.toBinaryString(result)).replaceAll(" ", "0");
        resultStr = new StringBuilder(resultStr).reverse().toString();
        int cnt = 0;
        while (cnt < 32 && resultStr.charAt(cnt) == '0') {
            cnt++;
        }
        return cnt;
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
