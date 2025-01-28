add_executable(calc Calc.cpp CodeGen.cpp Lexer.cpp Parser.cpp Sema.cpp)

# Ensure LLVM is linked properly
target_link_libraries(calc PRIVATE ${llvm_libs})
