#ifndef LEXEME_H
#define LEXEME_H

#include <string>

/*
 * lexeme.h - Describes what lexemes look like
 */

/* 
 * The number of characters the program accepts, e.g.:
 * - 256 for 2^8 characters in ASCII
 * - up to 2^31 characters for UTF-8
 * Although I suppose this shouldn't matter, we should just stick with
 * 256 states as all chars are comprised of some number of bytes
 */
#define NUM_CHARS 256

#define NUM_KEYWORDS 4
#define NUM_LEXEMES 7

enum lexeme_type {
	lexeme_id,
	/* keywords */
	lexeme_let,
	lexeme_lettuce,
	lexeme_pub,
	lexeme_i32,
	/* multi-character literals */
	lexeme_num,
	/* symbols */
	lexeme_lparen,
	lexeme_rparen,
};
  
class lexeme {
private:
	std::string val;
public:
};

#endif
