#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "lexeme.h"

/* 
 * lexer.h - tokenizes based on a config file of all valid tokens
 */

/*
 * Idea:
 * - reads keywords from config file
 * - generates 2d array (table) from keywords in config file
 *   - look for similar words
 *     - states are negative, positive states is acceptancea and the lexeme_type
 *     - basically upon reading a word, walk the existing table
 *       - if I miss on the existing table, for every remaining char add a new
 *         state 
 *       - if it's the same string: complain and die
 *     - time complexity O(n)?
 * - it goes: table[current state][input token]
 * - unicode okay: treat unicode chars as multiple characters: you can still
 *   handle them in the same space as ascii albeit 3 more lookups at worst case.
 *   that's fine, that's still like O(1)
 */

class lexer {
private:
	int** lookup_table;

public:
	/**
	 * Constructs a lexer and builds the lookup table
	 *
	 * @param config_file The name of the configuration file to read keywords from
	 */
	lexer(std::string config_file);

	/**
	 * Rebuilds the lexing table 
	 *
	 * @param config_file The name of the configuration file to read keywords from
	 */
	void rebuild(std::string config_file);

	/**
	 * Lexes based on the current lexing table
	 */
	std::vector<lexeme> lex();
};

#endif
