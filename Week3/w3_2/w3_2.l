%{
int chars=0;
int words=0;
int lines=0;
int spaces=0;
%}

%%
[a-zA-z]+ {words++;chars+=strlen(yytext);}
\n {chars++;lines++;}
[' '] {chars++;spaces+=strlen(yytext);}
. {chars++;}
%%

main(int argc,char **argv)
{
yylex();
printf("Lines=%d\tWords=%d\tCharacters=%d\tSpaces=%d\t\n",lines,words,chars,spaces);}

int yywrap(){
return 1;
}
