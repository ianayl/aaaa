#ifndef INPUT_H
#define INPUT_H

#include <string>

class input {
public:
	/**
	 * Consume the next character
	 */
	virtual char get_next() = 0;

	/**
	 * Consume the next character
	 */
	virtual char peek() = 0;
	virtual std::string print_remainder() = 0;
	virtual ~input() {};
};

#endif
