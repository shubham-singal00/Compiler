program  ->     header  using namespace System;  main 
 program  ->    header  using namespace System;  external-declaration   main 
 program  ->    header  using namespace System;  external-declaration   main   function-definitions 

 external-declaration  ->   function-definition  external-declaration 
 external-declaration  ->   function-declaration  external-declaration 
 external-declaration  ->   declaration  external-declaration 
 external-declaration  ->  '' 
                 	

 function-declaration  ->   type-specifier   identifier ( parameter-declarations );

 function-definitions  ->   function-definition  function-defintions 
 function-definitions  ->   function-definition 

 function-definition  ->   type-specifier   identifier ( parameter-declaration ) {  statements  }

 declaration  ->   type-specifier   identifier  ; 

 parameter-declarations  ->   parameter-declaration ,  parameter-declarations  
 parameter-declarations  ->   parameter-declaration  

 parameter-declaration  ->   type-specifier   identifier 

 type-specifier  ->  void
 type-specifier  ->  char
 type-specifier  ->  short		
 type-specifier  ->  int
 type-specifier  ->  long
 type-specifier  ->  float
 type-specifier  ->  double
 type-specifier  ->  signed
 type-specifier  ->  unsigned

 main  ->  int main() {  statements  return 0; }

 statements  ->    statement ; statements  
 statements  ->    statement ;

 statement  ->   conditional-statement  
 statement  ->   loop-statement  
 statement  ->   assignment-statement  
 statement  ->   function-call  
 statement  ->   logical-expression 

 function-call  ->   identifier  =  function  
 function-call  ->   function 

 function  ->   identifier ( parameter-list )  

 parameter-list  ->   identifier ,  parameter-list  
 parameter-list  ->   identifier 

 conditional-statement  ->   if-statememt  

 if-statememt  ->  if (  expression  ) {  statements  }
 if-statememt  ->  if (  expression  ) {  statements  } else {  statements  }

 loop-statement  ->  while (  expression  ) {  statements  } 

 assignment-expression  ->    identifier  =  logical-expression

logical-expression  ->   logical-expression  &&  relational-expression 
 logical-expression  ->   logical-expression  ||  relational-expression 
 logical-expression  ->   relational-expression 

 relational-expression  ->   relational-expression   <= h-relational-expression  
 relational-expression  ->   relational-expression   <  h-relational-expression  
 relational-expression  ->   relational-expression   >= h-relational-expression  
 relational-expression  ->   relational-expression   >  h-relational-expression   
 relational-expression  ->   h-relational-expression 

h-relational-expression  ->   h-relational-expression  ==  arithmetic-expression  
 h-relational-expression  ->   h-relational-expression  !=  arithmetic-expression  
 h-relational-expression  ->   arithmetic-expression 


 arithmetic-expression  ->   arithmetic-expression  +  term  
 arithmetic-expression  ->   arithmetic-expression  -  term  
 arithmetic-expression  ->   term 

 term  ->   term  *  factor 
 term  ->   term  /  factor 
 term  ->   term  %  factor 
 term  ->   factor 

 factor  ->   id 

 id  ->   digits 
 id  ->   variables 

 variables  ->  !  boolean-variable  
 variables  ->   identifier 

 boolean-variable  ->  true 
 boolean-variable  ->  false

 digits  ->   digit  digits  
 digits  ->   digit 

 digit  ->  0 
 digit  ->  1 
 digit  ->  2 
 digit  ->  3 
 digit  ->  4  
 digit  ->  5 
 digit  ->  6 
 digit  ->  7 
 digit  ->  8 
 digit  ->  9
alphabets  ->   alphabet  alphabets 
 alphabets  ->   alphabet 

 alphabet  ->  (A-Za-z_)

 identifier  ->   alphabet identifier-with-digit

identifier-with-digit  ->   alphabets  digits  
 identifier-with-digit  ->   digits  alphabets  
 identifier-with-digit  ->   digits 