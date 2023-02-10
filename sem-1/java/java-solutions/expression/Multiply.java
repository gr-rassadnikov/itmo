package expression;

import java.math.BigDecimal;


public class Multiply extends Binary {

    public Multiply(ExpressionMy a, ExpressionMy b) {
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
        return super.getA().evaluate(x, y, z) * super.getB().evaluate(x, y, z);
    }
}
