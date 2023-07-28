#ifndef RECDEC_PARSER_H
#define RECDEC_PARSER_H

#include "../parser.h"

class recdec_parser : public parser {
public:
	recdec_parser(lexer *l);
};

#endif
