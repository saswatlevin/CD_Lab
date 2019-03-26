%{
#include<stdio.h>
#include<stdlib.h>
#include"a.tab.h"
%}


%%
[0-9]+ {return NUMBER;}
\n {return NL;}
[a-zA-Z][a-zA-Z0-9_]* {return ID;}
" "|"\t" {;}
. {return yytext[0];}
      
%%
int yywrap()
{
return 1;
}
