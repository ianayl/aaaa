#ifndef LEXEME_H
#define LEXEME_H

#include <string>

// TODO consider making lexeme types it's own class instead of enums? 
// This allows for easier customization in the future

enum lexeme_t
{
	lexeme_null = 0,
	/* Symbols */
	lexeme_lparen,          /* ( */
	lexeme_rparen,          /* ) */
 	lexeme_plus,            /* + */
 	lexeme_dash,            /* - */
 	lexeme_asterisk,        /* * */
 	lexeme_fslash,          /* / */
 	lexeme_lbrace,          /* { */
 	lexeme_rbrace,          /* } */
 	lexeme_equals,          /* = */
 	lexeme_arrow,           /* -> */
	/* Keywords */
	lexeme_define,          /* def */
	lexeme_function,        /* fn */
	/* Misc */
	lexeme_END_CONSTS,      /* End delimiter for list traversal of lexeme constants */
	lexeme_id,              /* Identifiers */
	lexeme_num_lit,         /* Number literals */
	lexeme_EOF = -1,        /* End of file */
};

const std::string lexeme_defs[] = {
	"LEXEME_NULL",          /* lol */
	"(",
	")",
	"+",
	"-",
	"*",
	"/",
	"{",
	"}",
	"=",
	"->",
	"def",
	"fn",
};

class lexeme {
public:
	lexeme_t      type;
	std::string   value;      /* Literal value read from input */

	/**
	 * Create a new lexeme
	 * 
	 * @param t      Lexeme type
	 * @param v      Literal value read from input
	 */
	lexeme(lexeme_t t, std::string v);
};

// Old concept for separating token types:
//
// enum lexeme_t
// {
// 	lexeme_null = 0,
// 	lexeme_lparen,          /* ( */
// 	lexeme_rparen,          /* ) */
// 	lexeme_plus,            /* + */
// 	lexeme_dash,            /* - */
// 	lexeme_asterisk,        /* * */
// 	lexeme_fslash,          /* / */
// 	lexeme_lbrace,          /* { */
// 	lexeme_rbrace,          /* } */
// 	lexeme_SYMBOLS_END,     /* End delimiter for list traversal of valid objects */
// 	lexeme_id,
// 	lexeme_num_lit,
// 	lexeme_keyword,
// 	lexeme_EOF = -1,        /* End of file */
// };
// 
// enum lexeme_keyw_t
// {
// 	lexeme_keyw_null,       /* lol */
// 	lexeme_keyw_define,
// 	lexeme_keyw_functron,
// 	lexeme_keyw_END,        /* End delimiter for list traversal */
// };
// 
// const std::string lexeme_keyw_def[] = {
// 	"ERR",                  /* lol */
// 	"def",
// 	"fn",
// };
// 
// 
// class lexeme {
// public:
// 	lexeme_t      type;
// 	lexeme_keyw_t keyw_t;
// 	std::string   value;      /* Literal value read from input */
// 
// 	/**
// 	 * Create a new lexeme
// 	 * 
// 	 * @param t      Lexeme type
// 	 * @param keyw_t Keyword type, only changes of type is keyword
// 	 * @param v      Literal value read from input
// 	 */
// 	lexeme(lexeme_t t, lexeme_keyw_t keyw_t, std::string v);
// 
// 	/**
// 	 * Create a new normal lexeme
// 	 * 
// 	 * @param t      Lexeme type
// 	 * @param v      Literal value read from input
// 	 */
// 	lexeme(lexeme_t t, std::string v);
// 
// 	/**
// 	 * Create a new keyword lexeme
// 	 * 
// 	 * @param keyw_t Keyword type
// 	 * @param v      Literal value read from input
// 	 */
// 	lexeme(lexeme_keyw_t keyw_t, std::string v);
// };

#endif
