%{
int vowels=0;
int consonants=0;
%}

%%
[aeiouAEIOU] {vowels++;}
[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ] {consonants++;}

%%

main(int argc,char **argv)
{
yylex();
printf("\nvowels=%d\tconsonants=%d\n",vowels,consonants);}

int yywrap(){
return 1;
}
