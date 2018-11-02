# Compiler

## Compiler for a costom programming language 
---
## Installing and running the program

Download the compiler by running 
```
git clone 'https://github.com/Acesps/Compiler.git'
cd ./Compiler
g++ *.cpp *.hpp -o output
```
To run the compiler 
```
./output code.txt
```


## Grammer for the language
 startSym' -> startSym
 
 startSym -> funcs 
 
 startSym -> program 
 
 funcs -> funcs 
 
 func funcs -> func 
 
 func -> TYPE text '(' ')' '{' program '}' 
 
 program -> program construct 
 
 program -> construct 
 
 program -> stmts 
 
 construct -> block 
 
 construct -> WHILE '(' bool ')' block 
 
 construct -> IF '(' bool ')' block 
 
 construct -> IF '(' bool ')' block ELSE block 
 
 block -> '{' stmts '}' 
 
 stmts -> stmt 
 
 stmts -> stmts stmt 
 
 stmt -> ';' 
 
 stmt -> expr ';' 
 
 stmt -> dec ';' 
 
 stmt -> text '=' expr ';' 
 
 stmt -> dec '=' expr ';' 
 
 stmt -> PRINT1 '(' string ')' ';' 
 
 stmt -> SCAN1 '(' ID ')' ';' 
 
 stmt -> construct 
 
 string -> ID string 
 
 string -> ID 
 
 dec -> TYPE text 
 
 bool -> expr REL_OPT expr 
 
 bool -> bool OR bool bool -> bool AND bool 
 
 bool -> NOT '(' bool ')' bool -> '(' bool ')' 
 
 bool -> TRUE bool -> FALSE expr -> '(' expr ')' 
 
 expr -> expr '^' expr 
 
 expr -> expr '*' expr 
 
 expr -> expr '/' expr 
 
 expr -> expr '%' expr 
 
 expr -> expr '+' expr 
 
 expr -> expr '-' expr 
 
 expr -> text 
 
 expr -> number 
 
 text -> ID 
 
 number -> DIGIT 
 
 number -> FLOAT
 
## Sample Input
 int func(){ 
 
 a= a+b; 

 } 


int functwo(){ 

  b=b - c; 

if (a+b < c){ 

  z=z - 3; 

} 
  
} 
