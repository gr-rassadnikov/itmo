package expression;

import java.math.BigDecimal;

public class Const implements ExpressionMy {
    Number constant;
    int priority = 3;
    int wasExpression = 0;


    public int getPriority() {
        return priority;
    }

    public int getWasExpression() {
        return wasExpression;
    }

    public String getCh() {
        return "c";
    }

    @Override
    public String getVar() {
        return null;
    }

    @Override
    public Number getConstant() {
        return constant;
    }

    @Override
    public ExpressionMy getA() {
        return null;
    }

    @Override
    public ExpressionMy getB() {
        return null;
    }

    public Const(int constant) {
        this.constant = constant;
    }

    public Const(Number constant) {
        this.constant = constant;
    }

    public Const(BigDecimal constant) {
        this.constant = constant;
    }


    public String toString() {
        return "" + constant.toString();
    }

    public String toMiniString() {
        return "" + constant.toString();
    }

    @Override
    public int evaluate(int value) {
        return (int) this.constant;
    }

    public int evaluate(int x, int y, int z) {
        return (int) this.constant;
    }

    public BigDecimal evaluate(BigDecimal value) {
        return (BigDecimal) this.constant;
    }


    public boolean equals(Object c) {
        return (c != null && c.getClass() == this.getClass() && ((Const) c).getConstant().equals(getConstant()));
    }

    @Override
    public int hashCode() {
        return constant.hashCode();
    }
}
//javac expression/Multiply.java
//javac expression/Add.java
//javac expression/Divide.java
//javac expression/Subtract.java
//javac expression/Variable.java
//javac expression/Const.java
