%{
int float_pos=0;
int float_neg=0;
int int_pos=0;
int int_neg=0;
%}

%%
[+0-9]+ {int_pos++;}
[-01234556789]+ {int_neg++;}
![-01234556789]+ {int_pos++;}
[0-9.0-9]+ {float_pos++;}
[-0-9.0-9]+ {float_neg++;}
![-0-9.0-9]+ {float_pos++;}  
%%

main(int argc,char **argv)
{
yylex();
printf("\nNegative integers=%d\t",int_neg);
printf("\nPositive integers=%d\t",int_pos);
printf("\nPositive floats=%d\t",float_pos);
printf("\nNegative floats=%d\t",float_neg);}
int yywrap(){
return 1;
}
