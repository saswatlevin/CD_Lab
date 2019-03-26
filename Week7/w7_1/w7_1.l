%{
  #include<stdio.h>
  #include<stdlib.h>
  #include "w7_1.tab.h"
 
%}

%%
"\n" {return NL;}
"int" {return INT;}
[a-zA-Z]+ {return ID;}
";" {return SS;}
"," {return CO;}
%%
int yywrap()
{
	return 1;
}
