#include "ast.h"

#include "../input/input.h"
#include "../input/test_input.h"
#include "../lexer/lexer.h"

int main()
{
	// ast_lit n6 = ast_lit(10);
	// ast_id  n5 = ast_id("montgomery");
	// ast_lit n4 = ast_lit(42);
	// ast_add n3 = ast_add(&n4, &n5);
	// ast_mul n2 = ast_mul(&n6, &n3);
	// ast_assign n1 = ast_assign("bartholomew", &n2);
	// ast *n = &n1; 

	//n->print();

	lexer test(new test_input("def john(0)"));
	std::cout << test.peek().value << std::endl;
	std::cout << test.peek(1).value << std::endl;
	std::cout << test.peek(2).value << std::endl;
	std::cout << test.peek(3).value << std::endl;
	std::cout << test.peek(4).value << std::endl;
	std::cout << (int) test.peek(5).value[0] << std::endl;

}
