# Frontend `Calc`

### `Calc`
An expression calculation language.

#### Extended Backus-Naur Form:
```bash
calc   : ("with" ident ("," ident)* ":") ? expr;
expr   : term (( "+" | "-" ) term)* ;
term   : factor (( "*" | "/" ) factor)* ;
factor : ident | number | "(" expr ")" ;
ident  : ([a-zAZ])+ ;
number : ([0-9])+ ;
```

#### Example:
```bash
with a, b: a * (a + b)

3 + 4 * 5
```

---

### Project Layout
- ./Calc:
    - README.md
    - CMakeLists.txt
    - ./src:
        - AST.h: A
        - Calc.cpp
        - CMakeList.txt
        - CodeGen.cpp
        - CodeGen.h
        - Lexer.cpp
        - Lexer.h
        - Parser.cpp
        - Parser.h
        - rtcalc.c
        - Sema.cpp
        - Sema.h  

---

### Build
```sh
rm -rf build && mkdir build && cd build

# ./build
# cmake -GNinja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DLLVM_DIR=<path to llvm installation configuration> ../
cmake -GNinja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DLLVM_DIR=../../llvm-project/llvm ../
ninja

# test
# ./build/src/
./calc "with a: a*3" | llc -filetype=obj -relocation-model=pic -o=expr.o
# clang -o expr expr.o <path to rtcalc.c> 
clang -o expr expr.o ../../src/rtcalc.c
./expr
```