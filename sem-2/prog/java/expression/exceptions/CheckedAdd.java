package expression.exceptions;

import expression.Add;
import expression.ExpressionMy;
import expression.exceptions.AEExpression;
import expression.exceptions.*;

import java.math.BigDecimal;


public class CheckedAdd extends Add {
    public CheckedAdd(ExpressionMy a, ExpressionMy b) {
        super(a, b);
        set("+", a, b, 1, 0);
    }

    @Override
    public Number operation(Object value) {

        if (value instanceof Integer) {
            return super.getA().evaluate((int) value) + super.getB().evaluate((int) value);
        } else {
            return super.getA().evaluate((BigDecimal) value).add(super.getB().evaluate((BigDecimal) value));
        }
    }

    @Override
    public int operation(int x, int y, int z) {
        getException(super.getA().evaluate(x, y, z), super.getB().evaluate(x, y, z));
        return super.getA().evaluate(x, y, z) + super.getB().evaluate(x, y, z);
    }

    private void getException(int a, int b) throws AEExpression {
        if (b > 0 && a > Integer.MAX_VALUE - b || b < 0 && a < Integer.MIN_VALUE - b) {
            throw new AEExpression("overflow");
        }

    }
}
