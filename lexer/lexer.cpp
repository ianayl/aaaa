#include "lexer.h"
#include <array>
#include <algorithm>
#include <iostream>
#include <exception>
#include <iterator>

int _lexer_id_state;        /* Reserved state for identifiers */
int _lexer_num_lit_state;   /* Reserved state for number literals */

/**
 * Insert transitions into a state that corresponds to a valid identifier
 *
 * @param dest The state to insert into/modify
 * @param is_starting Is a new identifier possible from the current state? If set
 *        to true, invalid characters to start an id will not be inserted 
 */
void _lexer_insert_id_transitions(std::array<int, LEXER_CHAR_RANGE> *dest,
								  bool is_starting = false)
{
	for (char c = 'A'; c <= 'Z'; c++) (*dest)[c] = -_lexer_id_state;
	for (char c = 'a'; c <= 'z'; c++) (*dest)[c] = -_lexer_id_state;
	if (!is_starting)    /* Cannot start an identifier with numbers */
		for (char c = '0'; c <= '9'; c++) (*dest)[c] = -_lexer_id_state;
	/* Identifiers can have '_' */
	(*dest)['_'] = -_lexer_id_state;
}

/**
 * Insert transitions into a state that corresponds to a valid number literal
 *
 * @param dest The state to insert into/modify
 * @param is_starting Is a new number literal possible from the current state? 
 *		  If set to true, invalid characters to start a num lit will not be inserted 
 */
void _lexer_insert_num_lit_transitions(std::array<int, LEXER_CHAR_RANGE> *dest,
								  	   bool is_starting = false)
{
	for (char c = '0'; c <= '9'; c++) (*dest)[c] = -_lexer_num_lit_state;
}

/**
 * Insert transitions into a state to ignore whitespace characters
 *
 * @param dest The state to insert into/modify
 * @param current_state The number that corresponds to the current state
 */
void _lexer_ignore_whitespace(std::array<int, LEXER_CHAR_RANGE> *dest,
							  int current_state)
{
	for (const char *c = std::begin(LEXER_WHITESPACE_CHARS);
		 c != std::end(LEXER_WHITESPACE_CHARS); ++c) {
		(*dest)[*c] = -current_state;
	}
}

lexer::lexer(input *src)
{
	this->input_src = src;

	/*
	 * NOTE ON STATES:
	 * - Positive states are ACCEPTANCE states: their states are the value of
	 *   the lexeme_t the current lexeme is
	 * - Negative states are TEMPORARY states: these are states that represent
	 *   tokens still being built. This is why states are referred to with
	 *   NEGATIVES in the front in the following code.
	 * - State 0 is the beginning state: All acceptances come back to state 0
	 */

	/*
	 * Constructing the lookup_table states:
	 */
	std::vector<std::array<int, LEXER_CHAR_RANGE>> states; /* Temporary storage for state machine transitions */

	/* Construct the identifier state */
	_lexer_id_state = states.size() + 1;          /* Supposed to get the id of the future state */
	std::array<int, LEXER_CHAR_RANGE> state_id;   /* Template state meant to represent an intermediate id state */
	state_id.fill(lexeme_id);                     /* If any character other than id characters are seen, create an id lexeme */
	_lexer_insert_id_transitions(&state_id);
	states.push_back(state_id);

	/* Construct the number literal state -- ASSUMING lexer_num_lit_state = 2 */
	_lexer_num_lit_state = states.size() + 1;          /* Supposed to get the id of the future state */
	std::array<int, LEXER_CHAR_RANGE> state_num_lit;   /* Template array meant to represent an intermediate num_lit state */
	state_num_lit.fill(lexeme_num_lit);                /* If any character other than num_lit characters are seen, create a num_lit lexeme */
	_lexer_insert_num_lit_transitions(&state_num_lit);
	states.push_back(state_num_lit);

	/* Construct state 0 - state 0 constructed last so _lexer_id_state etc. is populated first */
	std::array<int, LEXER_CHAR_RANGE> state_0; /* State representing the initial state */
	state_0.fill(_lexer_reject_state);
	_lexer_insert_id_transitions(&state_0, true);
	_lexer_insert_num_lit_transitions(&state_0);
	_lexer_ignore_whitespace(&state_0, 0);
	states.insert(states.begin(), state_0);

	/* Construct all the other states based on the lexemes provided */
	int num_states = states.size() - 1; /* Id of the last inserted state */
	for (int t = lexeme_null + 1; t < lexeme_END_CONSTS; t++) {
		int curr_state = 0;       /* Current state that is being traversed */
		bool is_valid_id = true;  /* Is the lexeme, up to the current character, a valid identifier? */

		std::string::const_iterator lexeme_it = lexeme_defs[t].begin();
		is_valid_id = is_valid_starting_id_char(*lexeme_it);  /* Check if this lexeme can even be an identifier */
		while (lexeme_it != lexeme_defs[t].end()) {
			if (is_valid_id) is_valid_id = is_valid_id_char(*lexeme_it);

			std::array<int, LEXER_CHAR_RANGE> next_state;
			/* 
			 * If current state can either be a potential keyword or a potential
			 * id, then lexing table does not handle this combination of characters
			 * yet. Add the new transition, but preserve both keyword states and
			 * id states:
			 */
			if (is_valid_id && 
				(states[curr_state][*lexeme_it] == -_lexer_id_state ||
				 states[curr_state][*lexeme_it] > 0)) {

				if ((lexeme_it + 1) == lexeme_defs[t].end()) {
					next_state.fill(t);   /* Accept everything */
					_lexer_insert_id_transitions(&next_state);  /* ... But if I get an id character, it's an id again */
				} else next_state = state_id; /* Otherwise state is a normal id state */

				states.push_back(next_state);
				states[curr_state][*lexeme_it] = -(++num_states);  /* Create transition to new state */
				curr_state = num_states;
				lexeme_it ++;
			/* 
			 * If current state rejects, then lexing table does not handle this
			 * combination of characters yet. Add the new transition:
			 */
			// TODO this can technically be simplified since _lexer_reject_state > 0 anyways
			} else if (states[curr_state][*lexeme_it] > 0 ||
					   states[curr_state][*lexeme_it] == _lexer_reject_state) {
				/*
				 * Have we reached the end of our lexeme? Make a state for acceptance
				 *
				 * An entire acceptance state is created instead of just changing
				 * the current state's value to accept when encountering the char,
				 * because lexemes may overlap: some lexemes may be the prefix to
				 * other lexemes.
				 */
				if ((lexeme_it + 1) == lexeme_defs[t].end()) next_state.fill(t); /* ... accept token */
				else next_state.fill(_lexer_reject_state); /* ... or reject all and keep going */

				states.push_back(next_state);
				states[curr_state][*lexeme_it] = -(++num_states);  /* Create transition to new state */
				curr_state = num_states;
				lexeme_it ++;

			/* 
			 * If current state is another transition, then another word might share
			 * the same prefix. Follow the transition.
			 */
			} else if (states[curr_state][*lexeme_it] < 0) {
				curr_state = -states[curr_state][*lexeme_it];
				lexeme_it ++;

			} else {
				std::cout << *lexeme_it << " " << std::to_string(states[curr_state][*lexeme_it]) << " " << curr_state << std::endl;
				throw new std::logic_error("Error building lexing table: Bad transition state "
										   + std::to_string(states[curr_state][*lexeme_it]));
			}
		}
	}

	/* States generation finished. Fill out the lookup table: */
	lookup_table = new int*[states.size()];
	for (int i = 0; i < states.size(); i++) {
		lookup_table[i] = new int[LEXER_CHAR_RANGE];
		std::copy(states[i].begin(), states[i].end(), lookup_table[i]);
	}
	
}

lexer::~lexer()
{
	if (this->lookup_table != nullptr) delete lookup_table;
	if (this->input_src != nullptr) delete input_src;
}

bool is_valid_id_char(char c)
{
	if ((c >= 'A' && c <= 'Z') ||
		(c >= 'a' && c <= 'z') ||
		(c >= '0' && c <= '9') ||
		(c == '_'))
		return true;
	else return false;
}

bool is_valid_starting_id_char(char c)
{
	if ((c >= 'A' && c <= 'Z') ||
		(c >= 'a' && c <= 'z') ||
		(c == '_'))
		return true;
	else return false;
}

lexeme lexer::get_next_lexeme()
{
	int state = 0; 
	std::string buffer = "";
	while (state <= 0) {
		/* If the state is a transition state, add the character to buffer*/
		if (this->lookup_table[-state][input_src->peek()] < 0)
			buffer += input_src->peek();
		state = this->lookup_table[-state][input_src->peek()];   /* Go to the next state */
		if (state <= 0) input_src->get_next();   /* Consume the next char if next state is a transition */
	}
	return lexeme((lexeme_t) state, buffer);
}
