%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE*yyin;
%}
%token NUMBER ID  IF ELSE WHILE FOR SWITCH RELOP
%left '+'
%left '*'
%left '-'
%left '/'
%left '%'

%%
stmt:decision_stat  
    ;
statement_list : statement statement_list
               |
               ;
statement : assign_stat ';' 
          |decision_stat 
	  |looping_stat
	  ;
assign_stat : ID '=' expn
            ;
expn:simple_expn eprime
    ;
eprime:relop simple_expn
      |
      ;
       
simple_expn:term seprime
	   ;
seprime:addop term seprime 
       |
       ;
term : factor tprime
     ;
tprime : mulop factor tprime 
       |
       ;
factor : ID
       |NUMBER
       ;
decision_stat : IF '(' expn ')' '{'statement_list'}' dprime
              ;
dprime : ELSE '{'statement_list'}' 
       |
       ;
looping_stat : WHILE '('expn')' '{'statement_list'}'
             |FOR '('assign_stat ';' expn ';' assign_stat ')' '{'statement_list'}'
             ;
relop : RELOP
      ;
addop : '+'
      |'-'
      ;
mulop : '*'
      |'/'
      |'%'
      ;
%%
int yyerror(char*msg)
{
printf("ERROR %s",msg);
exit(0);
}
void main()
{
yyin=fopen("input.txt","r");
do{
if(yyparse())
{
printf("FAILURE");
exit(0);
}
printf("SUCCESS");

}while(!feof(yyin));

}


