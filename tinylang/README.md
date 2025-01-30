# `tinylang`

## `Modula-2`
Designed for **structured programming** and **systems programming**, with strong support for modularity, concurrency, and data abstraction.

We are going to use the subset of `Modula-2` which is **`tinylang`**.

---

### Project Layout
```yaml
Project: tinylang
 ├── cmake
 │   └── modules
 ├── include
 │   └── tinylang
 │       ├── AST
 │       ├── Basic
 │       ├── Lexer
 │       ├── Parser
 │       └── Sema
 ├── lib
 │   ├── AST
 │   ├── Basic
 │   ├── Lexer
 │   ├── Parser
 │   └── Sema
 ├── tinylang
 └── tools
     └── driver
```

---

### Extended Backus-Naur Form:
```bash
compilationUnit : "MODULE" identifier ";" ( import )* block identifier "." ;
Import : ( "FROM" identifier )? "IMPORT" identList ";" ;
Block : ( declaration )* ( "BEGIN" statementSequence )? "END" ;

declaration : "CONST" ( constantDeclaration ";" )* 
            | "VAR" ( variableDeclaration ";" )*
            | procedureDeclaration ";" ;

constantDeclaration : identifier "=" expression ;

variableDeclaration : identList ":" qualident ;
qualident : identifier ( "." identifier )* ;
identList : identifier ( "," identifier )* ;

procedureDeclaration : "PROCEDURE" identifier ( formalParameters )? ";" block identifier ;
formalParameters : "(" ( formalParameterList )? ")" ( ":" qualident )? ;
formalParameterList : formalParameter ( ";" formalParameter )* ;
formalParameter : ( "VAR" )? identList ":" qualident ;

statementSequence : statement ( ";" statement )* ;
statement : qualident ( ":=" expression | ( "(" ( expList )? ")" )? )
          | ifStatement | whileStatement | "RETURN" ( expression )? ;

ifStatement : "IF" expression "THEN" statementSequence ( "ELSE" statementSequence )? "END" ;
whileStatement : "WHILE" expression "DO" statementSequence "END" ;

expList : expression ( "," expression )* ;
expression : simpleExpression ( relation simpleExpression )? ;
relation : "=" | "#" | "<" | "<=" | ">" | ">=" ;
simpleExpression : ( "+" | "-" )? term ( addOperator term )* ;
addOperator : "+" | "-" | "OR" ;
term : factor ( mulOperator factor )* ;
mulOperator : "*" | "/" | "DIV" | "MOD" | "AND" ;
factor : integer_literal | "(" expression ")" | "NOT" factor | qualident ( "(" ( expList )? ")" )? ;
```

### Example
```v
MODULE Gcd;

PROCEDURE GCD(a, b: INTEGER) : INTEGER;
VAR t: INTEGER;
BEGIN
    IF b = 0 THEN
        RETURN a;
    END;
    WHILE b # 0 DO
        t := a MOD b;
        a := b;
        b := t;
    END;
    RETURN a;
END GCD;

END Gcd.
```