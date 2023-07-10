#ifndef TEST_INPUT_H
#define TEST_INPUT_H

#include <string>

#include "input.h"

class test_input : public input {
private:
	std::string tmp_input;

public:
	test_input(std::string src);
	~test_input();
	char get_next();
	char peek();
	std::string print_remainder();
};

#endif
