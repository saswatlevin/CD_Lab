%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}



%token IF
%token LR
%token RR
%token LBR
%token RBR
%token ELSE
%token NL
%token RELOP
%token MULOP
%token ADDOP
%token ID
%token NUM
%token SS
%%
stmt:STATEMENT NL
    | 
    ;
STATEMENT:DECISION_STAT
         ;

DECISION_STAT:IF LR EXPN RR LBR EXPN SS RBR DPRIME
             ;
EXPN: SIMPLE_EXPN EPRIME
    ;

SIMPLE_EXPN:TERM SEPRIME
           ;

EPRIME:RELOP SIMPLE_EXPN
      |
      ;

SEPRIME:ADDOP TERM SEPRIME
       |
       ;
TERM:FACTOR TPRIME
    ;

FACTOR:ID|NUM
      ;

TPRIME:MULOP FACTOR TPRIME
      |
      ;

  DPRIME: ELSE LBR EXPN SS RBR
      |
      ;

 /*STATEMENT_LIST:STATEMENT STATEMENT_LIST
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



