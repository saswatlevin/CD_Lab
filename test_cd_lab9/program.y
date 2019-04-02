%{
#include<stdio.h>
#include<stdlib.h>

int yylex();
int yyerror();
extern FILE *yyin;
%}

%token BASIC
%token LBR
%token RBR
%token LSQB
%token RSQB
%token NL
%token SS
%token CO
%token ID
%token COLON
%token NUM

%token EQUAL

%define parse.error verbose

%%
stmt:PROGRAM NL
    ;
PROGRAM:BLOCK
       ;
BLOCK:LBR DECLS stmts RBR
     ;
DECLS:DECL DECLS
     |
     ; 
DECL:TYPE ID SS
    ;
TYPE:TYPE LSQB NUM RSQB|BASIC
    ;
stmts:stmts stmt
     |
     ;
stmt:ID EQUAL NUM SS
    ;
   
%%


int yyerror(char *msg)
{
	printf("\n%s",msg);
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



