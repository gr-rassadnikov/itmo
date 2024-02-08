// Generated from antlr/Grammar.g4 by ANTLR 4.13.1
package antlr;

import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class GrammarParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, NONTERM=13, TERM=14, REG=15, STRING=16, CODE=17, 
		WS=18;
	public static final int
		RULE_file = 0, RULE_start = 1, RULE_rule = 2, RULE_rParse = 3, RULE_inherited = 4, 
		RULE_param = 5, RULE_synthesized = 6, RULE_production = 7, RULE_argument = 8, 
		RULE_rLex = 9, RULE_term_value = 10;
	private static String[] makeRuleNames() {
		return new String[] {
			"file", "start", "rule", "rParse", "inherited", "param", "synthesized", 
			"production", "argument", "rLex", "term_value"
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

	@Override
	public String getGrammarFileName() { return "Grammar.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public GrammarParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FileContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(GrammarParser.EOF, 0); }
		public StartContext start() {
			return getRuleContext(StartContext.class,0);
		}
		public List<RuleContext> rule_() {
			return getRuleContexts(RuleContext.class);
		}
		public RuleContext rule_(int i) {
			return getRuleContext(RuleContext.class,i);
		}
		public FileContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_file; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterFile(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitFile(this);
		}
	}

	public final FileContext file() throws RecognitionException {
		FileContext _localctx = new FileContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_file);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(28);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__0) {
				{
				setState(22);
				start();
				setState(24); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(23);
					rule_();
					}
					}
					setState(26); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==NONTERM || _la==TERM );
				}
			}

			setState(30);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StartContext extends ParserRuleContext {
		public TerminalNode NONTERM() { return getToken(GrammarParser.NONTERM, 0); }
		public StartContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_start; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterStart(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitStart(this);
		}
	}

	public final StartContext start() throws RecognitionException {
		StartContext _localctx = new StartContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_start);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(32);
			match(T__0);
			setState(33);
			match(NONTERM);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RuleContext extends ParserRuleContext {
		public RParseContext rParse() {
			return getRuleContext(RParseContext.class,0);
		}
		public RLexContext rLex() {
			return getRuleContext(RLexContext.class,0);
		}
		public RuleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rule; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterRule(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitRule(this);
		}
	}

	public final RuleContext rule_() throws RecognitionException {
		RuleContext _localctx = new RuleContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_rule);
		try {
			setState(41);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case NONTERM:
				enterOuterAlt(_localctx, 1);
				{
				setState(35);
				rParse();
				setState(36);
				match(T__1);
				}
				break;
			case TERM:
				enterOuterAlt(_localctx, 2);
				{
				setState(38);
				rLex();
				setState(39);
				match(T__1);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RParseContext extends ParserRuleContext {
		public TerminalNode NONTERM() { return getToken(GrammarParser.NONTERM, 0); }
		public InheritedContext inherited() {
			return getRuleContext(InheritedContext.class,0);
		}
		public SynthesizedContext synthesized() {
			return getRuleContext(SynthesizedContext.class,0);
		}
		public List<ProductionContext> production() {
			return getRuleContexts(ProductionContext.class);
		}
		public ProductionContext production(int i) {
			return getRuleContext(ProductionContext.class,i);
		}
		public RParseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rParse; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterRParse(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitRParse(this);
		}
	}

	public final RParseContext rParse() throws RecognitionException {
		RParseContext _localctx = new RParseContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_rParse);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(43);
			match(NONTERM);
			setState(45);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__5) {
				{
				setState(44);
				inherited();
				}
			}

			setState(49);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__2) {
				{
				setState(47);
				match(T__2);
				setState(48);
				synthesized();
				}
			}

			setState(51);
			match(T__3);
			setState(55);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 155648L) != 0)) {
				{
				{
				setState(52);
				production();
				}
				}
				setState(57);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(67);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__4) {
				{
				{
				setState(58);
				match(T__4);
				setState(62);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 155648L) != 0)) {
					{
					{
					setState(59);
					production();
					}
					}
					setState(64);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				}
				setState(69);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class InheritedContext extends ParserRuleContext {
		public List<ParamContext> param() {
			return getRuleContexts(ParamContext.class);
		}
		public ParamContext param(int i) {
			return getRuleContext(ParamContext.class,i);
		}
		public InheritedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inherited; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterInherited(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitInherited(this);
		}
	}

	public final InheritedContext inherited() throws RecognitionException {
		InheritedContext _localctx = new InheritedContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_inherited);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(70);
			match(T__5);
			setState(71);
			param();
			setState(76);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__6) {
				{
				{
				setState(72);
				match(T__6);
				setState(73);
				param();
				}
				}
				setState(78);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(79);
			match(T__7);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ParamContext extends ParserRuleContext {
		public TerminalNode NONTERM() { return getToken(GrammarParser.NONTERM, 0); }
		public TerminalNode TERM() { return getToken(GrammarParser.TERM, 0); }
		public ParamContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_param; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterParam(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitParam(this);
		}
	}

	public final ParamContext param() throws RecognitionException {
		ParamContext _localctx = new ParamContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_param);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(81);
			match(NONTERM);
			setState(82);
			match(T__2);
			setState(83);
			match(TERM);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SynthesizedContext extends ParserRuleContext {
		public TerminalNode TERM() { return getToken(GrammarParser.TERM, 0); }
		public SynthesizedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_synthesized; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterSynthesized(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitSynthesized(this);
		}
	}

	public final SynthesizedContext synthesized() throws RecognitionException {
		SynthesizedContext _localctx = new SynthesizedContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_synthesized);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(85);
			match(TERM);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProductionContext extends ParserRuleContext {
		public TerminalNode NONTERM() { return getToken(GrammarParser.NONTERM, 0); }
		public List<ArgumentContext> argument() {
			return getRuleContexts(ArgumentContext.class);
		}
		public ArgumentContext argument(int i) {
			return getRuleContext(ArgumentContext.class,i);
		}
		public TerminalNode TERM() { return getToken(GrammarParser.TERM, 0); }
		public TerminalNode CODE() { return getToken(GrammarParser.CODE, 0); }
		public ProductionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_production; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterProduction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitProduction(this);
		}
	}

	public final ProductionContext production() throws RecognitionException {
		ProductionContext _localctx = new ProductionContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_production);
		int _la;
		try {
			setState(103);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case NONTERM:
				enterOuterAlt(_localctx, 1);
				{
				setState(87);
				match(NONTERM);
				setState(99);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__8) {
					{
					setState(88);
					match(T__8);
					setState(89);
					argument();
					setState(94);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==T__6) {
						{
						{
						setState(90);
						match(T__6);
						setState(91);
						argument();
						}
						}
						setState(96);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					setState(97);
					match(T__9);
					}
				}

				}
				break;
			case TERM:
				enterOuterAlt(_localctx, 2);
				{
				setState(101);
				match(TERM);
				}
				break;
			case CODE:
				enterOuterAlt(_localctx, 3);
				{
				setState(102);
				match(CODE);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArgumentContext extends ParserRuleContext {
		public TerminalNode NONTERM() { return getToken(GrammarParser.NONTERM, 0); }
		public TerminalNode TERM() { return getToken(GrammarParser.TERM, 0); }
		public TerminalNode CODE() { return getToken(GrammarParser.CODE, 0); }
		public ArgumentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_argument; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterArgument(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitArgument(this);
		}
	}

	public final ArgumentContext argument() throws RecognitionException {
		ArgumentContext _localctx = new ArgumentContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_argument);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(105);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 155648L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RLexContext extends ParserRuleContext {
		public RLexContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rLex; }
	 
		public RLexContext() { }
		public void copyFrom(RLexContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class TokenLexContext extends RLexContext {
		public TerminalNode TERM() { return getToken(GrammarParser.TERM, 0); }
		public Term_valueContext term_value() {
			return getRuleContext(Term_valueContext.class,0);
		}
		public TokenLexContext(RLexContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterTokenLex(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitTokenLex(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SkipLexContext extends RLexContext {
		public TerminalNode TERM() { return getToken(GrammarParser.TERM, 0); }
		public Term_valueContext term_value() {
			return getRuleContext(Term_valueContext.class,0);
		}
		public SkipLexContext(RLexContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterSkipLex(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitSkipLex(this);
		}
	}

	public final RLexContext rLex() throws RecognitionException {
		RLexContext _localctx = new RLexContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_rLex);
		try {
			setState(113);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
			case 1:
				_localctx = new TokenLexContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(107);
				match(TERM);
				setState(108);
				match(T__10);
				setState(109);
				term_value();
				}
				break;
			case 2:
				_localctx = new SkipLexContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(110);
				match(TERM);
				setState(111);
				match(T__11);
				setState(112);
				term_value();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Term_valueContext extends ParserRuleContext {
		public TerminalNode REG() { return getToken(GrammarParser.REG, 0); }
		public TerminalNode STRING() { return getToken(GrammarParser.STRING, 0); }
		public Term_valueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_term_value; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterTerm_value(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitTerm_value(this);
		}
	}

	public final Term_valueContext term_value() throws RecognitionException {
		Term_valueContext _localctx = new Term_valueContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_term_value);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(115);
			_la = _input.LA(1);
			if ( !(_la==REG || _la==STRING) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\u0004\u0001\u0012v\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0001\u0000\u0001\u0000\u0004"+
		"\u0000\u0019\b\u0000\u000b\u0000\f\u0000\u001a\u0003\u0000\u001d\b\u0000"+
		"\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0002"+
		"\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0003\u0002"+
		"*\b\u0002\u0001\u0003\u0001\u0003\u0003\u0003.\b\u0003\u0001\u0003\u0001"+
		"\u0003\u0003\u00032\b\u0003\u0001\u0003\u0001\u0003\u0005\u00036\b\u0003"+
		"\n\u0003\f\u00039\t\u0003\u0001\u0003\u0001\u0003\u0005\u0003=\b\u0003"+
		"\n\u0003\f\u0003@\t\u0003\u0005\u0003B\b\u0003\n\u0003\f\u0003E\t\u0003"+
		"\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0005\u0004K\b\u0004"+
		"\n\u0004\f\u0004N\t\u0004\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0005\u0007]\b\u0007\n\u0007\f\u0007"+
		"`\t\u0007\u0001\u0007\u0001\u0007\u0003\u0007d\b\u0007\u0001\u0007\u0001"+
		"\u0007\u0003\u0007h\b\u0007\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0001\t\u0003\tr\b\t\u0001\n\u0001\n\u0001\n\u0000\u0000\u000b"+
		"\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0000\u0002\u0002"+
		"\u0000\r\u000e\u0011\u0011\u0001\u0000\u000f\u0010x\u0000\u001c\u0001"+
		"\u0000\u0000\u0000\u0002 \u0001\u0000\u0000\u0000\u0004)\u0001\u0000\u0000"+
		"\u0000\u0006+\u0001\u0000\u0000\u0000\bF\u0001\u0000\u0000\u0000\nQ\u0001"+
		"\u0000\u0000\u0000\fU\u0001\u0000\u0000\u0000\u000eg\u0001\u0000\u0000"+
		"\u0000\u0010i\u0001\u0000\u0000\u0000\u0012q\u0001\u0000\u0000\u0000\u0014"+
		"s\u0001\u0000\u0000\u0000\u0016\u0018\u0003\u0002\u0001\u0000\u0017\u0019"+
		"\u0003\u0004\u0002\u0000\u0018\u0017\u0001\u0000\u0000\u0000\u0019\u001a"+
		"\u0001\u0000\u0000\u0000\u001a\u0018\u0001\u0000\u0000\u0000\u001a\u001b"+
		"\u0001\u0000\u0000\u0000\u001b\u001d\u0001\u0000\u0000\u0000\u001c\u0016"+
		"\u0001\u0000\u0000\u0000\u001c\u001d\u0001\u0000\u0000\u0000\u001d\u001e"+
		"\u0001\u0000\u0000\u0000\u001e\u001f\u0005\u0000\u0000\u0001\u001f\u0001"+
		"\u0001\u0000\u0000\u0000 !\u0005\u0001\u0000\u0000!\"\u0005\r\u0000\u0000"+
		"\"\u0003\u0001\u0000\u0000\u0000#$\u0003\u0006\u0003\u0000$%\u0005\u0002"+
		"\u0000\u0000%*\u0001\u0000\u0000\u0000&\'\u0003\u0012\t\u0000\'(\u0005"+
		"\u0002\u0000\u0000(*\u0001\u0000\u0000\u0000)#\u0001\u0000\u0000\u0000"+
		")&\u0001\u0000\u0000\u0000*\u0005\u0001\u0000\u0000\u0000+-\u0005\r\u0000"+
		"\u0000,.\u0003\b\u0004\u0000-,\u0001\u0000\u0000\u0000-.\u0001\u0000\u0000"+
		"\u0000.1\u0001\u0000\u0000\u0000/0\u0005\u0003\u0000\u000002\u0003\f\u0006"+
		"\u00001/\u0001\u0000\u0000\u000012\u0001\u0000\u0000\u000023\u0001\u0000"+
		"\u0000\u000037\u0005\u0004\u0000\u000046\u0003\u000e\u0007\u000054\u0001"+
		"\u0000\u0000\u000069\u0001\u0000\u0000\u000075\u0001\u0000\u0000\u0000"+
		"78\u0001\u0000\u0000\u00008C\u0001\u0000\u0000\u000097\u0001\u0000\u0000"+
		"\u0000:>\u0005\u0005\u0000\u0000;=\u0003\u000e\u0007\u0000<;\u0001\u0000"+
		"\u0000\u0000=@\u0001\u0000\u0000\u0000><\u0001\u0000\u0000\u0000>?\u0001"+
		"\u0000\u0000\u0000?B\u0001\u0000\u0000\u0000@>\u0001\u0000\u0000\u0000"+
		"A:\u0001\u0000\u0000\u0000BE\u0001\u0000\u0000\u0000CA\u0001\u0000\u0000"+
		"\u0000CD\u0001\u0000\u0000\u0000D\u0007\u0001\u0000\u0000\u0000EC\u0001"+
		"\u0000\u0000\u0000FG\u0005\u0006\u0000\u0000GL\u0003\n\u0005\u0000HI\u0005"+
		"\u0007\u0000\u0000IK\u0003\n\u0005\u0000JH\u0001\u0000\u0000\u0000KN\u0001"+
		"\u0000\u0000\u0000LJ\u0001\u0000\u0000\u0000LM\u0001\u0000\u0000\u0000"+
		"MO\u0001\u0000\u0000\u0000NL\u0001\u0000\u0000\u0000OP\u0005\b\u0000\u0000"+
		"P\t\u0001\u0000\u0000\u0000QR\u0005\r\u0000\u0000RS\u0005\u0003\u0000"+
		"\u0000ST\u0005\u000e\u0000\u0000T\u000b\u0001\u0000\u0000\u0000UV\u0005"+
		"\u000e\u0000\u0000V\r\u0001\u0000\u0000\u0000Wc\u0005\r\u0000\u0000XY"+
		"\u0005\t\u0000\u0000Y^\u0003\u0010\b\u0000Z[\u0005\u0007\u0000\u0000["+
		"]\u0003\u0010\b\u0000\\Z\u0001\u0000\u0000\u0000]`\u0001\u0000\u0000\u0000"+
		"^\\\u0001\u0000\u0000\u0000^_\u0001\u0000\u0000\u0000_a\u0001\u0000\u0000"+
		"\u0000`^\u0001\u0000\u0000\u0000ab\u0005\n\u0000\u0000bd\u0001\u0000\u0000"+
		"\u0000cX\u0001\u0000\u0000\u0000cd\u0001\u0000\u0000\u0000dh\u0001\u0000"+
		"\u0000\u0000eh\u0005\u000e\u0000\u0000fh\u0005\u0011\u0000\u0000gW\u0001"+
		"\u0000\u0000\u0000ge\u0001\u0000\u0000\u0000gf\u0001\u0000\u0000\u0000"+
		"h\u000f\u0001\u0000\u0000\u0000ij\u0007\u0000\u0000\u0000j\u0011\u0001"+
		"\u0000\u0000\u0000kl\u0005\u000e\u0000\u0000lm\u0005\u000b\u0000\u0000"+
		"mr\u0003\u0014\n\u0000no\u0005\u000e\u0000\u0000op\u0005\f\u0000\u0000"+
		"pr\u0003\u0014\n\u0000qk\u0001\u0000\u0000\u0000qn\u0001\u0000\u0000\u0000"+
		"r\u0013\u0001\u0000\u0000\u0000st\u0007\u0001\u0000\u0000t\u0015\u0001"+
		"\u0000\u0000\u0000\r\u001a\u001c)-17>CL^cgq";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}