#ifndef AST_H
#define AST_H

#include <string>

// enum ast_t
// {
// 	ast_null = 0,
// 	ast_id,
// 	ast_lit,
// 	ast_add,
// 	ast_sub,
// 	ast_mul,
// 	ast_div,
// 	ast_exp,
// 	ast_assign,
// 	ast_define,
// };

/**
 * A visitor pattern representing one tree-walk traversal of the AST -- useful
 * for e.g. AST optimization, type checking, or straight tree-walk interpretation
 */
class ast_traversal {
public:
	virtual int visit(class ast_id *n)     = 0;
	virtual int visit(class ast_lit *n)    = 0;
	virtual int visit(class ast_add *n)    = 0;
	virtual int visit(class ast_sub *n)    = 0;
	virtual int visit(class ast_mul *n)    = 0;
	virtual int visit(class ast_div *n)    = 0;
	virtual int visit(class ast_exp *n)    = 0;
	virtual int visit(class ast_assign *n) = 0;
	virtual int visit(class ast_define *n) = 0;
};

/**
 * Base AST class
 */
class ast {
public:
	// ast_t type;
	/**
	 * Travel the current AST node using the provided traversal
	 * @param t Traversal object used to travel current node
	 */
	virtual int accept(class ast_traversal *t) = 0;
};

/*
 * AST node definitions
 */
// TODO: Consider: should all AST function definiitons really be in the header?

/**
 * Helper template for constructing AST nodes with a builtin visitor accept function
 */
template<class CRTP>
class ast_tmpl {
public:
	int accept(ast_traversal *t) { return t->visit(static_cast<CRTP*>(this)); }
};

/* AST node representing identifiers */
class ast_id : ast_tmpl<ast_id> {
public:
	std::string id; 
	ast_id(std::string id) { this->id = id; }
};

/* AST node representing literal values */
class ast_lit : ast_tmpl<ast_lit> {
public:
	int val; 
	ast_lit(int val) { this->val = val; }
};

/**
 * Helper template for representing binary operation AST nodes
 */
template<typename CRTP>   /* Curiously repeating template pattern */
class ast_binop_tmpl : public ast_tmpl<CRTP> {
public:
	ast *lhs, *rhs;
	ast_binop_tmpl(ast *lhs, ast *rhs) { this->lhs = lhs; this->rhs = rhs; }
};

/* AST node representing addition */
class ast_add : public ast_binop_tmpl<ast_add> { public: ast_add(ast *lhs, ast *rhs) : ast_binop_tmpl(lhs, rhs) { } };
/* AST node representing subtraction */
class ast_sub : public ast_binop_tmpl<ast_sub> { public: ast_sub(ast *lhs, ast *rhs) : ast_binop_tmpl(lhs, rhs) { } };
/* AST node representing multiplication */
class ast_mul : public ast_binop_tmpl<ast_mul> { public: ast_mul(ast *lhs, ast *rhs) : ast_binop_tmpl(lhs, rhs) { } };
/* AST node representing division */
class ast_div : public ast_binop_tmpl<ast_div> { public: ast_div(ast *lhs, ast *rhs) : ast_binop_tmpl(lhs, rhs) { } };
/* AST node representing exponents */
class ast_exp : public ast_binop_tmpl<ast_exp> { public: ast_exp(ast *lhs, ast *rhs) : ast_binop_tmpl(lhs, rhs) { } };

class ast_assign : ast_tmpl<ast_assign> {
public:
	std::string id;
	ast         *eval;
	ast_assign(std::string id, ast *eval) { this->id = id; this->eval = eval; }
};

class ast_define : ast_tmpl<ast_define> {
public:
	std::string id;
	ast         *eval;
	ast_define(std::string id, ast *eval) { this->id = id; this->eval = eval; }
};

#endif
