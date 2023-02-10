package expression.exceptions;

import expression.*;

import java.util.*;


public class ExpressionParser implements TripleParser {
    public ExpressionParser() {

    }

    private void getException(String str) throws ParsingException {
        throw new ParsingException(str);
    }

    public boolean isNumber(Character c) {
        return (c <= '9' && c >= '0');

    }

    public boolean checkBiggerInteger(String str) {
        if (str.charAt(0) == '-') {
            return false;
        }
        if (str.length() > 10) {
            return true;
        } else if (str.length() < 10) {
            return false;
        }
        String maxValue = Integer.toString(Integer.MAX_VALUE);
        for (int i = 0; i < 10; i++) {
            if (str.charAt(i) > maxValue.charAt(i)) {
                return true;
            } else if (str.charAt(i) < maxValue.charAt(i)) {
                return false;
            }
        }
        return false;

    }

    public boolean checkSmallerInteger(String str) {
        if (str.charAt(0) != '-') {
            return false;
        }
        if (str.length() > 11) {
            return true;
        } else if (str.length() < 11) {
            return false;
        }
        String minValue = Integer.toString(Integer.MIN_VALUE);
        for (int i = 1; i < 11; i++) {
            if (str.charAt(i) > minValue.charAt(i)) {
                return true;
            } else if (str.charAt(i) < minValue.charAt(i)) {
                return false;
            }
        }
        return false;

    }

    public boolean isVariable(Character c) {
        return (c == 'x' || c == 'y' || c == 'z');

    }

    public enum Type {
        ADD, SUBTRACT,
        DIVIDE, MULTIPLY,
        VARIABLE, CONST,
        LEFT_CLAMP, RIGHT_CLAMP,
        SHIFT_LEFT, SHIFT_RIGHT, SHIFT_ARIF,
        L0, T0, ELSE, MAX, MIN
    }

    Set<Type> SetBinaryType = Set.of(Type.ADD, Type.SUBTRACT, Type.DIVIDE,
            Type.MULTIPLY, Type.MIN, Type.MAX);
    Set<Type> SetUnaryType = Set.of(Type.L0, Type.T0);
    Set<Type> SetValueType = Set.of(Type.VARIABLE, Type.CONST);


    public static class Term {

        Type type;
        String value;

        public Term(Type type, String value) {
            this.type = type;
            this.value = value;
        }

        @Override
        public String toString() {
            return value;
        }
    }


    public List<Term> ParseStringForList(String expression) {
        List<Term> result = new ArrayList<>();
        int position = -1;
        int was = -2;
        while (++position < expression.length()) {
            Character c = expression.charAt(position);
            if (c == '%' || c == '[' || c == ']' || c == '>' || c == '<') {
                getException("ERROR_INSERTED");
            }
            switch (c) {
                case 't':
                    result.add(new Term(Type.T0, c.toString() + "0"));
                    position++;
                    continue;
                case 'l':
                    result.add(new Term(Type.L0, c.toString() + "0"));
                    position++;
                    continue;
                case 'm':
                    position++;
                    if (expression.charAt(position) == 'i' && expression.charAt(position + 1) == 'n') {
                        result.add(new Term(Type.MIN, "min"));
                    } else {
                        result.add(new Term(Type.MAX, "max"));
                    }
                    position++;
                    if (position + 1 >= expression.length() || isNumber(expression.charAt(position + 1))
                            || isVariable(expression.charAt(position + 1))) {
                        getException(expression);
                    }
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
                        if (position >= 2 && expression.charAt(position - 1) == '0' &&
                                (expression.charAt(position - 2) == 't' || expression.charAt(position - 2) == 'l')) {
                            getException(expression);
                        }
                        result.add(new Term(Type.CONST, sb.toString()));
                    } else if (isVariable(c)) {
                        was = position;
                        sb.append(c);
                        if (position >= 2 && expression.charAt(position - 1) == '0' &&
                                (expression.charAt(position - 2) == 't' || expression.charAt(position - 2) == 'l')) {
                            getException(expression);
                        }
                        result.add(new Term(Type.VARIABLE, c.toString()));
                    } else if (!Character.isWhitespace(c)) {
                        result.add(new Term(Type.ELSE, c.toString()));
                    }
            }

        }

        return result;
    }

    public class TermScanner {
        int position;
        public List<Term> termList;

        public String toString(List<Term> termListc) {
            StringBuilder str = new StringBuilder("");
            for (Term term : termListc) {
                str.append(term.value);
            }
            return str.toString();
        }

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

        public enum conditions {
            START, WAS_UNARY, WAS_BINARY, WAS_NUMBER_VAR
        }

        public String checkPE() {
            conditions condition = conditions.START;
            boolean wasLastClamp = false;
            int clampCnt = 0;
            boolean wasVarConst = false;

            if (termList.size() == 1 && termList.get(0).type == Type.ELSE) {
                return "Bare " + toString(termList);
            }

            for (int i = 0; i < termList.size(); i++) {
                if (SetBinaryType.contains(termList.get(i).type) &&
                        (condition == conditions.START || wasLastClamp && condition == conditions.WAS_BINARY)) {
                    if (termList.size() == 1) {
                        return "Bare " + toString(termList);
                    }
                    if (termList.get(i).type != Type.SUBTRACT) {
                        return "No first argument";
                    }
                }
                if (SetBinaryType.contains(termList.get(i).type) &&
                        (condition == conditions.WAS_BINARY)
                        && termList.get(i).type != Type.SUBTRACT) {
                    if (termList.size() == 1) {
                        return "Bare " + toString(termList);
                    }
                    return "No middle argument";
                }
                if (SetBinaryType.contains(termList.get(i).type)
                        && (i == termList.size() - 1 || termList.get(i + 1).type == Type.RIGHT_CLAMP)) {
                    if (termList.size() == 1 && condition != conditions.WAS_NUMBER_VAR) {
                        return "Bare " + toString(termList);
                    }
                    return "No last argument";
                }
                if (SetBinaryType.contains(termList.get(i).type) && condition == conditions.WAS_UNARY
                        && termList.get(i).type != Type.SUBTRACT) {
                    return toString(termList);
                }
                if (SetUnaryType.contains(termList.get(i).type) && i == termList.size() - 1) {
                    return toString(termList);
                }
                if (termList.get(i).type == Type.RIGHT_CLAMP && clampCnt <= 0) {
                    return "No opening parenthesis";
                }
                if (termList.get(i).type == Type.ELSE) {
                    if (condition == conditions.START) {
                        return "Start symbol";
                    } else if (i == termList.size() - 1) {
                        return "End symbol";
                    } else {
                        return "Middle symbol";
                    }
                }
                if (termList.get(i).type == Type.CONST &&
                        (checkSmallerInteger(termList.get(i).value)
                                || checkBiggerInteger(termList.get(i).value))) {
                    return "Constant overflow";
                }
                if (condition == conditions.WAS_NUMBER_VAR && termList.get(i).type == Type.CONST && !wasLastClamp) {
                    return "Spaces in numbers";
                }
                if (SetBinaryType.contains(termList.get(i).type)) {
                    condition = conditions.WAS_BINARY;
                } else if (SetUnaryType.contains(termList.get(i).type)) {
                    condition = conditions.WAS_UNARY;
                } else if (SetValueType.contains(termList.get(i).type)) {
                    wasVarConst = true;
                    condition = conditions.WAS_NUMBER_VAR;
                }
                if (termList.get(i).type == Type.LEFT_CLAMP) {
                    clampCnt++;
                    wasLastClamp = true;
                } else if (termList.get(i).type == Type.RIGHT_CLAMP) {
                    clampCnt--;
                    wasLastClamp = true;
                } else {
                    wasLastClamp = false;
                }
            }
            if (clampCnt > 0) {
                return "No closing parenthesis";
            }
            if (condition == conditions.START || !wasVarConst) {
                return toString(termList);
            }
            return "";
        }
    }

    public ExpressionMy parseExpression(TermScanner terms) {
        if (!terms.hasNext()) {
            return null;
        }
        return minmax(terms);
    }

    public ExpressionMy minmax(TermScanner terms) {
        ExpressionMy result = AddSubtract(terms);
        while (terms.hasNext()) {
            Term term = terms.nextItem();
            switch (term.type) {
                case MIN:
                    result = new Min(result, AddSubtract(terms));
                    break;
                case MAX:
                    result = new Max(result, AddSubtract(terms));
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
                    result = new CheckedAdd(result, MultiplyDivide(terms));
                    break;
                case SUBTRACT:
                    result = new CheckedSubtract(result, MultiplyDivide(terms));
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
                    result = new CheckedMultiply(result, ConstVarUn(terms));
                    break;
                case DIVIDE:
                    result = new CheckedDivide(result, ConstVarUn(terms));
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
                return new CheckedNegate(result);
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
        TermScanner terms = new TermScanner(ParseStringForList(expression));
        String str = terms.checkPE();
        if (!str.isEmpty()) {
            getException(str);
        }
        return parseExpression(terms);
    }
}
