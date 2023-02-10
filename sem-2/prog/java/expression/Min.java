package expression;

import java.math.BigDecimal;

public class Min extends Binary {

    public Min(ExpressionMy a, ExpressionMy b) {
        set("min", a, b, 0, 1);
    }

    @Override
    public Number operation(Object value) {

        if (super.getA().evaluate((int) value) < super.getB().evaluate((int) value)) {
            return super.getA().evaluate((int) value);
        }
        return super.getB().evaluate((int) value);
    }

    @Override
    public int operation(int x, int y, int z) {
        if (super.getA().evaluate(x, y, z) < super.getB().evaluate(x, y, z)) {
            return super.getA().evaluate(x, y, z);
        }
        return super.getB().evaluate(x, y, z);
    }


}
