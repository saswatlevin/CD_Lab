%{
	extern FILE * yyin;
	#include"ST1.h"
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#define YY_DECL struct token *yylex(void)/* (If your environment supports function prototypes, then it will be "int yylex( void )".) This definition may be changed by defining the "YY_DECL" macro. For example, you could use: #define YY_DECL float lexscan( a, b ) float a, b;
								//to give the scanning routine the name lexscan, returning a float, and taking two floats as arguments. Note that if you give arguments to the scanning routine using a K&R-style/non-prototyped function declaration, you must terminate the definition with a semi-colon (`;').*/
	
	struct token *tk;

	struct token * allocToken() 
	{
		struct token *tk;
		tk=(struct token *)malloc(sizeof(struct token));
		tk->lexeme = (char *)malloc(sizeof(char)*50); //maximum two characters in this case
		tk->type=(char *)malloc(sizeof(char)*50); 
		return tk;
	}

	void setTokenArgs(struct token *tk, char *lexeme, char* type)
	{
		if(tk==NULL)
			return; 
		strcpy(tk->lexeme,lexeme);
	
		tk->type=type;
		

	}

	struct token* arr[100];
%}
%%
			
"\n"																	{
																			printf("start of newline\n");
																			tk=allocToken();
																			setTokenArgs(tk,yytext,"Newline");
																			return tk;
																		}	
"//".*"\n" 																{	
															printf("gotten singly comm\n");	
																		}	
"#include".*"\n"														{
																printf("gotten preproxessor\n");
																		}
"\"".*"\"" 																{	

																			tk=allocToken();
																			setTokenArgs(tk,yytext,"String literal");
																			return tk;
																		}
"int"|"float"|"switch"|"for"|"do"|"while"|"return"|"if"|"else"|"double"|"switch"|"case"|"default"|"break"|"char"	{
																			tk=allocToken();
																			setTokenArgs(tk,yytext,"KEYW");
																			return tk;
																		}	
"strlen"|"printf"|"scanf"|"malloc"|"sizeof"|"strcmp"	{
															tk=allocToken();															
															setTokenArgs(tk,yytext,"preDef func.");
															return tk;
														}																	
"*"|"+"|"-"|"*"|"/"|"%"|"++"|"--"							{
															tk=allocToken();
															printf("gotten arith\n");
															setTokenArgs(tk,yytext,"Arithm. op");
															return tk;
														}
"&&"|"||"|"&"|"|"										{
															tk=allocToken();
															setTokenArgs(tk,yytext,"Logical. op");
															return tk;
														}
"<"|"<="|">"|">="|"!="|"==" 							{	
															tk=allocToken();
															setTokenArgs(tk,yytext,"Relational Op.");
															return tk; 
														}
"("|")"|"["|"]"|"{"|"}"|","|";"|":" 						{
																
															tk=allocToken();
															
															setTokenArgs(tk,yytext,"SS");
															return tk; 
														}
"="														{	
															tk=allocToken();
															printf("gotten =\n");
															setTokenArgs(tk,yytext,"Assigm. op.");
															return tk; 
														}
(\'(.)\') 												{	;/* for character literals*/
														tk=allocToken();
														setTokenArgs(tk,yytext,"Character literal");
														return tk; 	
														}
[0-9]+													{	tk=allocToken();
															
															setTokenArgs(tk,yytext,"Numeric Constant");
															return tk; 
														}
[a-zA-Z0-9_]+ 											{	tk=allocToken();
															
															setTokenArgs(tk,yytext,"Identifier");
															return tk; 
														}

%%

int yywrap() 
{ 
		return 1;
}


 