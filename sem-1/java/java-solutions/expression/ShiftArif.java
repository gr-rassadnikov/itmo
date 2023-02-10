package expression;

import java.math.BigDecimal;

public class ShiftArif extends Binary {

    public ShiftArif(ExpressionMy a, ExpressionMy b) {
        set(">>>", a, b, 0, 1);
    }

    @Override
    public Number operation(Object value) {

        if (value instanceof Integer) {
            return super.getA().evaluate((int) value) >>> super.getB().evaluate((int) value);
        }
        return 0;
    }

    @Override
    public int operation(int x, int y, int z) {
        return super.getA().evaluate(x, y, z) >>> super.getB().evaluate(x, y, z);
    }


}
