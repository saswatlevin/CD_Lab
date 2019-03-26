%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}


%token NL ID NUMBER PLUS MINUS DIV MUL
%left '+' '-' '*' '/'

%%
stmt :  exp NL
	;

exp : 	exp PLUS term
	|exp MINUS term
	|exp DIV term
        |exp MUL term
	|term
	;

term :	ID
	|NUMBER
	;

%%

int yyerror(char * mag)
{
printf("Invalid expression\n");
return 1;
}


void main()
{
printf("in.txt file opened\n");
yyin=fopen("in.txt","r");

do
{
   if(yyparse())
     {
     printf("Failure\n");
     exit(0);
     }

}while(!feof(yyin));
printf("\nSuccess");
}

