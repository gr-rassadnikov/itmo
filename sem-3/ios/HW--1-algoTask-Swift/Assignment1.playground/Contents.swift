import Cocoa

enum CalculatorError: Error {
    case IncorrectOperator(String)
    case StackError(String)
    case IncorrectNumber(String)
}

struct CommonCalculator<Number: Numeric & LosslessStringConvertible>: Calculator {
    let operators: [String: Operator<Number>]

    init(operators: [String: Operator<Number>]) {
        self.operators = operators
    }

    func evaluate(_ input: String) throws -> Number {
        let components = input.components(separatedBy: .whitespaces)
        var stackOperator = [Operator<Number>]()
        var stackOutput = [Any]()

        for component in components {
            if let op = operators[component] {
                while !stackOperator.isEmpty {
                    if let last = stackOperator.last {
                        if last.precedence >= op.precedence && (op.associativity == .left || op.associativity == .none) ||
                            last.precedence > op.precedence && op.associativity == .right
                        {
                            stackOutput.append(last as Any)
                            stackOperator.popLast()
                        } else {
                            break
                        }
                    } else {
                        throw CalculatorError.StackError("Algo error: last - nil in not empty array")
                    }
                }
                stackOperator.append(op)
            } else if let num = Number(component) {
                stackOutput.append(num as Any)
            } else {
                throw CalculatorError.IncorrectOperator("Component \(component) can not parse to operator and can not parse to <\(Number.self)>")
            }
        }

        while !stackOperator.isEmpty {
            stackOutput.append(stackOperator.last as Any)
            stackOperator.popLast()
        }

        var newStack = [Number]()

        for cmp in stackOutput {
            if let op = cmp as? Operator<Number> {
                if let rhs = newStack.last {
                    newStack.popLast()
                    if let lhs = newStack.last {
                        newStack.popLast()
                        newStack.append(try op.apply(lhs, rhs))
                    } else {
                        throw CalculatorError.IncorrectNumber("Incorrect number of operators or values")
                    }
                } else {
                    throw CalculatorError.IncorrectNumber("Incorrect number of operators or values")
                }
            } else if let num = cmp as? Number {
                newStack.append(num)
            } else {
                throw CalculatorError.IncorrectOperator("Component \(cmp) can not parse to operator and can not parse to <\(Number.self)>")
            }
        }
        if let ans = newStack.last {
            return ans
        } else {
            throw CalculatorError.IncorrectNumber("Incorrect number of operators or values")
        }
    }
}

typealias IntegerCalculator = CommonCalculator<Int>
typealias RealCalculator = CommonCalculator<Double>

// Пример испльзования
func test1<C: Calculator>(calculator type: C.Type) {
    let calculator = type.init(operators: [
        "+": Operator(precedence: 10, associativity: .left, function: +),
        "*": Operator(precedence: 20, associativity: .left, function: *),
        "-": Operator(precedence: 10, associativity: .left, function: -),
//        "/": Operator(precedence: 20, associativity: .left, function: /),
    ])

    let result = try! calculator.evaluate("2 + 2 * 2 - 2 * 2 + 2")
    print(result)
}

func test<C: Calculator>(calculator type: C.Type) {
    let calculator = type.init(operators: [
        "+": Operator(precedence: 10, associativity: .left, function: +),
        "*": Operator(precedence: 20, associativity: .left, function: *),
        "-": Operator(precedence: 10, associativity: .left, function: -),
//        "/": Operator(precedence: 20, associativity: .left, function: /),
    ])

    let result = try! calculator.evaluate("2 + 3 * 4 - 9.3 + 1")
    print(result)
}

// test Real - 4.0
test1(calculator: RealCalculator.self)
// test Integer - 4
test1(calculator: IntegerCalculator.self)
// test Real - 5.7
test(calculator: RealCalculator.self)
// test Integer - Get CalculatorError
test(calculator: IntegerCalculator.self)
