"use strict";

function Const(value) {
    this.value = value;
    this.type = "const";
    this.toString = () => String(this.value);
    this.evaluate = () => Number(this.value);
    this.prefix = () => String(this.value);
}

function Variable(value) {
    this.value = value;
    this.type = "variable";
    this.toString = () => this.value;
    this.evaluate = (x, y, z) => value === "x" ? x : value === "y" ? y : z;
    this.prefix = () => this.value;
}

function MultiOperation(type, operation, values) {
    this.operation = operation;
    this.type = type;
    this.values = values;
}

MultiOperation.prototype.evaluate = function (x, y, z) {
    let values = [];
    for (let i = 0; i < this.values.length; i++) {
        values.push(this.values[i].evaluate(x, y, z));
    }
    return this.operation(values);
};

MultiOperation.prototype.toString = function () {
    let str = "";
    for (let i = 0; i < this.values.length; i++) {
        str += this.values[i].toString() + " ";
    }
    return str + this.type;
};

MultiOperation.prototype.prefix = function () {
    let str = "";
    for (let i = 0; i < this.values.length - 1; i++) {
        str += this.values[i].prefix() + " ";
    }
    str += this.values[this.values.length - 1].prefix();
    return "(" + this.type + " " + str + ")";
}

function Add(first, second) {
    MultiOperation.call(this, "+", values => values[0] + values[1], [first, second]);
}

Add.prototype = Object.create(MultiOperation.prototype);

function Subtract(first, second) {
    MultiOperation.call(this, "-", values => values[0] - values[1], [first, second]);
}

Subtract.prototype = Object.create(MultiOperation.prototype);

function Multiply(first, second) {
    MultiOperation.call(this, "*", values => values[0] * values[1], [first, second]);
}

Multiply.prototype = Object.create(MultiOperation.prototype);

function Divide(first, second) {
    MultiOperation.call(this, "/", values => values[0] / values[1], [first, second]);
}

Divide.prototype = Object.create(MultiOperation.prototype);

function Negate(first) {
    MultiOperation.call(this, "negate", value => -value, [first]);
}

Negate.prototype = Object.create(MultiOperation.prototype);

function Sinh(first) {
    MultiOperation.call(this, "sinh", value => Math.sinh(value), [first]);
}

Sinh.prototype = Object.create(MultiOperation.prototype);

function Cosh(first) {
    MultiOperation.call(this, "cosh", value => Math.cosh(value), [first]);
}

Cosh.prototype = Object.create(MultiOperation.prototype);

function cntMean(values) {
    let sum = 0;
    for (let i = 0; i < values.length; i++) {
        sum += values[i];
    }
    return sum / values.length;
}

function cntVar(values) {
    let sum = 0;
    let mean = cntMean(values);
    for (let i = 0; i < values.length; i++) {
        sum += (values[i] - mean) * (values[i] - mean);
    }
    return sum / values.length;
}

function Mean(...args) {
    MultiOperation.call(this, "mean", values => cntMean(values), args)
}

Mean.prototype = Object.create(MultiOperation.prototype);

function Var(...args) {
    MultiOperation.call(this, "var", values => cntVar(values), args)
}

Var.prototype = Object.create(MultiOperation.prototype);

const operationsBinary = {
    "+": Add,
    "-": Subtract,
    "*": Multiply,
    "/": Divide,
};

function isDigit(digit) {
    return digit >= '0' && digit <= '9';
}

function ParsingError(mes, str) {
    this.message = mes + " in expression:" + str;
}

function parse(str) {
    let stack = [];
    let ind = 0;
    while (ind < str.length) {
        while ( ind < str.length && str[ind] === " ") {
            ind += 1;
        }
        let loc = "";
        while (ind < str.length && str[ind] !== " ") {
            loc = loc + str[ind];
            ind += 1;
        }
        let added;
        if (loc === "x" || loc === "y" || loc === "z") {
            added = new Variable(loc);
        } else if (loc === "+" || loc === "-" || loc === "*" || loc === "/") {
            added = new operationsBinary[loc](stack[stack.length - 2], stack.pop());
            stack.pop();
        } else if (loc === "negate") {
            added = new Negate(stack.pop());
        } else if (loc === "sinh") {
            added = new Sinh(stack.pop());
        } else if (loc === "cosh") {
            added = new Cosh(stack.pop());
        } else {
            added = new Const(loc);
        }
        stack.push(added);
    }
    return stack[0];
}

let ParserPrefix = function (str) {
    let ind = 0;

    function splitSpace() {
        while (ind < str.length && str[ind] === " ") {
            ind += 1;
        }
    }

    function isWhiteOrBracketSymbol() {
        if (str[ind] === " " || str[ind] === "(" || str[ind] === ")") {
            return true;
        }
    }

    function parsePrefixRecursive(wasOpenLeftBracket) {
        let result;
        splitSpace();
        if (str[ind] === ')' && wasOpenLeftBracket === false) {
            throw new ParsingError("many closing in end", str);
        } else if (str[ind] === '(') {
            ind++;
            result = parsePrefixRecursive(true);
            if (result.type === "const" || result.type === "variable") {
                throw new ParsingError("expected expression in ()", str);
            }
        } else if (str[ind] === '-' && isDigit(str[ind + 1])) {
            let strConst = '-';
            ind++;
            while (isDigit(str[ind])) {
                strConst += str[ind++];
            }
            result = new Const(strConst);
        } else if (isDigit(str[ind])) {
            let strConst = '';
            while (isDigit(str[ind])) {
                strConst += str[ind++];
            }
            result = new Const(strConst);
        } else if (str[ind] === 'x' || str[ind] === 'y' || str[ind] === 'z') {
            result = new Variable(str[ind++]);
            if (ind < str.length && !isWhiteOrBracketSymbol()) {
                throw new ParsingError("expected white space ot bracket after variable", str);
            }
        } else if (str[ind] === 'n') {
            let type = "";
            while (ind < str.length && !isWhiteOrBracketSymbol()) {
                type += str[ind++];
            }
            if (type === "negate") {
                result = new Negate(parsePrefixRecursive(false));
            } else {
                throw new ParsingError("unknown symbol(perhaps you meant negate)", str);
            }
        } else if (str[ind] === 'm') {
            let type = '';
            while (ind < str.length && !isWhiteOrBracketSymbol()) {
                type += str[ind++];
            }
            if (type === "mean") {
                let values = [];
                while (str[ind] !== ")") {
                    values.push(parsePrefixRecursive(false));
                }
                result = new Mean(...values);
            } else {
                throw new ParsingError("unknown symbol(perhaps you meant mean)", str);
            }
        } else if (str[ind] === 'v') {
            let type = '';
            while (ind < str.length && !isWhiteOrBracketSymbol()) {
                type += str[ind++];
            }
            if (type === "var") {
                let values = [];
                while (str[ind] !== ")") {
                    values.push(parsePrefixRecursive(false));
                }
                result = new Var(...values);
            } else {
                throw new ParsingError("unknown symbol(perhaps you meant var)", str);
            }
        } else if (str[ind] === '+' || str[ind] === '-' || str[ind] === '*' || str[ind] === '/') {
            let type = str[ind++];
            if (wasOpenLeftBracket === false) {
                throw new ParsingError("expected open bracket", str);
            }
            const first = parsePrefixRecursive(false);
            const second = parsePrefixRecursive(false);
            if (first === undefined || second === undefined) {
                throw new ParsingError("expected two arguments for binary function", str);
            }
            result = new operationsBinary[type](first, second);
        } else {
            throw  new ParsingError("unknown symbol", str);
        }
        splitSpace();
        if (wasOpenLeftBracket) {
            if (str[ind] === ')') {
                ind++;
                wasOpenLeftBracket = false;
            } else {
                throw new ParsingError("expected close bracket", str);
            }
        }
        return result;
    }

    let result = parsePrefixRecursive(false);
    if (ind < str.length) {
        throw new ParsingError("expected end of expression", str);
    }
    return result;
}

const parsePrefix = (str) => ParserPrefix(str);