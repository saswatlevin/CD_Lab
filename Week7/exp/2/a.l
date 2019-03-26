%{
#include<stdio.h>
#include<stdlib.h>
#include"a.tab.h"
%}


%%
[0-9]+ {printf("%s",yytext);return NUMBER;}
\n {;}
"if" {printf("%s",yytext);return IF;}
"else" {printf("%s",yytext);return ELSE;}
"while" {printf("%s",yytext);return WHILE;}
"for" {printf("%s",yytext);return FOR;}
"switch" {printf("%s",yytext);return SWITCH;}
"=="|"!="|"<="|">="|">"|"<" {printf("%s",yytext);return RELOP;} 
[a-zA-Z][a-zA-Z0-9_]* {printf("%s",yytext);return ID;}
" "|"\t" {;}
. {printf("%s",yytext);return yytext[0];}
      
%%
int yywrap()
{
return 1;
}
