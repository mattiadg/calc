# Calc
A basic calculator that supports the 4 base operations and parentheses.
It is written as a simple interpreter with hand-written lexer, [Pratt parser](https://dev.to/jrop/pratt-parsing) and [Tree Walk interpreter](https://imantung.github.io/tree-walk-interpreter/).  
No compiler-compiler tools are used, following the spirit of books such as [Crafting Interpreters](https://craftinginterpreters.com/) and [Writing an Interpreter in Go](https://interpreterbook.com/). The goal is twofold: leave no space for "magic" in the implementation, and learn C++.  

Please, note that this is a toy project with educational purpose and not something that will ever go in production anywhere.  
It comes with a cmake recipe and a small Google Test suite, having the same goal in mind of familiarizing with such technologies.

Forking this repo to add more features and improve its codebase is strongly encouraged. I am releasing it to share this learning project with anybody that may need it.

## Compile

git clone the project and in the main folder run 
```Bash
$ cmake -S . -B build && cmake --build build
```

the executables will be under the `build` folder.
## Example
```Bash
$ ./calc "(2 + 3) * 7"
 35
```

## License
This project has to be considered "public domain" and is released with double license MIT and Apache. Reuse it with the license you find more appropriate.