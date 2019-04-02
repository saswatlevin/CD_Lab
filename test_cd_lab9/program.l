%{
#include <stdio.h>
#include "program.tab.h"
%}

%%
"{" {return LBR;}
"}" {return RBR;}
"[" {return LSQB;}
"]" {return RSQB;}

"basic" {return BASIC;}

"="      {return EQUAL;}

"$"     {return NL;}
","      {return CO;}
";"      {return SS;}
":"      {return CO;}
[.]      {return ID;} 
[aA-zZ]  {return ID;}
[0-9]+   {return NUM;}

%%
int yywrap(){
return 1;
}

