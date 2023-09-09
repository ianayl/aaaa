#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

class parser {
public:
	ast *epsilon = new _ast_epsilon();
	virtual ast* parse() = 0;
	// ~parser() {
	// 	operator delete(epsilon);
	// }
};

#endif
