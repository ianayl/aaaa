#include <iostream>

#include "lexer/lexer.h"
#include "input/test_input.h"

int main()
{
	lexer poop = lexer(new test_input("A 1123def define"));
	std::cout << '[' << poop.get_next_lexeme().type << std::endl;
	std::cout << '[' << poop.get_next_lexeme().type << std::endl;
	std::cout << '[' << poop.get_next_lexeme().type << std::endl;
	std::cout << '[' << poop.get_next_lexeme().type << std::endl;
	// std::cout << poop.lookup_table[0]['-'] << std::endl;
	// std::cout << poop.lookup_table[5]['>'] << std::endl;
	// std::cout << poop.lookup_table[6]['5'] << std::endl;
	// std::cout << poop.lookup_table[1]['f'] << std::endl;
	// std::cout << poop.lookup_table[1]['\n'] << std::endl;
	// TODO lookup_table currently doesn't consider EOF
}
