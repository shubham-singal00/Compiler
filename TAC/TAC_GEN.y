%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct exprType{

	char *addr;
	char *code;

};

int n=1;
int nl = 1;
char *var;
char num_to_concatinate[10];
char num_to_concatinate_l[10];
char *ret;
char *temp;

char *label;
char *label2;
char *check;

char *begin;

char *b1;
char *b2;

char *s1;
char *s2;

struct exprType *to_return_expr;

char * newTemp(){

	char *newTemp = (char *)malloc(20);
	strcpy(newTemp,"t");
	snprintf(num_to_concatinate, 10,"%d",n);
	//printf("Creating new temp num %d\n", n);
	strcat(newTemp,num_to_concatinate);

	n++;
	return newTemp;
}

char * newLabel(){

	char *newLabel = (char *)malloc(20);
	strcpy(newLabel,"L");
	snprintf(num_to_concatinate_l, 10,"%d",nl);
	strcat(newLabel,num_to_concatinate_l);

	nl++;
	return newLabel;
}
%}

%start startSym

%union {
	int ival;
	float fval;
	char *sval;
	struct exprType *EXPRTYPE;
}
%token <ival> DIGIT
%token <fval> FLOAT
%token <sval> ID IF ELSE WHILE TYPE REL_OPT OR AND NOT TRUE FALSE PRINT1 SCAN1
%token <sval> '+' '-' '*' '/' '^' '%' '\n' '=' ';'
%type <sval> stmts text number construct block dec bool program startSym funcs func string 
%type <EXPRTYPE> expr stmt

%left OR
%left AND
%left NOT
%left REL_OPT
%right '='
%left '+' '-'
%left '*' '/' '%'
%right '^'

%%

startSym : funcs
		{
			s1 = $1;
			label = newLabel();

			check = strstr (s1,"NEXT");

			while(check!=NULL){
				strncpy (check,label,strlen(label));
				strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (s1,"NEXT");
				}

			ret = (char *)malloc(strlen(s1)+10);
			ret[0] = 0;

			strcat(ret,s1);
			strcat(ret,"\n");
			strcat(ret,label);
			strcat(ret," :\n");

			printf("\nTHREE ADDRESS CODE IS\n");
			puts(ret);

			$$ = ret;
		}
		|  program
				{
					s1 = $1;
					////printf("finally %s\n",s1 );
					label = newLabel();

					check = strstr (s1,"NEXT");

					while(check!=NULL){
						strncpy (check,label,strlen(label));
						//printf("finally1 %s\n",s1 );
						
						strncpy (check+strlen(label),"    ",(4-strlen(label)));
						//printf("finally2 %s\n",s1 );

						check = strstr (s1,"NEXT");
						//printf("finally %s\n",s1 );

						}
					//printf("finally %s\n",s1 );

					ret = (char *)malloc(strlen(s1)+100);
					ret[0] = 0;

					strcat(ret,s1);
					strcat(ret,"\n");
					strcat(ret,label);
					strcat(ret,":\n");

					printf("\nTHREE ADDRESS CODE IS:\n");
					puts(ret);

					$$ = ret;
				};

funcs : funcs func
		{
			//printf("Inside funcs: funcs func\n");
			s1 = $1;
			s2 = $2;

			label = newLabel();

			check = strstr (s1,"NEXT");

			while(check!=NULL){
				strncpy (check,label,strlen(label));
				strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (s1,"NEXT");
				}

			ret = (char *)malloc(strlen($1)+strlen($2)+10);
			ret[0] = 0;
			strcat(ret,$1);
			strcat(ret,"\n");
			strcat(ret,label);
			strcat(ret," : ");
			strcat(ret,$2);

			//printf("funcs func\n");

			//puts(ret);
			$$ = ret;
		}
		| func
		{
			//printf("Inside funcs: func\n");
			//printf("Final func\n");
			//puts($1);
			$$ = $1;
		}
func : TYPE text '(' ')' '{' program '}'
		{
			ret = (char *)malloc(strlen($2)+strlen($6)+80);
			ret[0] = 0;
			strcat(ret, "func begin ");
			strcat(ret, $2);
			strcat(ret, "\n");
			strcat(ret,$6);
			strcat(ret, "\nfunc end\n");

			//printf("Func:\n");
			//puts(ret);

			$$ = ret;
		}
program : 	program construct
		{
			//printf("Inside prog:prog construct");
			s1 = $1;
			s2 = $2;

			label = newLabel();

			check = strstr (s1,"NEXT");

			while(check!=NULL){
				strncpy (check,label,strlen(label));
				strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (s1,"NEXT");
				}

			ret = (char *)malloc(strlen($1)+strlen($2)+4);
			ret[0] = 0;
			strcat(ret,$1);
			strcat(ret,"\n");
			strcat(ret,label);
			strcat(ret," : ");
			strcat(ret,$2);

			//printf("program construct\n");

			//puts(ret);
			$$ = ret;
		}
		|
		construct
		{
			//printf("Final Construct \n");
			//puts($1);
			$$ = $1;
		}
		|
		stmts
		{
			//printf("Final stmts \n");
			//puts($1);
			$$ = $1;
		}
		;

construct :     block
		{
			$$ = $1;
		}
		|
		WHILE '(' bool ')' block
		{
			//printf("Inside WHILE\n");
			//puts($5);

			b1 = $3;
			s1 = $5;

			begin = newLabel();
			label = newLabel();

			check = strstr (b1,"TRUE");

			while(check!=NULL){
				strncpy (check,label,strlen(label));
				strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (b1,"TRUE");
				}

			check = strstr (b1,"FAIL");

			while(check!=NULL){
				strncpy (check,"NEXT",4);
				//strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (b1,"FAIL");
				}

			check = strstr (s1,"NEXT");

			while(check!=NULL){
				strncpy (check,begin,strlen(begin));
				strncpy (check+strlen(begin),"    ",(4-strlen(begin)));
				check = strstr (s1,"NEXT");
				}

			ret = (char *)malloc(strlen(b1)+strlen(s1)+20);
			ret[0] = 0;
			strcat(ret,begin);
			strcat(ret," : ");
			strcat(ret,b1);
			strcat(ret,"\n");
			strcat(ret,label);
			strcat(ret," : ");
			strcat(ret,s1);

			strcat(ret,"\n");
			strcat(ret,"goto ");
			strcat(ret,begin);

			//printf("Final return from while\n");
			//puts(ret);

			$$ = ret;

		}
		|
		IF '(' bool ')' block
		{
			//printf("Inside IF\n");

			label = newLabel();
			b1 = $3;

			check = strstr (b1,"TRUE");

			while(check!=NULL){
				strncpy (check,label,strlen(label));
				strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (b1,"TRUE");
				}

			check = strstr (b1,"FAIL");

			while(check!=NULL){
				strncpy (check,"NEXT",4);
				//strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (b1,"FAIL");
				}

			ret = (char *)malloc(strlen(b1)+strlen($5)+4);
			ret[0] = 0;
			strcat(ret,b1);
			strcat(ret,"\n");
			strcat(ret,label);
			strcat(ret," : ");
			strcat(ret,$5);

			//puts(ret);
			$$ = ret;
		}
		|
		IF '(' bool ')' block ELSE block
		{
			//printf("Inside if then else\n");

			b1 = $3;
			label = newLabel();

			check = strstr (b1,"TRUE");
			//replacing all TRUE with labels in b1
			while(check!=NULL){
				strncpy (check,label,strlen(label));
				strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (b1,"TRUE");
				}

			//replacing all Fail with labels in b1
			label2 = newLabel();
			check = strstr (b1,"FAIL");

			while(check!=NULL){
				strncpy (check,label2,strlen(label2));
				strncpy (check+strlen(label2),"    ",(4-strlen(label2)));
				check = strstr (b1,"FAIL");
				}

			ret = (char *)malloc(strlen(b1)+strlen($5)+strlen($7)+20);
			ret[0] = 0;
			strcat(ret,b1);
			strcat(ret,"\n");
			strcat(ret,label);
			strcat(ret," : ");
			strcat(ret,$5);
			strcat(ret,"\n");
			strcat(ret,"goto NEXT");
			strcat(ret,"\n");
			strcat(ret,label2);
			strcat(ret," : ");
			strcat(ret,$7);
			
			//puts(ret);

			$$ = ret;

		}
		;

block:		'{' stmts '}'
		{
			//printf("Inside block\n");
			$$ = $2;
		}
		|
		'{' construct '}'
		{
			$$ = $2;
		}
		;


stmts:    stmt               /* Base Condition */
		{	
			//printf("INSIDE stmts\n");
			$$ = $1->code;
		}
         |
        stmts stmt
		{
			ret = (char *)malloc(strlen($1)+strlen($2->code)+4);
			ret[0] = 0;

			strcat(ret,$1);
			strcat(ret,"\n");
			strcat(ret,$2->code);

			//printf("Inside stmts stmt \n");
			//puts(ret);
			$$ = ret;
		}
	 |
        stmts error '\n'
         {
           yyerrok;
         }
         ;


stmt:    ';'
	 {
		to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = $1;

		to_return_expr->code = (char *)malloc(2);
		to_return_expr->code[0] = 0;

		$$ = to_return_expr;
	 }
	 |
	 expr ';'
         {
		$$ = $1;

         }
	 |
	 dec ';'
         {
		to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = $1;

		to_return_expr->code = (char *)malloc(2);
		to_return_expr->code[0] = 0;

		$$ = to_return_expr;

         }
     |
     text '=' expr ';'
         {
	    //printf("Assignment stmtement \n");

		to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = newTemp();

		ret = (char *)malloc(20);
		ret[0] = 0;

		strcat(ret,$1);

		strcat(ret,"=");
		strcat(ret,$3->addr);
		//printf("RET  = \n");
		//puts(ret);

		temp = (char *)malloc(strlen($3->code)+strlen(ret)+6);

		temp[0] = 0;

		if ($3->code[0]!=0){
			strcat(temp,$3->code);
			strcat(temp,"\n");
			}
		strcat(temp,ret);
		//printf("TEMP = \n");

		//puts(temp);

		to_return_expr->code = temp;

           	$$ = to_return_expr;


		////printf(" %s ===== %s \n",to_return_expr->code,to_return_expr->addr);


         }
	 |
	 dec '=' expr ';'
         {
	    //printf("Dec and Assignment stmtement \n");

		to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = newTemp();

		ret = (char *)malloc(20);
		ret[0] = 0;

		//strcat(ret,to_return_expr->addr);

		strcat(ret,$1);
		strcat(ret,"=");
		strcat(ret,$3->addr);
		//printf("RET  = \n");
		//puts(ret);

		temp = (char *)malloc(strlen($1)+strlen($3->code)+strlen(ret)+6);

		temp[0] = 0;

		if ($3->code[0]!=0){
			strcat(temp,$3->code);
			strcat(temp,"\n");
			}
		strcat(temp,ret);
		//printf("TEMP = \n");

		//puts(temp);

		to_return_expr->code = temp;

           	$$ = to_return_expr;

		////printf(" %s = %s \n",$1,$3->addr);


        }
     |  PRINT1 '(' string ')'';'
     	{
     		////printf("Assignment stmtement \n");

		to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = newTemp();

		ret = (char *)malloc(1000);
		ret[0] = 0;

		strcat(ret,"print ");
		strcat(ret,$3);
		//printf("RET  = \n");
		//puts(ret);

		to_return_expr->code = ret;

           	$$ = to_return_expr;


          
     	}
     | SCAN1 '(' ID ')'';'
     	{
         	to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = newTemp();

		ret = (char *)malloc(100);
		ret[0] = 0;

		strcat(ret,"scan ");
		strcat(ret,$3);
		//printf("RET  = \n");
		//puts(ret);

		to_return_expr->code = ret;

           	$$ = to_return_expr;
 
     	}
     |construct
     {
     	to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = newTemp();
		to_return_expr->code =$1;
		$$ = to_return_expr;


     }
     	;
string : ID string
		{	
			ret = (char *)malloc(strlen($1) + strlen($2) + 10);
			ret[0] = 0;
			strcat(ret,$1);
			strcat(ret," ");
			strcat(ret,$2);
			$$ = ret;
		}
	|	
		ID
			{
		//printf("Inside Identifier : %s\n",$1);
           	$$ = $1;
         }


dec : 		TYPE text
		{
			$$ = $2;
		}
			

bool : 	 	expr REL_OPT expr
		{
			//printf("Inside rel opt\n");
			////printf("$1 code is %s\n",$1->addr);
			temp = (char *)malloc(strlen($1->code)+strlen($3->code)+50);
			temp[0] = 0;

			if($1->code[0]!=0){
				strcat(temp,$1->code);
				strcat(temp,"\n");
				}
			if($3->code[0]!=0){
				strcat(temp,$3->code);
				strcat(temp,"\n");
				}

			ret = (char *)malloc(50);
			ret[0] = 0;
			strcat(ret,"if(");
			strcat(ret,$1->addr);
			strcat(ret,$2);
			strcat(ret,$3->addr);
			strcat(ret,") goto TRUE \n goto FAIL");
			strcat(temp,ret);

			$$ = temp;
		}
		|
		bool OR bool
		{
			//printf("Inside OR\n");

			b1 = $1;
			b2 = $3;

			label = newLabel();

			check = strstr (b1,"FAIL");

			while(check!=NULL){
				strncpy (check,label,strlen(label));
				strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (b1,"FAIL");
				}

			temp = (char *)malloc(strlen(b1)+strlen(b2)+10);
			temp[0] = 0;

			strcat(temp,b1);
			strcat(temp,"\n");
			strcat(temp,label);
			strcat(temp," : ");
			strcat(temp,b2);

			$$ = temp;
		}
		|
		bool AND bool
		{
			//printf("Inside AND\n");

			b1 = $1;
			b2 = $3;

			label = newLabel();

			check = strstr (b1,"TRUE");

			while(check!=NULL){
				strncpy (check,label,strlen(label));
				strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (b1,"TRUE");
				}

			temp = (char *)malloc(strlen(b1)+strlen(b2)+10);
			temp[0] = 0;

			strcat(temp,b1);
			strcat(temp,"\n");
			strcat(temp,label);
			strcat(temp," : ");
			strcat(temp,b2);

			$$ = temp;
		}
		|
		NOT '(' bool ')'
		{
			//printf("Inside NOT\n");
			//puts($3);

			b1 = $3;

			label = "TEFS";

			check = strstr (b1,"TRUE");

			while(check!=NULL){
				strncpy (check,label,strlen(label));
				//strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (b1,"TRUE");
				}

			label = "TRUE";
			check = strstr (b1,"FAIL");

			while(check!=NULL){
				strncpy (check,label,strlen(label));
				//strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (b1,"FAIL");
				}

			label = "FAIL";
			check = strstr (b1,"TEFS");

			while(check!=NULL){
				strncpy (check,label,strlen(label));
				//strncpy (check+strlen(label),"    ",(4-strlen(label)));
				check = strstr (b1,"TEFS");
				}

			$$ = b1;
		}
		|
		'(' bool ')'
		{
			$$ = $2;
		}
		|
		TRUE
		{
			//printf("Inside TRUE\n");

			ret = (char *)malloc(20);
			ret[0] = 0;
			strcat(ret,"\ngoto TRUE");

			$$ = ret;
		}
		|
		FALSE
		{
			//printf("Inside FALSE\n");

			//printf("Inside TRUE\n");

			ret = (char *)malloc(20);
			ret[0] = 0;
			strcat(ret,"\ngoto FAIL");

			$$ = ret;
		}
		;

expr:    '(' expr ')'
         {
           $$ = $2;
         }
         |
	 expr '^' expr
         {
		//printf("Exponential : ");

		to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = newTemp();

		ret = (char *)malloc(20);
		ret[0] = 0;

		strcat(ret,to_return_expr->addr);

		strcat(ret,"=");
		strcat(ret,$1->addr);
		strcat(ret,"^");
		strcat(ret,$3->addr);
		//printf("RET  = \n");
		//puts(ret);

		temp = (char *)malloc(strlen($1->code)+strlen($3->code)+strlen(ret)+6);

		temp[0] = 0;

		if ($1->code[0]!=0){
			strcat(temp,$1->code);
			strcat(temp,"\n");
			}
		if ($3->code[0]!=0){
			strcat(temp,$3->code);
			strcat(temp,"\n");
			}
		strcat(temp,ret);
		//printf("TEMP = \n");

		//puts(temp);

		to_return_expr->code = temp;

           	$$ = to_return_expr;

         }
	 |
         expr '*' expr
         {

           //printf("Multiplication : ");
	   	to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = newTemp();

		ret = (char *)malloc(20);
		ret[0] = 0;

		strcat(ret,to_return_expr->addr);

		strcat(ret,"=");
		strcat(ret,$1->addr);
		strcat(ret,"*");
		strcat(ret,$3->addr);
		//printf("RET  = \n");
		//puts(ret);

		temp = (char *)malloc(strlen($1->code)+strlen($3->code)+strlen(ret)+6);

		temp[0] = 0;

		if ($1->code[0]!=0){
			strcat(temp,$1->code);
			strcat(temp,"\n");
			}
		if ($3->code[0]!=0){
			strcat(temp,$3->code);
			strcat(temp,"\n");
			}
		strcat(temp,ret);
		//printf("TEMP = \n");

		//puts(temp);

		to_return_expr->code = temp;

           	$$ = to_return_expr;

         }
         |
         expr '/' expr
         {
           //printf("Division : ");
	  	to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = newTemp();

		ret = (char *)malloc(20);
		ret[0] = 0;

		strcat(ret,to_return_expr->addr);

		strcat(ret,"=");
		strcat(ret,$1->addr);
		strcat(ret,"/");
		strcat(ret,$3->addr);
		//printf("RET  = \n");
		//puts(ret);

		temp = (char *)malloc(strlen($1->code)+strlen($3->code)+strlen(ret)+6);

		temp[0] = 0;

		if ($1->code[0]!=0){
			strcat(temp,$1->code);
			strcat(temp,"\n");
			}
		if ($3->code[0]!=0){
			strcat(temp,$3->code);
			strcat(temp,"\n");
			}
		strcat(temp,ret);
		//printf("TEMP = \n");

		//puts(temp);

		to_return_expr->code = temp;

           	$$ = to_return_expr;

         }
         |
         expr '%' expr
         {
           //printf("Modulo Division : ");
	   	to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = newTemp();

		ret = (char *)malloc(20);
		ret[0] = 0;

		strcat(ret,to_return_expr->addr);

		strcat(ret,"=");
		strcat(ret,$1->addr);
		strcat(ret,"%");
		strcat(ret,$3->addr);
		//printf("RET  = \n");
		//puts(ret);

		temp = (char *)malloc(strlen($1->code)+strlen($3->code)+strlen(ret)+6);

		temp[0] = 0;

		if ($1->code[0]!=0){
			strcat(temp,$1->code);
			strcat(temp,"\n");
			}
		if ($3->code[0]!=0){
			strcat(temp,$3->code);
			strcat(temp,"\n");
			}
		strcat(temp,ret);
		//printf("TEMP = \n");

		//puts(temp);

		to_return_expr->code = temp;

           	$$ = to_return_expr;
         }
         |
         expr '+' expr
         {
           //printf("Addition : ");
	   	to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(200);
		to_return_expr->addr = newTemp();

		ret = (char *)malloc(200);
		ret[0] = 0;

		strcat(ret,to_return_expr->addr);

		strcat(ret,"=");
		strcat(ret,$1->addr);
		strcat(ret,"+");
		strcat(ret,$3->addr);
		//printf("RET  = \n");
		//puts(ret);

		temp = (char *)malloc(strlen($1->code)+strlen($3->code)+strlen(ret)+60);

		temp[0] = 0;

		if ($1->code[0]!=0){
			strcat(temp,$1->code);
			strcat(temp,"\n");
			}
		if ($3->code[0]!=0){
			strcat(temp,$3->code);
			strcat(temp,"\n");
			}
		strcat(temp,ret);
		//printf("TEMP = \n");

		//puts(temp);

		to_return_expr->code = temp;

           	$$ = to_return_expr;
         }
         |
         expr '-' expr
         {
	   //printf("Subtraction : ");
           	to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = newTemp();

		ret = (char *)malloc(20);
		ret[0] = 0;

		strcat(ret,to_return_expr->addr);

		strcat(ret,"=");
		strcat(ret,$1->addr);
		strcat(ret,"-");
		strcat(ret,$3->addr);
		//printf("RET  = \n");
		//puts(ret);

		temp = (char *)malloc(strlen($1->code)+strlen($3->code)+strlen(ret)+6);

		temp[0] = 0;

		if ($1->code[0]!=0){
			strcat(temp,$1->code);
			strcat(temp,"\n");
			}
		if ($3->code[0]!=0){
			strcat(temp,$3->code);
			strcat(temp,"\n");
			}
		strcat(temp,ret);
		//printf("TEMP = \n");

		//puts(temp);

		to_return_expr->code = temp;

           	$$ = to_return_expr;

         }
         |
	 text {
		//printf("Inside text\n");
		to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = $1;

		to_return_expr->code = (char *)malloc(2);
		to_return_expr->code[0] = 0;

		$$ = to_return_expr;}
         |
         number {
		//printf("Inside Number\n");
		to_return_expr = (struct exprType *)malloc(sizeof(struct exprType));
		to_return_expr->addr = (char *)malloc(20);
		to_return_expr->addr = $1;

		to_return_expr->code = (char *)malloc(2);
		to_return_expr->code[0] = 0;

		$$ = to_return_expr;}
         ;

text: 	ID
         {
		//printf("Inside Identifier : %s\n",$1);
           	$$ = $1;
         }
	  ;

number:  DIGIT
         {
		//printf("Inside DIGIT : %d\n",$1);
		var = (char *)malloc(20);
           	snprintf(var, 10,"%d",$1);
		$$ = var;

         }
	 |
         FLOAT
         {
		//printf("Inside FLOAT : %f\n",$1);
		var = (char *)malloc(20);
           	snprintf(var, 10,"%f",$1);
		$$ = var;

         }
	;

%%

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern char *yytext;

main() {
	// open a file handle to a particular file:
	FILE *myfile = fopen("input.txt", "r");
	// make sure it is valid:
	if (!myfile) {
		//printf("File not found!");
		return -1;
	}
	// set lex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));

}

void yyerror(const char *s) {
	//printf("Parse error!  Message: ");
	//puts(s);
	//printf(" with yytext=%s\n", yytext);
	//printf("RET of yylex() is %d\n", yylex());
	exit(-1);
}
