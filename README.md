# llvm-source
Hand-written works, referring to *Learn LLVM17* by Kai Nacke and Amy Kwan.

#### Build
```sh
cmake -GNinja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DLLVM_DIR=../../llvm-project/llvm ../
ninja
```