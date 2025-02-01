# LLVM IR Generation
LLVM's process of generating **Intermediate Representation (IR)** from an **Abstract Syntax Tree (AST)** is critical in the compilation pipeline.

## Step 1: AST Traversal
LLVM begin with **traversing the AST** to analyze the structure of the source code.

#### Example AST for a Simple Function
For this C function:
```c
int add(int a, int b) {
    return a + b;
}
```
The Clang frontend parses this into an **AST**, which might look like this:
```yaml
FunctionDecl: add
├── ParmVarDecl: a (int)
├── ParmVarDecl: b (int)
└── ReturnStmt
    └── BinaryOperator: +
```
- `FunctionDecl` represent the function declaration (`add`).
- `ParmVarDecl` nodes represent function parameters (`a` and `b`).
- `ReturnStmt` represents the return statement.
- `BinaryOperator` represents `a + b`.

## Step 1: Symbol Resolution
During AST traversal, Clang's **CodeGen** module maps variables and function symbols into LLVM IR consturcts.
- **Function Declaration** -> Mapped to an LLVM function (`llvm::Function`).
- **Parameters** -> Mapped to LLVM function arguments (`llvm::Argument`).
- **Operators** -> Mapped to LLVM IR instructions (`llvm::Instruction`).

#### Example: Resolving Function Symbol
LLVM uses the **LLVM IR Builder** API to generate IR for function declarations:
```cpp
llvm::LLVMContext Context;
llvm::Module *Module = new llvm::Module("my_module", Context);
llvm::IRBuilder<> Builder(Context);

// Define function type: int(int, int)
llvm::FunctionType *FuncType =
    llvm::FunctionType::get(llvm::Type::getInt32Ty(Context),
                            {llvm::Type::getInt32Ty(Context),
                             llvm::Type::getInt32Ty(Context)},
                            false);

// Create function
llvm::Function *AddFunction =
    llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage,
                           "add", Module);
```

## Step 3: Instruction Selection (AST -> LLVM IR)
LLVM IR Builder translates AST ndoes into **LLVM IR instructions**.

#### 3.1 Function Prologue Generatin
LLVM generates the function prologue:
```llvm
define i32 @add(i32 %a, i32 %b) {
```
This corresponds to:
- `define i32 @add` -> Defines an integer function named `add`.
- `i32 %a, i32 %b` -> Parameters `%a` and `%b` are of type `i32` (32-bit integer).

#### 3.2 Generating the Addition Operation
LLVM IR represents `a + b` as:
```llvm
%1 = add i32 %a, %b
```
LLVM IR Builder generates this:
```llvm
llvm::Function::arg_iterator Args = AddFunction->arg_begin();
llvm::Value *A = Args++;
llvm::Value *B = Args++;

llvm::BasicBlock *Entry = llvm::BasicBlock::Create(Context, "entry", AddFunction);
Builder.SetInsertPoint(Entry);

// Create `add` instruction
llvm::Value *Sum = Builder.CreateAdd(A, B, "sum");
```

#### 3.3 Generating the Return Statement
IR for `return a + b`:
```llvm
ret i32 %1
```
LLVM IR Builder generates this:
```cpp
Builder.CreateRet(Sum);
```

#### Final LLVM IR Output
The final IR code generated:
```llvm
define i32 @add(i32 %a, i32 %b) {
entry:
  %1 = add i32 %a, %b
  ret i32 %1
}
```