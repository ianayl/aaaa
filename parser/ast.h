#ifndef AST_H
#define AST_H

#include <string>
#include <iostream>

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
 * the BASE class for a visitor pattern representing one tree-walk traversal of
 * the AST -- useful for e.g. AST optimization, type checking, or straight tree-
 * walk interpretation.
 *
 * Note: use ast_traversal_tmpl when creating AST traversals! Return types are
 * enforced independently in the traverse() function and each individual impl
 * of visit.
 */
class ast_traversal {
public:
	virtual void* visit(class ast_id     *n) = 0;
	virtual void* visit(class ast_lit    *n) = 0;
	virtual void* visit(class ast_add    *n) = 0;
	virtual void* visit(class ast_sub    *n) = 0;
	virtual void* visit(class ast_mul    *n) = 0;
	virtual void* visit(class ast_div    *n) = 0;
	virtual void* visit(class ast_exp    *n) = 0;
	virtual void* visit(class ast_assign *n) = 0;
	virtual void* visit(class ast_define *n) = 0;
};

/*
 * Note on the visitor functions:
 * - accept() is usually a CRTP that works as normal
 * - visit() is the visitor function, except usually the return type is void*
 *   as to not assume return types of any of the visitors. However, internally,
 *   in each implementation of visit(), it is expected that type conversions are
 *   enfored INTERNALLY.
 * - traverse() is the ACTUAL function used to traverse an AST. This is because
 *   traverse will actually enforce the return result of the output. This saves
 *   you the effort from having to cast every time.
 */

template<class CRTP, typename result_t>
class ast_traversal_tmpl : public ast_traversal {
public:
	/**
	 * Traverse an AST using the current AST traversal 
	 * Note: This is a template function and the return type of the function is
	 * determined by template arguments
	 */
	result_t traverse(class ast *n);
};

/**
 * AST Traversal for printing an AST to stdout
 */
class ast_print : public ast_traversal_tmpl<ast_print, void> {
private:
	int indent_lvl;

	/**
	 * Helper function for visiting the children of a binop AST node
	 */
	template<class ast_type>
	void _ast_print_visit_binop_children(ast_type *n);
public:
	/**
	 * Create an AST traversal to print an AST to stdout
	 * @param initial_indent_lvl The starting indentation level to use
	 */
	ast_print(int initial_indent_lvl = 0);

	void* visit(ast_id     *n);
	void* visit(ast_lit    *n);
	void* visit(ast_add    *n);
	void* visit(ast_sub    *n);   
	void* visit(ast_mul    *n);   
	void* visit(ast_div    *n);   
	void* visit(ast_exp    *n);   
	void* visit(ast_assign *n);
	void* visit(ast_define *n);
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
	virtual void* accept(class ast_traversal *t) = 0;
	void print();
};

/*
 * AST node definitions
 */
// TODO: Consider: should all AST function definiitons really be in the header?

/**
 * Helper template for constructing AST nodes with a builtin visitor accept function
 */
template<class CRTP>
class ast_tmpl : public ast {
public:
	void* accept(ast_traversal *t);
};

/* AST node representing identifiers */
class ast_id : public ast_tmpl<ast_id> {
public:
	std::string id; 
	ast_id(std::string id);
};

/* AST node representing literal values */
class ast_lit : public ast_tmpl<ast_lit> {
public:
	int val; 
	ast_lit(int val);
};

/**
 * Helper template for representing binary operation AST nodes
 */
template<class CRTP>   /* Curiously repeating template pattern */
class ast_binop_tmpl : public ast_tmpl<CRTP> {
public:
	ast *lhs, *rhs;
	ast_binop_tmpl(ast *lhs, ast *rhs);
};

/* AST node representing addition */
class ast_add : public ast_binop_tmpl<ast_add> { public: ast_add(ast *lhs, ast *rhs); };
/* AST node representing subtraction */
class ast_sub : public ast_binop_tmpl<ast_sub> { public: ast_sub(ast *lhs, ast *rhs); };
/* AST node representing multiplication */
class ast_mul : public ast_binop_tmpl<ast_mul> { public: ast_mul(ast *lhs, ast *rhs); };
/* AST node representing division */
class ast_div : public ast_binop_tmpl<ast_div> { public: ast_div(ast *lhs, ast *rhs); };
/* AST node representing exponents */
class ast_exp : public ast_binop_tmpl<ast_exp> { public: ast_exp(ast *lhs, ast *rhs); };

class ast_assign : public ast_tmpl<ast_assign> {
public:
	std::string  id;
	ast         *eval;
	ast_assign(std::string id, ast *eval);
};

class ast_define : public ast_tmpl<ast_define> {
public:
	std::string  id;
	ast         *eval;
	ast_define(std::string id, ast *eval);
};

#endif
