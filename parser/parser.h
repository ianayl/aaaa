#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "../lexer/lexer.h"

class parser {
public:
	parser(lexer *l);
	ast* parse();
};

#endif
