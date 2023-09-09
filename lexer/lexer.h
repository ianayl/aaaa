#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <limits>

#include "lexeme.h"
#include "../input/input.h"

/*
 * Constants dpceclaration
 */

/* State to reject a token */
const int _lexer_reject_state  = std::numeric_limits<int>::max();
// TODO make each state an object instead of relying on jank moves like this?
// But classes will be hard to store in plaintext, that's a bit of a problem.

/* 
 * Range of characters accepted, currently 2^8 for basic char support.
 *
 * The current idea is to use four 256 sized vals to represent UTF chars.
 */
const int LEXER_CHAR_RANGE = 256;

/* All characters considered whitespace */
const char LEXER_WHITESPACE_CHARS[] = {
	' ', '\t',
};

class lexer {
private:
	/* Buffer for peeking */
	std::vector<lexeme> buffer;
	input* input_src = nullptr;

	/* lookup_table[<current state>][<input char>] */
	int** lookup_table = nullptr;


public:
	/**
	 * Fetch a single lexeme from the input source
	 */
	lexeme get_next_lexeme();
	/* 
	 * Construct a new lexer and initialize the lookup table used to lex
	 *
	 * @param src The input source to use for the lexer
	 */
	lexer(input *src);
	~lexer();

	/**
	 * Return the next lookahead-th token without consuming it
	 */
	lexeme peek(int lookahead = 0);

	/**
	 * Return the next token and consume the token
	 */
	lexeme consume(int lookahead = 0);
};

// TODO should these be put as private functions? where do util functions go?

/* Checks if a char is a valid intermediate id character */
bool _lexer_is_valid_id_ch(char c);

/* Checks if a char is a valid starting id character */
bool _lexer_is_valid_starting_id_ch(char c);

#endif
