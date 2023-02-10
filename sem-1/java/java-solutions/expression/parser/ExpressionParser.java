package expression.parser;

import expression.*;

import java.util.ArrayList;
import java.util.List;

public class ExpressionParser implements Parser {
    public ExpressionParser() {

    }

    public Boolean isNumber(Character c) {
        return (c <= '9' && c >= '0');

    }

    public Boolean isVariable(Character c) {
        return (c == 'x' || c == 'y' || c == 'z');

    }

    public enum Type {
        ADD, SUBTRACT,
        DIVIDE, MULTIPLY,
        VARIABLE, CONST,
        LEFT_CLAMP, RIGHT_CLAMP,
        SHIFT_LEFT, SHIFT_RIGHT, SHIFT_ARIF,
        L0, T0
    }

    public static class Term {
        Type type;
        String value;

        public Term(Type type, String value) {
            this.type = type;
            this.value = value;
        }
    }


    public List<Term> ParseStringForList(String expression) {
        List<Term> result = new ArrayList<>();
        int position = -1;
        int was = -2;
        while (++position < expression.length()) {
            Character c = expression.charAt(position);
            switch (c) {
                case 't':
                    result.add(new Term(Type.T0, c.toString()));
                    position++;
                    continue;
                case 'l':
                    result.add(new Term(Type.L0, c.toString()));
                    position++;
                    continue;
                case '>':
                    position++;
                    if (position + 1 < expression.length() && expression.charAt(position + 1) == '>') {
                        result.add(new Term(Type.SHIFT_ARIF, c.toString()));
                        position++;
                        continue;
                    }
                    result.add(new Term(Type.SHIFT_RIGHT, c.toString()));
                    continue;
                case '<':
                    result.add(new Term(Type.SHIFT_LEFT, c.toString()));
                    position++;
                    continue;
                case '+':
                    result.add(new Term(Type.ADD, c.toString()));
                    continue;
                case '-':
                    if (was != position - 1 && position + 1 < expression.length() && isNumber(expression.charAt(position + 1))) {
                        StringBuilder sb = new StringBuilder();
                        while (position + 1 < expression.length() && isNumber(expression.charAt(position + 1))) {
                            position++;
                            sb.append(expression.charAt(position));
                        }
                        result.add(new Term(Type.CONST, "-" + sb));
                        continue;

                    }
                    result.add(new Term(Type.SUBTRACT, c.toString()));
                    continue;
                case '*':
                    result.add(new Term(Type.MULTIPLY, c.toString()));
                    continue;
                case '/':
                    result.add(new Term(Type.DIVIDE, c.toString()));
                    continue;
                case '(':
                    result.add(new Term(Type.LEFT_CLAMP, c.toString()));
                    continue;
                case ')':
                    result.add(new Term(Type.RIGHT_CLAMP, c.toString()));
                    continue;
                default:
                    StringBuilder sb = new StringBuilder();
                    if (isNumber(c)) {
                        sb.append(c);
                        while (position + 1 < expression.length() && isNumber(expression.charAt(position + 1))) {
                            position++;
                            sb.append(expression.charAt(position));
                        }
                        result.add(new Term(Type.CONST, sb.toString()));
                    } else if (isVariable(c)) {
                        was = position;
                        sb.append(c);
                        result.add(new Term(Type.VARIABLE, c.toString()));
                    }
            }

        }
        return result;
    }

    public class TermScanner {
        int position;
        public List<Term> termList;

        public TermScanner(List<Term> termList) {
            this.termList = termList;
        }

        public Term nextItem() {
            if (position == termList.size()) {
                return null;
            }
            return termList.get(position++);
        }

        public void SetLast() {
            position--;
        }

        public boolean hasNext() {
            return position < termList.size();
        }
    }

    public ExpressionMy parseExpression(TermScanner terms) {
        if (!terms.hasNext()) {
            return null;
        }
        return shifts(terms);
    }

    public ExpressionMy shifts(TermScanner terms) {
        ExpressionMy result = AddSubtract(terms);
        while (terms.hasNext()) {
            Term term = terms.nextItem();
            switch (term.type) {
                case SHIFT_ARIF:
                    result = new ShiftArif(result, AddSubtract(terms));
                    break;
                case SHIFT_RIGHT:
                    result = new ShiftRight(result, AddSubtract(terms));
                    break;
                case SHIFT_LEFT:
                    result = new ShiftLeft(result, AddSubtract(terms));
                    break;
                default:
                    terms.SetLast();
                    return result;
            }
        }
        return result;
    }

    public ExpressionMy AddSubtract(TermScanner terms) {
        ExpressionMy result = MultiplyDivide(terms);
        while (terms.hasNext()) {
            Term term = terms.nextItem();
            switch (term.type) {
                case ADD:
                    result = new Add(result, MultiplyDivide(terms));
                    break;
                case SUBTRACT:
                    result = new Subtract(result, MultiplyDivide(terms));
                    break;
                default:
                    terms.SetLast();
                    return result;
            }
        }
        return result;
    }

    public ExpressionMy MultiplyDivide(TermScanner terms) {
        ExpressionMy result = ConstVarUn(terms);
        while (terms.hasNext()) {
            Term term = terms.nextItem();
            switch (term.type) {

                case MULTIPLY:
                    result = new Multiply(result, ConstVarUn(terms));
                    break;
                case DIVIDE:
                    result = new Divide(result, ConstVarUn(terms));
                    break;
                default:
                    terms.SetLast();
                    return result;
            }
        }
        return result;
    }

    public ExpressionMy ConstVarUn(TermScanner terms) {
        Term term = terms.nextItem();
        switch (term.type) {
            case T0:
                ExpressionMy result = ConstVarUn(terms);
                return new UnT0(result);
            case L0:
                result = ConstVarUn(terms);
                return new UnL0(result);
            case SUBTRACT:
                result = ConstVarUn(terms);
                return new UnMinus(result);
            case CONST:
                return new Const(Integer.parseInt(term.value));
            case VARIABLE:
                return new Variable(term.value);
            default:
                result = parseExpression(terms);
                terms.nextItem();
                return result;
        }
    }


    @Override
    public TripleExpression parse(String expression) {

        return parseExpression(new TermScanner(ParseStringForList(expression)));

    }
}
