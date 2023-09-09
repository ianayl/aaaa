#include "recdec_parser.h"

// recdec_parser::recdec_parser(lexer *l)
// {
// 	input = l;
// }


lexeme recdec_parser::peek(int lookahead)
{
	if (input.size() <= lookahead)
		return lexeme(lexeme_null, "");
	return input[lookahead];
}

lexeme recdec_parser::consume(int lookahead)
{
	if (input.size() <= lookahead)
		return lexeme(lexeme_null, "");
	lexeme tmp = input[lookahead];
	input.erase(input.begin(), input.begin() + lookahead);
	return tmp;
}

recdec_parser::recdec_parser()
{
	input.push_back(lexeme(lexeme_num_lit, "2"));
	input.push_back(lexeme(lexeme_plus, "+"));
	input.push_back(lexeme(lexeme_num_lit, "2"));
}

ast* recdec_parser::parse()
{
	return nullptr;
}

ast* recdec_parser::parse_stmt()
{
	/* Statement  ::= Define '\n' | Expression '\n' */
	/* Define     ::= 'def' id '=' Expression */
	if (peek().type == lexeme_define) {
		// TODO parse define
		return nullptr;
	/* Statement  ::= Expression '\n' */
	} else return parse_expr();
}

ast* recdec_parser::parse_expr()
{
	/* Expression ::= id '=' Expression */
	if (peek(0).type == lexeme_id && peek(1).type == lexeme_equals) {
		std::string id = peek(0).value;
		consume(1);
		ast *expr = parse_expr();
		if (expr == nullptr) return nullptr; /* TODO handle errors */
		return new ast_assign(id, expr);
	/* Expression ::= Add */
	} else return parse_add();
}

ast* recdec_parser::parse_add()
{
	/* Add ::= Mul Add' */
	ast *mul = parse_mul();
	if (mul == nullptr) return nullptr; /* TODO handle errors */
	ast *addp = parse_addp();
	if (addp == nullptr) return nullptr; /* TODO handle errors */
	else if (addp == epsilon) return mul;
	else {
	}
}

ast* recdec_parser::parse_addp()
{
	/* Add' ::= '+' Mul Add' */
	if (peek().type == lexeme_plus) 
	ast *mul = parse_mul();
	if (mul == nullptr) return nullptr; /* TODO handle errors */
	ast *addp = parse_addp();
	if (addp == nullptr) return nullptr; /* TODO handle errors */
	else if (addp == epsilon) return mul;
	else return new ast_add(mul, addp);
}
