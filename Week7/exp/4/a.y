%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE*yyin;
%}
%token NUMBER ID NL
%left '+'
%left '*'
%left '-'
%left '/'
%right '^'

%%
stmt:stmt line 
    |
    ;
line:NL 
    |exp NL {printf("Valid expn");exit(0);}
    ;
exp : NUMBER 
    | exp exp '+'
    | exp exp '-'
    | exp exp '*'
    | exp exp '/'
    | exp exp '^'
    | exp NL
    ;

%%
int yyerror(char*msg)
{
printf("INvalid expn");
exit(0);
}
void main()
{
printf("\nEnter the expn:");
yyparse();
}
