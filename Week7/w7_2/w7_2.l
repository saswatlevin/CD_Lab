%{
#include<stdio.h>
#include"w7_2.tab.h"
%}

%%
";"    {return SS;}
"="    {return RELOP;}
"=="   {return RELOP;}
"<="   {return RELOP;}
">="   {return RELOP;}
"!="   {return RELOP;}
"!"    {return RELOP;}
"<"    {return RELOP;}
">"    {return RELOP;}

"if"   {return IF;}
"else" {return ELSE;}

"{"    {return LBR;}
"}"    {return RBR;}

"("    {return LR;}
")"    {return RR;}

"\n"   {return NL;}

"*"    {return MULOP;}
"+"    {return ADDOP;}

[0-9]+ {return NUM;}
[aA-zZ] {return ID;}

%%

int yywrap()
{
  return 1;
}
