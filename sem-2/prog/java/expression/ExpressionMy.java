package expression;

import java.math.BigDecimal;

public interface ExpressionMy extends Expression, TripleExpression, BigDecimalExpression {
    String getVar();

    Number getConstant();

    String toString();

    int evaluate(int value);

    ExpressionMy getA();

    ExpressionMy getB();

    String toMiniString();

    String getCh();

    int getPriority();

    int getWasExpression();

    int evaluate(int x, int y, int z);

    BigDecimal evaluate(BigDecimal value);


}
