#include <iostream>
#include "test_input.h"

test_input::test_input(std::string src)
{
	this->tmp_input = src;
}

char test_input::get_next()
{
	if (tmp_input.length() == 0) return '\0';
	char res = tmp_input[0];
	tmp_input.erase(0, 1);
	return res;
}

char test_input::peek()
{
	if (tmp_input.length() == 0) return '\0';
	return this->tmp_input[0];
}

test_input::~test_input()
{
}

std::string test_input::print_remainder()
{
	return tmp_input;
}
