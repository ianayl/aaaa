/*
 * ast.cpp: Implementation code for ast.h
 */

#include "ast.h"

void ast::print()
{
	ast_print tmp = ast_print();
	tmp.traverse(this);
	// this->accept(&tmp);
}

/*
 * AST NODE TEMPLATE DEFINITIONS
 */

template<class CRTP>
void* ast_tmpl<CRTP>::accept(ast_traversal *t)
{
	return t->visit(static_cast<CRTP*>(this));
}

template<typename CRTP>
ast_binop_tmpl<CRTP>::ast_binop_tmpl(ast *lhs, ast *rhs)
{
	this->lhs = lhs; this->rhs = rhs;
}

/*
 * PRECISE AST NODE DEFINITIONS
 */

/*
 * Definitions for simple AST node types
 */
_ast_epsilon::_ast_epsilon() { } // TODO do i need this?
ast_id::ast_id(std::string id) { this->id = id; }
ast_lit::ast_lit(int val) { this->val = val; }

/*
 * Definitions for binary operations
 */
ast_add::ast_add(ast *lhs, ast *rhs) : ast_binop_tmpl(lhs, rhs) { };
ast_sub::ast_sub(ast *lhs, ast *rhs) : ast_binop_tmpl(lhs, rhs) { };
ast_mul::ast_mul(ast *lhs, ast *rhs) : ast_binop_tmpl(lhs, rhs) { };
ast_div::ast_div(ast *lhs, ast *rhs) : ast_binop_tmpl(lhs, rhs) { };
ast_exp::ast_exp(ast *lhs, ast *rhs) : ast_binop_tmpl(lhs, rhs) { };
// This is dumb I hate header files... what even was the point of this?

/*
 * Definitions for more complex AST node types
 */
ast_assign::ast_assign(std::string id, ast *eval) { this->id = id; this->eval = eval; }
ast_define::ast_define(std::string id, ast *eval) { this->id = id; this->eval = eval; }

/*
 * DEFINITIONS FOR AST_PRINT
 */
ast_print::ast_print(int initial_indent_lvl) { this->indent_lvl = initial_indent_lvl; }

void* ast_print::visit(ast_id *n)
{
	for (int i = 0; i < indent_lvl; i++) std::cout << "   ";
	std::cout << "AST Identifier: " << n->id << std::endl;
	return 0; 
}

void* ast_print::visit(_ast_epsilon *n)
{
	for (int i = 0; i < indent_lvl; i++) std::cout << "   ";
	std::cout << "AST EPSILON: " << std::endl;
	return 0; 
}

void* ast_print::visit(ast_lit *n)
{
	for (int i = 0; i < indent_lvl; i++) std::cout << "   ";
	std::cout << "AST Literal Value: " << n->val << std::endl;
	return 0; 
} 

template<class ast_type>
void ast_print::_ast_print_visit_binop_children(ast_type *n)
{
	indent_lvl ++;
	n->lhs->accept(this);
	n->rhs->accept(this);
	indent_lvl --;
}

// TODO this could be smarter: Figure out how
void* ast_print::visit(ast_add *n)
{
	for (int i = 0; i < indent_lvl; i++) std::cout << "   ";
	std::cout << "AST Addition (+)" << std::endl;
	this->_ast_print_visit_binop_children(n);
	return 0; 
} 

void* ast_print::visit(ast_sub *n)
{
	for (int i = 0; i < indent_lvl; i++) std::cout << "   ";
	std::cout << "AST Subtraction (-)" << std::endl;
	this->_ast_print_visit_binop_children(n);
	return 0; 
} 

void* ast_print::visit(ast_mul *n)
{
	for (int i = 0; i < indent_lvl; i++) std::cout << "   ";
	std::cout << "AST Multiplication (*)" << std::endl;
	this->_ast_print_visit_binop_children(n);
	return 0; 
} 

void* ast_print::visit(ast_div *n)
{
	for (int i = 0; i < indent_lvl; i++) std::cout << "   ";
	std::cout << "AST Division (/)" << std::endl;
	this->_ast_print_visit_binop_children(n);
	return 0; 
} 

void* ast_print::visit(ast_exp *n)
{
	for (int i = 0; i < indent_lvl; i++) std::cout << "   ";
	std::cout << "AST Exponentiation (^)" << std::endl;
	this->_ast_print_visit_binop_children(n);
	return 0; 
} 

void* ast_print::visit(ast_assign *n)
{
	for (int i = 0; i < indent_lvl; i++) std::cout << "   ";
	std::cout << "AST Assignment (=): " << n->id << std::endl;
	indent_lvl ++;
	n->eval->accept(this);
	indent_lvl --;
	return 0; 
} 

void* ast_print::visit(ast_define *n)
{
	for (int i = 0; i < indent_lvl; i++) std::cout << "   ";
	std::cout << "AST Define (=): " << n->id << std::endl;
	indent_lvl ++;
	n->eval->accept(this);
	indent_lvl --;
	return 0; 
} 

template<class CRTP, typename result_t>
result_t ast_traversal_tmpl<CRTP, result_t>::traverse(ast *n)
{
	return static_cast<result_t>(n->accept(static_cast<CRTP*>(this)));
}
