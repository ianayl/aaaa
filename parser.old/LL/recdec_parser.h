#ifndef RECDEC_PARSER_H
#define RECDEC_PARSER_H

#include "../parser.h"
#include "../../lexer/lexer.h"
#include <vector>

class recdec_parser : public parser {
	// lexer *input;
	std::vector<lexeme> input;

	ast* parse_stmt();
	ast* parse_expr();
	ast* parse_add();
	ast* parse_addp();
	ast* parse_mul();
	ast* parse_mulp();

	lexeme peek(int lookahead = 0);
	lexeme consume(int lookahead = 0);
public:
	// recdec_parser(lexer *l);
	recdec_parser();
	ast* parse();
};

#endif
