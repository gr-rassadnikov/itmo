package expression.exceptions;

import expression.ExpressionMy;
import expression.UnMinus;
import expression.exceptions.AEExpression;

import java.math.BigDecimal;

public class CheckedNegate extends UnMinus {
    public CheckedNegate(ExpressionMy a) {
        super(a);

    }

    @Override
    public int evaluate(int value) {
        return super.getA().evaluate(value) * (-1);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        getException(super.getA().evaluate(x, y, z));
        return super.getA().evaluate(x, y, z) * (-1);
    }

    @Override
    public BigDecimal evaluate(BigDecimal value) {
        return BigDecimal.ZERO.subtract(super.getA().evaluate(value));
    }


    private void getException(int a) throws AEExpression {
        if (a == Integer.MIN_VALUE) {
            throw new AEExpression("overflow");
        }
    }
}
