startSym -> program
program -> program construct
program -> construct
program -> list
construct -> block
construct -> WHILE '(' bool ')' block
construct -> IF '(' bool ')' block
construct -> IF '(' bool ')' block ELSE block
block -> '{' list '}' 
list -> stat
list ->	list stat
list -> list error 
stat -> ';'
stat ->	expr ';'
stat -> dec ';'
stat -> text '=' expr ';'
stat -> dec '=' expr ';' 
dec -> TYPES text
bool -> expr REL_OPT expr
bool -> bool OR bool
bool -> bool AND bool
bool -> NOT '(' bool ')'
bool -> '(' bool ')'
bool -> TRUE
bool -> FALSE
expr -> '(' expr ')'
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