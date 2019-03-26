%{

#include<stdio.h>
#include<stdlib.h>

int yylex();
int yyerror();
extern FILE *yyin;
%}



%token AUTO
%token BREAK
%token CASE
%token CHAR
%token CONST
%token CONTINUE
%token DEFAULT
%token DO
%token DOUBLE
%token ELSE
%token ENUM
%token EXTERN
%token FLOAT
%token FOR
%token GOTO
%token INT
%token IF
%token LONG
%token MAIN
%token REGISTER
%token RETURN
%token SHORT
%token SIGNED
%token STATIC
%token STRUCT
%token SIZEOF
%token SWITCH
%token TYPEDEF
%token UNION
%token UNSIGNED
%token VOID
%token VOLATILE
%token WHILE


%token NL      // newline character \n
%token LBR     //left brace {
%token RBR     //right brace }
%token LR      //rounded left bracket (
%token RR      //rounded right bracket )
%token LSQB    //square left bracket [
%token RSQB    //square right bracket ]
%token SS      //semicolon
%token CO      //comma
%token COLON

%token ADDOP   //+ and -
%token MULOP   // multiplication operator * and division operator /
%token EQUAL


%token NUMBER
%token IDENTIFIER


%token RELOP    //relational operators



%token NOT
%token AND
%token OR

%define parse.error verbose

%%


stmt:PROGRAM NL
    ;
PROGRAM: DATA_TYPE MAIN LR RR LBR DECLARATIONS STATEMENT_LIST RBR
       ;
DECLARATIONS:DATA_TYPE IDENTIFIER_LIST SS DECLARATIONS
            |
            ;
DATA_TYPE:INT|FLOAT|CHAR|VOID
         ;

IDENTIFIER_LIST:IDENTIFIER|IDENTIFIER CO IDENTIFIER_LIST|IDENTIFIER LSQB NUMBER RSQB CO IDENTIFIER_LIST|IDENTIFIER LSQB NUMBER RSQB
               ;

STATEMENT_LIST:STATEMENT STATEMENT_LIST
              |
              ;

STATEMENT:ASSIGN_STAT SS|DECISION_STAT|LOOPING_STAT
         ;

ASSIGN_STAT:IDENTIFIER EQUAL EXPN
           ;

EXPN:SIMPLE_EXPN EPRIME
    ;

EPRIME:RELOP SIMPLE_EXPN
      |
      ;

SIMPLE_EXPN:TERM SEPRIME
           ;

SEPRIME:ADDOP TERM SEPRIME
       |
       ;
TERM:FACTOR TPRIME
    ;


TPRIME:MULOP FACTOR TPRIME
      |
      ;

FACTOR:IDENTIFIER|NUMBER
      ;

DECISION_STAT:IF LR EXPN RR LBR STATEMENT_LIST RBR DPRIME
             ;

DPRIME:ELSE LBR STATEMENT_LIST RBR
      |
      ;

LOOPING_STAT:WHILE LR EXPN RR LBR STATEMENT_LIST RBR
            |FOR LR ASSIGN_STAT SS EXPN SS EXPN RR LBR STATEMENT_LIST RBR
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



