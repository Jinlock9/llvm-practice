# LLVM Compiler Frontend Overview
The **frontend** of a compiler is responsible for analyzing the source code and transforming it into an intermediate representation (IR) that can be further optimized and eventually compiled into machine code. In LLVM, the frontend consists of multiple stages:

1. **Lexical Analysis (Lexer)**
2. **Parsing (Parser)**
3. **Semantic Analysis**
4. **Code Generation (CodeGen)**

---

### 1. Lexical Analysis (Lexer)
- The lexer (tokenizer) scans the raw source code and converts it into **tokens**.
- Tokens are the smallest units of meaning in a programming language (e.g., keywords, operators, identifiers, literals).

#### Example:  
```c
int x = 10
```  
The Lexer would generate tokens: 
```css
[int] [identifier: x] [=] [integer: 10] [;]
```

#### Role in LLVM:
- LLVM frontends (e.g., Clang for C/C++) use `Lexer.cpp` to tokenize input text.
- It ignores comments annd whitespace but retains them for error messages.
- Outputs a sequence of tokens for the **parser**.

---

### 2. Parsing (Parser)
- The **parser** processes tokens and generates an **Abstract Syntax Tree (AST)**.
- AST is a structured, hierarchical representation of the program's syntax.
- It checks for syntactic correctness.

#### Example:
For the following code:
```c
int sum(int a, int b) {
    return a + b;
}
```
The parser produces an AST like:
```yaml
Function: sum
 ├── Parameters: a, b
 ├── Return Type: int
 └── Body:
      └── Return Statement:
           ├── Operator: +
           ├── Left Operand: a
           └── Right Operand: b
```

#### Role in LLVM:
- Clang's `Parser.cpp` constructs an AST from tokens.
- The AST is then used for type checking and semantic analysis.

---

### 3. Semantic Analysis
- Ensures the code is **logically and contextually correct**.
- Checks:
    - Type mismatches (`int x = "hello"` → **error**)
    - Undefined variables (`y = 5;` → **error: y not declared**)
    - Function overloading and resolution
    - Control flow correctness (e.g., `return` inside `void` function)

#### Role in LLVM:
- Clang's `Sema.cpp` performs type checking and symbol resolution.
- Ensures correctness before IR generation.

---

### 4. Code Generation (CodeGen)
- Converts the AST into **LLVM Intermediate Representation (LLVM IR)**.
- LLVM IR is a low-level, architecture-independent representation.

#### Example:
For this simple function:
```c
int square(int x) {
    return x * x;
}
```
LLVM IR might look like:
```llvm
define i32 @square(i32 %x) {
entry:
  %mul = mul i32 %x, %x
  ret i32 %mul
}
```

#### Role in LLVM:
- Clang's `CodeGen` module translates AST to LLVM IR.
- This IR is optimized and passed to the LLVM backend for machine code generation.