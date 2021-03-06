%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#define YY_DECL struct token *yylex(void)

char *Type(struct token *tk)
{
switch(tk->type)
{
case 0:
return "RELATIONAL_OPERATOR";

case 1:
return "IDENTIFIER";

case 2:
return "KEYWORD";

case 3:
return "NUMERICAL_CONSTANT";

case 4:
return "LOGICAL_OPERATOR";

case 5:
return "ARITHMETIC_OPERATOR";

case 6:
return "SPECIAL_SYMBOL";

case 7:
return "SYMBOL";

case 8:
return "ASSIGNMENT_OPERATOR";
case 9:
return "FUNCTION";
default:
return "UNIDENTIFIED";

}

}
 




int lineno=1,colno=1,size=0,scope=0;
char sc;
//struct token* tk;
struct token* allocToken(){
struct token* tk;
tk=(struct token*)malloc(sizeof(struct token));
tk->lexeme=(char*)malloc(sizeof(char)*3);


    
    tk->index=-1;
    tk->type=EOFILE;
    tk->size=sizeof(tk->lexeme);
    return tk;

}


void setTokenArgs(struct token *tk,char *lexeme,int index,int rowno,int colno,enum tokenType type,int size,int scope)
{

if(tk==NULL)
     return;

strcpy(tk->lexeme,lexeme);
tk->index=index;
tk->rowno=rowno;
tk->colno=colno;
tk->type=type;
tk->size=size;
tk->scope=scope;
//strcpy(tk->sc,sc);
}
%}

%%



          

("!","&&","||","|^",",",":")      {tk=allocToken();
            setTokenArgs(tk,yytext,-1,lineno,colno,LOGICAL_OPERATOR,size,scope);
            colno+=strlen(yytext);
            size=sizeof(yytext);
            return tk;}

['^','+','*','/','-']     {tk=allocToken();
            setTokenArgs(tk,yytext,-1,lineno,colno,ARITHMETIC_OPERATOR,size,scope);
            colno+=strlen(yytext);
            size=sizeof(yytext);
            return tk;}     


("_","r")       {tk=allocToken();
            setTokenArgs(tk,yytext,-1,lineno,colno,IDENTIFIER,size,scope);
            colno+=strlen(yytext);
            size=sizeof(yytext);
            return tk;}

("++","--","exp")     {tk=allocToken();
            setTokenArgs(tk,yytext,-1,lineno,colno,ARITHMETIC_OPERATOR,size,scope);
            colno+=strlen(yytext);
            size=sizeof(yytext);
            return tk;} 


['(',')','[',']']      {tk=allocToken();
                                setTokenArgs(tk,yytext,-1,lineno,colno,SYMBOL,size,scope);
                                colno+=strlen(yytext);
                                size=sizeof(yytext);
                                return tk;}

['{']                   {tk=allocToken();
                                setTokenArgs(tk,yytext,-1,lineno,colno,SYMBOL,size,scope);
                                colno+=strlen(yytext);
                                scope++;
                                size=sizeof(yytext);
                                return tk;}
['}']                   {tk=allocToken();
                                setTokenArgs(tk,yytext,-1,lineno,colno,SYMBOL,size,scope);
                                colno+=strlen(yytext);
                                scope--;
                                size=sizeof(yytext);
                                return tk;}


(";")     {tk=allocToken();
                 setTokenArgs(tk,yytext,-1,lineno,colno,SPECIAL_SYMBOL,size,scope);
                 colno+=strlen(yytext);
                 size=sizeof(yytext);
                 return tk;}

"="      {tk=allocToken();
            setTokenArgs(tk,yytext,-1,lineno,colno,ASSIGNMENT_OPERATOR,size,scope);
            colno+=strlen(yytext);
            size=sizeof(yytext);
            return tk;}

                        


"/*".*"*/" { int i=0;
               while(yytext[i]!='\0'){
                   if(yytext[i]=='\n')
        {
                            lineno++;
                            colno=1;
                    }
                    else
                        
                        colno++;
                    i++;
                }
          }
        

"//".*"\n" {lineno++;colno=1;}
(\"(.)*\") {colno+= strlen(yytext);}
(\'(.)*\') {colno+=strlen(yytext);}
\n         {lineno++;colno=1;}


 ['<', '>']   {tk=allocToken();
            setTokenArgs(tk,yytext,-1,lineno,colno,RELATIONAL_OPERATOR,size,scope);
            colno+=strlen(yytext);
            size=sizeof(yytext);
            return tk;
              }
(">=","<=","<=","==","!=")   {tk=allocToken();
                               setTokenArgs(tk,yytext,-1,lineno,colno,RELATIONAL_OPERATOR,size,scope);         
                               colno+=strlen(yytext);
                               size=sizeof(yytext);
                               return tk;}



("include")  {lineno++;colno=1;}
("stdio")  {lineno++;colno=1;}
("stdlib")  {lineno++;colno=1;}
("string")  {lineno++;colno=1;}
("math")  {lineno++;colno=1;}
("conio")  {lineno++;colno=1;}
(".h")  {lineno++;colno=1;}
 

("auto","break","case","const","continue","default","do","double","switch","union","FILE")              {tk=allocToken();
setTokenArgs(tk,yytext,-1,lineno,colno,KEYWORD,size,scope);
colno+=strlen(yytext);
size=sizeof(yytext);
return tk;}

("else","enum","extern","float","for","goto","if","int","typedef")  {tk=allocToken();
setTokenArgs(tk,yytext,-1,lineno,colno,KEYWORD,size,scope);
colno+=strlen(yytext);
size=sizeof(yytext);
return tk;}

("long","register","return","short","signed","sizeof","static","struct","unsigned")  {tk=allocToken();
setTokenArgs(tk,yytext,-1,lineno,colno,KEYWORD,size,scope);
colno+=strlen(yytext);
size=sizeof(yytext);
return tk;}

[0-9]+    {tk=allocToken();
            setTokenArgs(tk,yytext,-1,lineno,colno,NUMERICAL_CONSTANT,size,scope);
            colno+=1;
            size=sizeof(yytext);
            return tk;}
             
[aA-zZ]+  {tk=allocToken();
            setTokenArgs(tk,yytext,-1,lineno,colno,IDENTIFIER,size,scope);
            colno+=1;
            size=sizeof(yytext);
            return tk;}             





["for"]["(".*")"] {
lineno++;colno=strlen(yytext);
}
    



%%

int  main(int argc,char **argv)

{

   if(argc<2){
         printf("This program requires name of one C file");
         exit(0);
   }
   yyin=fopen(argv[1],"r");
   int cnt=0;
   printf("\n        Lexeme   Function_Name   Arguments     Type        Size       Scope");
   while(tk=yylex()){
         if(tk->scope>0)
          printf("\n       %s        %s        %d       L",tk->lexeme,Type(tk),tk->size);
         else
          printf("\n       %s        %s        %d       G",tk->lexeme,Type(tk),tk->size);
        
        cnt++;
   //INSERT(tk);
   //Display();
   }
return 0;
}
int yywrap(){
     return 1;
}

