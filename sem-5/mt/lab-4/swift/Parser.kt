import Foundation

enum GrammarException : Error {
    case Parse(mes: String = "", pos: Int = -1)
}

class Parser {
	let lexer: Lexer

    init(lexer: Lexer) {
        self.lexer = lexer
    }

    private func skip(token: Token) throws -> String {
        if lexer.token != token {
            throw GrammarException.Parse()
        }
        return try patterns[lexer.nextToken()]?.pattern ?? "error"
    }
	func parse() throws -> Int {
        try lexer.nextToken()
        return try expr()
    }
	private func Expr(null) throws Int {
switch lexer.token { 
		default: throw GrammarException.Parse()
	}
	private func Exprs(null) throws Int {
switch lexer.token { 
		default: throw GrammarException.Parse()
	}
	private func Term(null) throws Int {
switch lexer.token { 
		default: throw GrammarException.Parse()
	}
	private func Terms(null) throws Int {
switch lexer.token { 
		default: throw GrammarException.Parse()
	}
	private func Factor(null) throws Int {
switch lexer.token { 
		default: throw GrammarException.Parse()
	}
	private func Factors(null) throws Int {
switch lexer.token { 
		default: throw GrammarException.Parse()
	}
	private func Single(null) throws Int {
switch lexer.token { 
		default: throw GrammarException.Parse()
	}
	private func Num(null) throws Int {
switch lexer.token { 
		default: throw GrammarException.Parse()
	}
	}
}
