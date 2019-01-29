%{
int p=0;
int s=0;
%}

%%
printf {p++;fprintf(yyout,"write");}
scanf {s++;fprintf(yyout,"read");}
%%

main()
{
yyin=fopen("f1.c","r");
yyout=fopen("f2.c","w");
yylex();
printf("\n No of printf's=%d",p);
printf("\n No of scanf's=%d",s);
}
int yywrap() {
return 1;
}

