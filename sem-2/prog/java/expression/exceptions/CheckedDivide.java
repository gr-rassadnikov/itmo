package expression.exceptions;

import expression.Divide;
import expression.ExpressionMy;
import expression.exceptions.AEExpression;

import java.math.BigDecimal;
import java.util.Dictionary;

public class CheckedDivide extends Divide {
    public CheckedDivide(ExpressionMy a, ExpressionMy b) {
        super(a, b);
        set("/", a, b, 2, 1);
    }

    @Override
    public Number operation(Object value) {

        if (value instanceof Integer) {
            return super.getA().evaluate((int) value) / super.getB().evaluate((int) value);
        } else {
            return super.getA().evaluate((BigDecimal) value).divide(super.getB().evaluate((BigDecimal) value));
        }
    }

    @Override
    public int operation(int x, int y, int z) {
        getException(super.getA().evaluate(x, y, z), super.getB().evaluate(x, y, z));
        return super.getA().evaluate(x, y, z) / super.getB().evaluate(x, y, z);
    }

    private void getException(int a, int b) throws AEExpression {
        if (b == 0) {
            throw new AEExpression("divide by zero");
        }
        if (a == Integer.MIN_VALUE && b == -1) {
            throw new AEExpression("overflow");
        }
    }
}
