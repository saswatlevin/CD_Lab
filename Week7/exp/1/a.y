%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}


%token NL ID NUMBER  SS CO INT


%%
stmt :  DC NL
	;

DC   : 	DT term SS
        |DT term CO term SS
	;

DT :	INT
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
printf("\nin.txt file opened\n");
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

