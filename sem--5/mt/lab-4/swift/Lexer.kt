import Foundation

enum Token: Int {
	case EOF
	case PLUS
	case MINUS
	case DIV
	case MUL
	case OPENBR
	case CLOSEBR
	case NUM
}

let patterns: [Token: NSRegularExpression] = [
	.EOF: try! NSRegularExpression(pattern: "-1"), 
	.PLUS: try! NSRegularExpression(pattern: "0"), 
	.MINUS: try! NSRegularExpression(pattern: "1"), 
	.DIV: try! NSRegularExpression(pattern: "2"), 
	.MUL: try! NSRegularExpression(pattern: "3"), 
	.OPENBR: try! NSRegularExpression(pattern: "4"), 
	.CLOSEBR: try! NSRegularExpression(pattern: "5"), 
	.NUM: try! NSRegularExpression(pattern: "6"), 
]
class Lexer {
    private let skipSmbls = try! NSRegularExpression(pattern:  "[ \n\r\t]")
    private var current = 0
    private let input: String
    
    
    init(input: String) {
        self.input = input
    }
    
    var token = Token.EOF
    
    func nextToken() throws -> Token {
        if current >= input.count {
            return Token.EOF
        }
        
        let range = NSRange(location: current, length: input.count - current)
        
        guard let match = patterns
            .compactMap({ $0.value.firstMatch(in: input, range: range) })
            .first(where: { $0.range.location == current }) else {
            return Token.EOF
        }
        
        current = match.range.upperBound
        token = Token(rawValue: match.range.lowerBound)!
        return token
    }
}
