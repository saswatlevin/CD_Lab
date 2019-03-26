%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}

%token NL ID INT SS CO
%%
stmt:decl NL
    ;
decl:DT IDL SS
     ;
DT:INT
   ;
IDL:ID
  | ID CO IDL
  ;
%%

int yyerror(char *msg)
{
	printf("\n Invalid\n");
	exit(0);
}

void main()
{
	printf("\n Enter the expression:\n");
	yyin=fopen("1.txt","r");
        do{
            if(yyparse())
            {
               printf("\nFailure:\n");
               exit(0);
            }
        }while(!feof(yyin));
         
        printf("\nSuccess\n");
}
