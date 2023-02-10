package expression.exceptions;

import expression.ExpressionMy;
import expression.Multiply;
import expression.exceptions.AEExpression;

import java.lang.management.MemoryUsage;
import java.math.BigDecimal;

public class CheckedMultiply extends Multiply {
    public CheckedMultiply(ExpressionMy a, ExpressionMy b) {
        super(a, b);
        set("*", a, b, 2, 0);
    }

    @Override
    public Number operation(Object value) {

        if (value instanceof Integer) {
            return super.getA().evaluate((int) value) * super.getB().evaluate((int) value);
        } else {
            return super.getA().evaluate((BigDecimal) value).multiply(super.getB().evaluate((BigDecimal) value));
        }
    }

    @Override
    public int operation(int x, int y, int z) {
        getException(super.getA().evaluate(x, y, z), super.getB().evaluate(x, y, z));
        return super.getA().evaluate(x, y, z) * super.getB().evaluate(x, y, z);
    }

    private void getException(int a, int b) throws AEExpression {
        if (a > 0 && b > 0 && a > Integer.MAX_VALUE / b ||
                a > 0 && b < 0 && b < Integer.MIN_VALUE / a ||
                a < 0 && b > 0 && a < Integer.MIN_VALUE / b ||
                a < 0 && b < 0 && a < Integer.MAX_VALUE / b) {
            throw new AEExpression("overflow");
        }
    }

}
