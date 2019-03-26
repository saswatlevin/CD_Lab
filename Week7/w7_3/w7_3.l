%{
#include<stdio.h>
#include"w7_3.tab.h"
%}

%%


"+"    {return PLUS;}
"-"    {return MINUS;}
"*"    {return INTO;}
"="    {return EQUAL;}
"/"    {return BY;}
"\n"   {return NL;}
[0-9]+ {return NUMBER;}
[aA-zZ]+ {return ID;}
%%

int yywrap()
{
return 1;
}


