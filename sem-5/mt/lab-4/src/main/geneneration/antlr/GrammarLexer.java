// Generated from antlr/Grammar.g4 by ANTLR 4.13.1
package antlr;

import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class GrammarLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, NONTERM=13, TERM=14, REG=15, STRING=16, CODE=17, 
		WS=18;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "T__11", "NONTERM", "TERM", "REG", "STRING", "CODE", 
			"WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'<start>'", "';'", "'->'", "':='", "'|'", "'<'", "','", "'>'", 
			"'('", "')'", "':'", "':>'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, "NONTERM", "TERM", "REG", "STRING", "CODE", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public GrammarLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "Grammar.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u0012\u0083\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002"+
		"\u0001\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002"+
		"\u0004\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002"+
		"\u0007\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002"+
		"\u000b\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e"+
		"\u0002\u000f\u0007\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011"+
		"\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0004\u0001\u0004"+
		"\u0001\u0005\u0001\u0005\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007"+
		"\u0001\b\u0001\b\u0001\t\u0001\t\u0001\n\u0001\n\u0001\u000b\u0001\u000b"+
		"\u0001\u000b\u0001\f\u0001\f\u0005\fI\b\f\n\f\f\fL\t\f\u0001\r\u0001\r"+
		"\u0005\rP\b\r\n\r\f\rS\t\r\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e"+
		"\u0005\u000eY\b\u000e\n\u000e\f\u000e\\\t\u000e\u0001\u000e\u0001\u000e"+
		"\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0005\u000fd\b\u000f"+
		"\n\u000f\f\u000fg\t\u000f\u0001\u000f\u0001\u000f\u0001\u0010\u0001\u0010"+
		"\u0001\u0010\u0001\u0010\u0004\u0010o\b\u0010\u000b\u0010\f\u0010p\u0001"+
		"\u0010\u0003\u0010t\b\u0010\u0005\u0010v\b\u0010\n\u0010\f\u0010y\t\u0010"+
		"\u0001\u0010\u0001\u0010\u0001\u0011\u0004\u0011~\b\u0011\u000b\u0011"+
		"\f\u0011\u007f\u0001\u0011\u0001\u0011\u0000\u0000\u0012\u0001\u0001\u0003"+
		"\u0002\u0005\u0003\u0007\u0004\t\u0005\u000b\u0006\r\u0007\u000f\b\u0011"+
		"\t\u0013\n\u0015\u000b\u0017\f\u0019\r\u001b\u000e\u001d\u000f\u001f\u0010"+
		"!\u0011#\u0012\u0001\u0000\u0007\u0001\u0000az\u0003\u000009AZaz\u0001"+
		"\u0000AZ\u0003\u0000\n\n\r\r\'\'\u0001\u0000\"\"\u0004\u0000##<<>>}}\u0003"+
		"\u0000\t\n\r\r  \u008c\u0000\u0001\u0001\u0000\u0000\u0000\u0000\u0003"+
		"\u0001\u0000\u0000\u0000\u0000\u0005\u0001\u0000\u0000\u0000\u0000\u0007"+
		"\u0001\u0000\u0000\u0000\u0000\t\u0001\u0000\u0000\u0000\u0000\u000b\u0001"+
		"\u0000\u0000\u0000\u0000\r\u0001\u0000\u0000\u0000\u0000\u000f\u0001\u0000"+
		"\u0000\u0000\u0000\u0011\u0001\u0000\u0000\u0000\u0000\u0013\u0001\u0000"+
		"\u0000\u0000\u0000\u0015\u0001\u0000\u0000\u0000\u0000\u0017\u0001\u0000"+
		"\u0000\u0000\u0000\u0019\u0001\u0000\u0000\u0000\u0000\u001b\u0001\u0000"+
		"\u0000\u0000\u0000\u001d\u0001\u0000\u0000\u0000\u0000\u001f\u0001\u0000"+
		"\u0000\u0000\u0000!\u0001\u0000\u0000\u0000\u0000#\u0001\u0000\u0000\u0000"+
		"\u0001%\u0001\u0000\u0000\u0000\u0003-\u0001\u0000\u0000\u0000\u0005/"+
		"\u0001\u0000\u0000\u0000\u00072\u0001\u0000\u0000\u0000\t5\u0001\u0000"+
		"\u0000\u0000\u000b7\u0001\u0000\u0000\u0000\r9\u0001\u0000\u0000\u0000"+
		"\u000f;\u0001\u0000\u0000\u0000\u0011=\u0001\u0000\u0000\u0000\u0013?"+
		"\u0001\u0000\u0000\u0000\u0015A\u0001\u0000\u0000\u0000\u0017C\u0001\u0000"+
		"\u0000\u0000\u0019F\u0001\u0000\u0000\u0000\u001bM\u0001\u0000\u0000\u0000"+
		"\u001dT\u0001\u0000\u0000\u0000\u001f_\u0001\u0000\u0000\u0000!j\u0001"+
		"\u0000\u0000\u0000#}\u0001\u0000\u0000\u0000%&\u0005<\u0000\u0000&\'\u0005"+
		"s\u0000\u0000\'(\u0005t\u0000\u0000()\u0005a\u0000\u0000)*\u0005r\u0000"+
		"\u0000*+\u0005t\u0000\u0000+,\u0005>\u0000\u0000,\u0002\u0001\u0000\u0000"+
		"\u0000-.\u0005;\u0000\u0000.\u0004\u0001\u0000\u0000\u0000/0\u0005-\u0000"+
		"\u000001\u0005>\u0000\u00001\u0006\u0001\u0000\u0000\u000023\u0005:\u0000"+
		"\u000034\u0005=\u0000\u00004\b\u0001\u0000\u0000\u000056\u0005|\u0000"+
		"\u00006\n\u0001\u0000\u0000\u000078\u0005<\u0000\u00008\f\u0001\u0000"+
		"\u0000\u00009:\u0005,\u0000\u0000:\u000e\u0001\u0000\u0000\u0000;<\u0005"+
		">\u0000\u0000<\u0010\u0001\u0000\u0000\u0000=>\u0005(\u0000\u0000>\u0012"+
		"\u0001\u0000\u0000\u0000?@\u0005)\u0000\u0000@\u0014\u0001\u0000\u0000"+
		"\u0000AB\u0005:\u0000\u0000B\u0016\u0001\u0000\u0000\u0000CD\u0005:\u0000"+
		"\u0000DE\u0005>\u0000\u0000E\u0018\u0001\u0000\u0000\u0000FJ\u0007\u0000"+
		"\u0000\u0000GI\u0007\u0001\u0000\u0000HG\u0001\u0000\u0000\u0000IL\u0001"+
		"\u0000\u0000\u0000JH\u0001\u0000\u0000\u0000JK\u0001\u0000\u0000\u0000"+
		"K\u001a\u0001\u0000\u0000\u0000LJ\u0001\u0000\u0000\u0000MQ\u0007\u0002"+
		"\u0000\u0000NP\u0007\u0001\u0000\u0000ON\u0001\u0000\u0000\u0000PS\u0001"+
		"\u0000\u0000\u0000QO\u0001\u0000\u0000\u0000QR\u0001\u0000\u0000\u0000"+
		"R\u001c\u0001\u0000\u0000\u0000SQ\u0001\u0000\u0000\u0000TZ\u0005\'\u0000"+
		"\u0000UY\b\u0003\u0000\u0000VW\u0005\\\u0000\u0000WY\u0005\'\u0000\u0000"+
		"XU\u0001\u0000\u0000\u0000XV\u0001\u0000\u0000\u0000Y\\\u0001\u0000\u0000"+
		"\u0000ZX\u0001\u0000\u0000\u0000Z[\u0001\u0000\u0000\u0000[]\u0001\u0000"+
		"\u0000\u0000\\Z\u0001\u0000\u0000\u0000]^\u0005\'\u0000\u0000^\u001e\u0001"+
		"\u0000\u0000\u0000_e\u0005\"\u0000\u0000`d\b\u0004\u0000\u0000ab\u0005"+
		"\\\u0000\u0000bd\u0005\"\u0000\u0000c`\u0001\u0000\u0000\u0000ca\u0001"+
		"\u0000\u0000\u0000dg\u0001\u0000\u0000\u0000ec\u0001\u0000\u0000\u0000"+
		"ef\u0001\u0000\u0000\u0000fh\u0001\u0000\u0000\u0000ge\u0001\u0000\u0000"+
		"\u0000hi\u0005\"\u0000\u0000i \u0001\u0000\u0000\u0000jk\u0005#\u0000"+
		"\u0000kl\u0005<\u0000\u0000lw\u0001\u0000\u0000\u0000mo\b\u0005\u0000"+
		"\u0000nm\u0001\u0000\u0000\u0000op\u0001\u0000\u0000\u0000pn\u0001\u0000"+
		"\u0000\u0000pq\u0001\u0000\u0000\u0000qs\u0001\u0000\u0000\u0000rt\u0003"+
		"!\u0010\u0000sr\u0001\u0000\u0000\u0000st\u0001\u0000\u0000\u0000tv\u0001"+
		"\u0000\u0000\u0000un\u0001\u0000\u0000\u0000vy\u0001\u0000\u0000\u0000"+
		"wu\u0001\u0000\u0000\u0000wx\u0001\u0000\u0000\u0000xz\u0001\u0000\u0000"+
		"\u0000yw\u0001\u0000\u0000\u0000z{\u0005>\u0000\u0000{\"\u0001\u0000\u0000"+
		"\u0000|~\u0007\u0006\u0000\u0000}|\u0001\u0000\u0000\u0000~\u007f\u0001"+
		"\u0000\u0000\u0000\u007f}\u0001\u0000\u0000\u0000\u007f\u0080\u0001\u0000"+
		"\u0000\u0000\u0080\u0081\u0001\u0000\u0000\u0000\u0081\u0082\u0006\u0011"+
		"\u0000\u0000\u0082$\u0001\u0000\u0000\u0000\u000b\u0000JQXZcepsw\u007f"+
		"\u0001\u0006\u0000\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}