%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}

%token NUMBER
%token NL
%token PLUS
%token MINUS
%token INTO
%token BY
%token EQUAL
%token ID
%%
stmt:EXPR NL
    |
    ;
EXPR:ID EQUAL ID PLUS NUMBER|ID EQUAL ID MINUS NUMBER|ID EQUAL ID INTO NUMBER|ID EQUAL ID BY NUMBER
    |
    ;

    ; 
/*NUMBER:NUMBER PLUS INT|NUMBER MINUS INT|NUMBER INTO INT|NUMBER BY INT
      |
      ;*/
%%
int yyerror(char *msg)
{
	printf("\n Invalid\n");
	exit(0);
}

void main()
{
	//printf("\nEnter the expression:\n");
	yyin=fopen("test.txt","r");
        do{
            if(yyparse())
            {
               printf("\nFailure:\n");
               exit(0);
            }
        }while(!feof(yyin));
         
        printf("\nSuccess\n");
}



