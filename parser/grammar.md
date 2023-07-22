# Grammar

## LL

This grammar _will_ be LL if I manifest hard enough.

```ebnf
Statement  ::= Expression '\n' | Define '\n'
Define     ::= 'def' id '=' Expression
Expression ::= id '=' Expression
           |   Add
Add        ::= Mul Addp
Addp       ::= '+' Mul Addp
           |   '-' Mul Addp
           |   ε
Mul        ::= Exp Mulp
Mulp       ::= '*' Exp Mulp
           |   '/' Exp Mulp
           |   ε
Exp        ::= Term Expp
Expp       ::= '^' Term Expp
           |   ε
Term       ::= ( Expression )
           |   '-' Term
           |   id
           |   num_lit
```

## LR

Deprecated: I am preferring LL because ~~I'm lazy~~ handwriting LL parsers are faster. 

Nonetheless, this grammar _will_ be LR if I manifest hard enough.

```ebnf
Statement  ::= Expression '\n' | Define '\n'
Define     ::= def id = Expression
Expression ::= Term
           |   Expression + Term
Term       ::= Factor
           |   Term * Factor
Factor     ::= ( Expression )
           |   id
           |   num_lit
```
