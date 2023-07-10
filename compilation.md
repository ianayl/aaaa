# Compiling

As far as I know, there are many ways to "compile" or represent an AST as an intermediate in able to generate machine code. The most popular way as far as I can tell is by turning an AST into static single assignment form (SSA), and then turning that into machine code.

**TODO** Figure out more ways to compile other than converting to SSA

# New plan

- Don't construct an AST, construct a CFG instead
- apply SSA algo

# My understanding thus far...

- Sections of the AST where code is executed sequentially without jumps are separated into **basic blocks**
- These blocks are then treated as nodes and built into a control flow graph (**CFG**s, these are _not_ context free grammars) when we talk about compilation.
- Blocks are terminated by "terminators" (so e.g. `jmp`/`j`, `br`/`b`/`beq`/`bne`/etc) -- **TODO** still don't quite understand how to implement this part yet

## SSA construction

The most commonly used algorithm seems to be a eager algorithm made by Cytron et al. However, there seems to be a more efficient approach by Braun et al.:

### Forming basic blocks

This is just brainstorming. I have no idea how this actually works.

Basically: create a stack. Descend down the AST/DAG until you hit an atomic "thing", e.g. constants, or a call to an identifier. Push it onto the stack (see dragon book section below), and basically construct the AST/DAG using triples/quadruples (see dragon book section below).

### Local value numbering

Okay, but if I'm constructing basic blocks and I'm faced with a constant or an identifier, I need to assign it a number. Hence, local value numbering:

SSA's require that a variable is only established once. So, our algorithm must facilitate this. From what I understand, the Braun et al. approach does.

From what I get, for the Braun et al. algorithm for local numbering:

#### `writeVariable`:

- the `variable` parameter is an identifier
- the `block` is a basic block in a CFG
- the `value` is actually the value, so e.g if you have a static value `v1` then `value` is `v1`(???)

I don't understand this if I'm honest. Please send help.

#### Writes operations:

Just write it into the current "definition"(???)

#### Read operations:


# According to dragon book...

- Convert AST to DAG (which gives you more information about which variables are used. Useful for converting to three-address codes akin to assembly)
    - The DAG here is merely a DAG because instead of having a new identifier node for every call of a variable in an AST, calls to the same identifiers in a DAG is pointed to the same node, creating a DAG instead of a tree.
- DAGS can be equivalently represented in a list of triples (think math triples, e.g. tuples, quadruples, etc), where the first element is an operation, and the two remaining elements are parameters. Note that there is nothing keeping track of results, so to represent DAG's, a list of triples are used: each triple has it's index, and to use the returned result of that triple, it's index in the list is used. In theory, a stack and a tree traversal should be sufficient for representing a DAG as a list of triples. 
- Quadruples are also a thing, where instead of triples having just 3 elements, quadruples have an extra "result" element: So, instead of keeping track of index numbers of triples when referring to results of prior operations, each operation is named as the "result" element.
