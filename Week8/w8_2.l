%{
#include <stdio.h>
#include "w8_2.tab.h"
%}

%%

"auto"      {return AUTO;}

"break"      {return BREAK;}

"case"      {return CASE;}

"char"      {return CHAR;}

"const"      {return CONST;}

"continue"      {return CONTINUE;}

"default"      {return DEFAULT;}

"do"           {return DO;}        

"double"      {return DOUBLE;}

"else"        {return ELSE;}

"enum"      {return ENUM;}

"extern"      {return EXTERN;}

"float"      {return FLOAT;}

"for"      {return FOR;}

"goto"      {return GOTO;}

"if"      {return IF;}

"int"      {return INT;}

"long"      {return LONG;}

"main"      {return MAIN;}

"register"      {return REGISTER;}

"return"      {return RETURN;}

"short"      {return SHORT;}

"signed"      {return SIGNED;}

"sizeof"      {return SIZEOF;}

"static"      {return STATIC;}

"struct"      {return STRUCT;}

"switch"      {return SWITCH;}

"typedef"      {return TYPEDEF;}

"union"      {return UNION;}

"unsigned"      {return UNSIGNED;}

"void"      {return VOID;}

"volatile"      {return VOLATILE;}

"while"      {return WHILE;}

"$"     {return NL;}

"{"      {return LBR;}

"}"      {return RBR;}

"("      {return LR;}

")"      {return RR;}

"["      {return LSQB;}

"]"      {return RSQB;}

";"      {return SS;}

","      {return CO;}

":"      {return COLON;}



"+"    {return ADDOP;}
"-"    {return ADDOP;}


"*"    {return MULOP;}
"/"    {return MULOP;}
"%"    {return MULOP;}


"="    {return EQUAL;}


"<"    {return RELOP;}
">"    {return RELOP;}
"<="   {return RELOP;}
">="   {return RELOP;}
"=="   {return RELOP;}



"!"    {return NOT;}
"&&"   {return AND;}
"||"   {return OR;}


[aA-zZ]  {return IDENTIFIER;}             
[0-9]+   {return NUMBER;}              


%%


int yywrap(){
     return 1;
}
  
