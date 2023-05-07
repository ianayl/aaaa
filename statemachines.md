# Implementations of State Machines - Lessons Learned

While doing research for this section I learned a lot. I will now document them here because I have the memory of a lobotomized chimpanzee.

## Implementing a state machine

Here are the ways I've encountered on how to actually implement a state machine:

### TODO: research more efficient ways to represent graphs

State machines are just graphs, so better graphs eventually lead to better state machines.

### Adjacency list

Cursed lookup, but smaller than a full lookup table / adjacency matrix.

### Lookup table / adjacency matrix

Cursed space usage but O(1) lookup -- as far as I can see this is the most popular way to implement a state machine

### Adjacency trees(?)

If your input into the state machine can be sorted, instead of using an adjacency list you can create an adjacency structure out of more complex data structures, for example a search tree.

Much better than adjacency list, but still not going to be as good as O(1) lookup.

### Using OOP

States are objects, edges are pointers. Basically O(1) lookup and space is fairly reasonable, but this is not very maintainable for handwriting. This is only good for generating stuff

### Using functions as states

Probably the best solution for handwriting small stuff, where each state is a function, and transitions are recursive function calls. Seems like the best solution for handwriting stuff and has O(1) lookup, but recursion isn't great for locality and memory usage when running.

**TODO** This has the capability of becoming more sophisticated and maintainable if you study functional programming more. Check out parser combinators and see how they do things. Also consider checking out architectural-oriented programming instead.

### TODO: States as monads

Null mentioned this, but I don't understand monads enough to actually know what this is yet.

## Optimization

### Hierarchical state machines

Why have one lookup when you can have two? You're basically making a trade-off, by trading maybe O(1) more execution time for more efficient space usage. This also lets you potentially reuse certain parts of the state machine, which makes things even more maintainable. This overall seems like good practice.

### Compression

Obviously compress your representation if you care about hard drive usage. This is kind of useless though, but a good idea to keep in mind to come up with cool ways to mix things together.
