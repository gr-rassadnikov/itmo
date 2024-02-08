// Generated from antlr/Grammar.g4 by ANTLR 4.13.1
package antlr;

import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link GrammarParser}.
 */
public interface GrammarListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link GrammarParser#file}.
	 * @param ctx the parse tree
	 */
	void enterFile(GrammarParser.FileContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#file}.
	 * @param ctx the parse tree
	 */
	void exitFile(GrammarParser.FileContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#start}.
	 * @param ctx the parse tree
	 */
	void enterStart(GrammarParser.StartContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#start}.
	 * @param ctx the parse tree
	 */
	void exitStart(GrammarParser.StartContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#rule}.
	 * @param ctx the parse tree
	 */
	void enterRule(GrammarParser.RuleContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#rule}.
	 * @param ctx the parse tree
	 */
	void exitRule(GrammarParser.RuleContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#rParse}.
	 * @param ctx the parse tree
	 */
	void enterRParse(GrammarParser.RParseContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#rParse}.
	 * @param ctx the parse tree
	 */
	void exitRParse(GrammarParser.RParseContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#inherited}.
	 * @param ctx the parse tree
	 */
	void enterInherited(GrammarParser.InheritedContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#inherited}.
	 * @param ctx the parse tree
	 */
	void exitInherited(GrammarParser.InheritedContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#param}.
	 * @param ctx the parse tree
	 */
	void enterParam(GrammarParser.ParamContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#param}.
	 * @param ctx the parse tree
	 */
	void exitParam(GrammarParser.ParamContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#synthesized}.
	 * @param ctx the parse tree
	 */
	void enterSynthesized(GrammarParser.SynthesizedContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#synthesized}.
	 * @param ctx the parse tree
	 */
	void exitSynthesized(GrammarParser.SynthesizedContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#production}.
	 * @param ctx the parse tree
	 */
	void enterProduction(GrammarParser.ProductionContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#production}.
	 * @param ctx the parse tree
	 */
	void exitProduction(GrammarParser.ProductionContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#argument}.
	 * @param ctx the parse tree
	 */
	void enterArgument(GrammarParser.ArgumentContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#argument}.
	 * @param ctx the parse tree
	 */
	void exitArgument(GrammarParser.ArgumentContext ctx);
	/**
	 * Enter a parse tree produced by the {@code tokenLex}
	 * labeled alternative in {@link GrammarParser#rLex}.
	 * @param ctx the parse tree
	 */
	void enterTokenLex(GrammarParser.TokenLexContext ctx);
	/**
	 * Exit a parse tree produced by the {@code tokenLex}
	 * labeled alternative in {@link GrammarParser#rLex}.
	 * @param ctx the parse tree
	 */
	void exitTokenLex(GrammarParser.TokenLexContext ctx);
	/**
	 * Enter a parse tree produced by the {@code skipLex}
	 * labeled alternative in {@link GrammarParser#rLex}.
	 * @param ctx the parse tree
	 */
	void enterSkipLex(GrammarParser.SkipLexContext ctx);
	/**
	 * Exit a parse tree produced by the {@code skipLex}
	 * labeled alternative in {@link GrammarParser#rLex}.
	 * @param ctx the parse tree
	 */
	void exitSkipLex(GrammarParser.SkipLexContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#term_value}.
	 * @param ctx the parse tree
	 */
	void enterTerm_value(GrammarParser.Term_valueContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#term_value}.
	 * @param ctx the parse tree
	 */
	void exitTerm_value(GrammarParser.Term_valueContext ctx);
}