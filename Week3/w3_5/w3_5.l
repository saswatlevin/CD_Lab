%{
int join_count=0;
%}

%%
" and " {++join_count;}
" but " {++join_count;}
" because " {++join_count;}
" or " {++join_count;}
" as " {++join_count;}
%%

main(int argc,char **argv)
{
yylex();

if(join_count>0)
printf("\nThis is a compound statement");
printf("\nJoins=%d\t",join_count);}

int yywrap(){
return 1;
}
