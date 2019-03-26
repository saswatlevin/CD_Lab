%{
   #include <stdio.h>
   #include <stdlib.h>
   int yylex();
   int yyerror();
%}

%token NUMBER ID NL

%left '+'
%left '*'

%%
stmt: exp NL{printf("Valid Expression"); exit(0);}
    ;

exp:exp'+'term
    |term
term:term'*'factor
    |factor
factor:ID
      |NUMBER
      ;
%%

int yyerror(char *msg)
{
   printf("\nInvalid expression");
   exit(0);
}

int main()
{   
    printf("\nEnter the expression");
    yyparse();    
    if(!yyparse())
    {
       printf("\nError");
       exit(0);
    }
    else{
       printf("\nSuccess");
    }
}



