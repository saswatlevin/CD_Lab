%{
#include "a.tab.h"
%}

%%

[0-9]+ { printf(" %s\n",yytext); return NUMBER; }
\n { return NL ;}
"int" {return INT;}
[a-zA-Z]+ {  printf(" %s\n",yytext); return ID; } 
";" { printf(";\n"); return SS;}
"," { printf(",\n"); return CO;}
 

%%

int yywrap()
{
return 1;
}
