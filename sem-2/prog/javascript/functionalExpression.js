"use strict";
const variable = value => (x, y, z) => value === "x" ? x : (value === "y" ? y: z);
const cnst = value => () => value;
const unaryOperation = operation => first => (x, y, z) => operation(first(x, y, z));
const binaryOperation = operation => (first, second) => (x, y, z) => operation(first(x, y, z), second(x, y, z));
const add = binaryOperation((first, second) => first + second);
const subtract = binaryOperation((first, second) => first - second);
const multiply = binaryOperation((first, second) => first * second);
const divide = binaryOperation((first, second) => first / second);
const negate = unaryOperation(first => - first);
const sinh = unaryOperation(first  => Math.sinh(first));
const cosh = unaryOperation(first => Math.cosh(first));
const pi = cnst(Math.PI);
const e = cnst(Math.E);