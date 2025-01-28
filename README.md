# llvm-practice
Hand-written works, referring to *Learn LLVM17* by Kai Nacke and Amy Kwan.

#### Build
```sh
rm -rf build && mkdir build && cd build

# ./build
cmake -GNinja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DLLVM_DIR=../../llvm-project/llvm ../

ninja

# test
cd build/src/
./calc "with a: a*3" | llc -filetype=obj -relocation-model=pic -o=expr.o
clang -o expr expr.o ../../src/rtcalc.c 
./expr
```
