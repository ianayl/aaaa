// #include <stdexcept>

#include "lexeme.h"

lexeme::lexeme(lexeme_t t, std::string v)
{
	this->type   = t;
	this->value  = v;
}

// lexeme::lexeme(lexeme_t t, lexeme_keyw_t keyw_t, std::string v)
// {
// 	this->type   = t;
// 	this->keyw_t = (t == lexeme_keyword) ? keyw_t : lexeme_keyw_null;
// 	this->value  = v;
// }
// 
// lexeme::lexeme(lexeme_t t, std::string v)
// {
// 	if (t == lexeme_keyword) throw std::logic_error("Wrong constructor dingus");
// 	this->type   = t;
// 	this->keyw_t = lexeme_keyw_null;
// 	this->value  = v;
// }
// 
// lexeme::lexeme(lexeme_keyw_t keyw_t, std::string v)
// {
// 	this->keyw_t = keyw_t;
// 	this->value  = v;
// }
