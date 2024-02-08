// Generated from antlr/MathExpr.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link MathExprParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface MathExprVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link MathExprParser#let}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLet(MathExprParser.LetContext ctx);
	/**
	 * Visit a parse tree produced by the {@code newState}
	 * labeled alternative in {@link MathExprParser#state}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNewState(MathExprParser.NewStateContext ctx);
	/**
	 * Visit a parse tree produced by the {@code exprInt}
	 * labeled alternative in {@link MathExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprInt(MathExprParser.ExprIntContext ctx);
	/**
	 * Visit a parse tree produced by the {@code exprCnk}
	 * labeled alternative in {@link MathExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprCnk(MathExprParser.ExprCnkContext ctx);
	/**
	 * Visit a parse tree produced by the {@code exprAddSub}
	 * labeled alternative in {@link MathExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprAddSub(MathExprParser.ExprAddSubContext ctx);
	/**
	 * Visit a parse tree produced by the {@code exprVar}
	 * labeled alternative in {@link MathExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprVar(MathExprParser.ExprVarContext ctx);
	/**
	 * Visit a parse tree produced by the {@code exprParens}
	 * labeled alternative in {@link MathExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprParens(MathExprParser.ExprParensContext ctx);
	/**
	 * Visit a parse tree produced by the {@code exprMulDiv}
	 * labeled alternative in {@link MathExprParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprMulDiv(MathExprParser.ExprMulDivContext ctx);
}