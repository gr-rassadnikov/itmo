package expression;

import java.math.BigDecimal;

public class Divide extends Binary {

    public Divide(ExpressionMy a, ExpressionMy b) {
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
        return super.getA().evaluate(x, y, z) / super.getB().evaluate(x, y, z);
    }

}
