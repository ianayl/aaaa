#include "ast.h"

int main()
{
	ast_lit n6 = ast_lit(10);
	ast_id  n5 = ast_id("montgomery");
	ast_lit n4 = ast_lit(42);
	ast_add n3 = ast_add(&n4, &n5);
	ast_mul n2 = ast_mul(&n6, &n3);
	ast_assign n1 = ast_assign("bartholomew", &n2);
	ast *n = &n1; 

	n->print();
}
