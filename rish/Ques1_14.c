#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include "lex.yy.c"// corr to GNT1.l

// lookupID is to check for prscnece in Symbol Table

#define LENGTH 512

char delimiters[3] = {' ','\n','\t'};

Table *table;
	char *total_scope;
	int s_no;

char buffer[LENGTH];
//char input[LENGTH][LENGTH];	// Input array?
int count = 0;	// Total no of tokens
int i = 0; 	// current token
char *nextWord;
int flag=0;
int line=0;
int col=1;
char* presently();
void printError();
void printSuccess();
void labeled_stat();
void constant_expn();
void break_statement();
void actuallyMoveAhead();
char* lookahead();
char* nextLexeme();
struct token *getCurrentToken();
int checkForMatch(char *word,char *name);
void program();
void declarations();
void data_type();
void identifier_list();
void statement_list();
void statement();
void assign_stat();
void assign_stat_loop();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void decision_stat();
void dprime();
void looping_stat();
void relop();
void addop();
void mulop();
int BegOfstat(char* word);


char *word;
char *curr_word;
struct token *nextToken;
char *t_type;

struct token *getCurrentToken()
{
	if(flag==1)
		return nextToken;
	else
		return tk;
}
char* getTokenType()
{
	if(flag==1)
		return nextToken->type;
	else
		return tk->type; 
}
char* lookahead()
{
	if(flag==1)//already we had looked ahead
		return presently();
	nextWord=(char*)malloc(sizeof(char)*50);
	flag=1;
	nextWord= nextLexeme();// return the next word
	nextToken=tk;
	return nextWord;
}

void actuallyMoveAhead()
{
	flag=0;
}
char *presently()
{
	if(flag==1)
		curr_word=nextWord;// set cur_word to the word looked ahead 
	else
		curr_word=nextLexeme();//set cur_word to next word
	return curr_word;

}
char* nextLexeme()
{
	printf("in next %d, %d\n",i,count);
	

	tk=yylex();
	if(strcmp(tk->type,"Newline")==0)
	{	line++;
		col=1;
		i+=1;
		tk=yylex();
	}

	//printf("lexeme = %s\n",tk->lexeme );
	printf("considering %s\n",tk->lexeme);
	word=(char*)malloc(sizeof(char)*50);
	word=tk->lexeme;
//	count++;
	return word;
}

void printError(char* error)
{
	printf("line no = %d, col = %d Error occured, expected %s \n",line+1,col,error); 
	// +1 cause if error is at line x then it gets counted at the end after reader reads newline at the end of it
	//i.e, cos error on first line means error is at line1 and not on line 0 
	exit(0);
}
void printSuccess()
{
	printf("_______________________________Debugging Ends_________________________________________________\nAccepted\n"); 
	exit(0); 
}
int checkForMatch(char* word,char* name)
{
	return (strcmp(word, name) == 0);
}

void program()
{
	printf("in program count=%d\n",count);
	word=presently();
	t_type=getTokenType();
	if(checkForMatch(t_type,"KEYW"))
	{	
		i+=1;col+=strlen(word);
		actuallyMoveAhead();
		word=presently();
		if(checkForMatch(word,"main"))
		{
			i+=1;col+=strlen(word); actuallyMoveAhead();
			 word=presently();
			if(checkForMatch(word,"(")) 
			{
				i+=1;col+=strlen(word); actuallyMoveAhead();
				 word=presently();
				if(checkForMatch(word,")")) 
				{
					i+=1;col+=strlen(word); actuallyMoveAhead();
					 word=presently();
					if(checkForMatch(word,"{")) 
					{
						i+=1;col+=strlen(word); actuallyMoveAhead();
						// word=presently();
						declarations();
						statement_list();
						 word=presently();
						if(checkForMatch(word,"}")) 
						{
							i+=1;col+=strlen(word); actuallyMoveAhead();
							
							printf("11 i = %d, count= %d\n",i,count);
							if (i == (count)) 
							{
								printSuccess();;
							}
							else
								printError("Not accepted eventually"); 
						} 
						else 
						{
						//	printf("Epresently() = %s, 11 i = %d, k= %d\n",presently(),i,k);
							
							printError("}");;
						}
					} 
					else 
					{
						printf("22");
						printError("{");;
					}
				} 
				else 
				{
					printf("33");
					printError(")");;
				}
			} 
			else
			{
				printf("44");
				printError("(");;
			}
		} 
		else 
		{
			printf("55");
			printError("main");;
		}
	}
	else
		printError("ret type");
}

void declarations() 
{
	printf("in declarations\n");
	word=lookahead();
	if (checkForMatch(word,"int") || checkForMatch(word,"char")) 
	{
		data_type();
		identifier_list();
		word=presently();
		if(checkForMatch(word,";")) 
		{
			i+=1;col+=strlen(word); actuallyMoveAhead();
			actuallyMoveAhead();
			declarations();
		} 
		else 
		{
			printError(";");;
		}
	}
}

void data_type() 
{
	printf("in data_type\n");
	word=lookahead();
	if (checkForMatch(word,"int") || checkForMatch(word,"char")) 
	{
		actuallyMoveAhead();
		i+=1;col+=strlen(word); actuallyMoveAhead();
		
	} 
	else 
	{
		printError("data type");;
	}
}

void identifier_list() 
{

	//printf("in identifier_list\n");
	word=presently();
	t_type=getTokenType();
	printf("in identifier_list %s, type= %s\n",word,t_type);
	if(checkForMatch(t_type,"Identifier")) 
	{
		if(!lookupId(table,getCurrentToken()))
		{	
			printf("token not found\n");
			printError("token is not in ST");
		}
		i+=1;col+=strlen(word); actuallyMoveAhead();
		 word=lookahead();
		if(checkForMatch(word,",")) 
		{

			i+=1;col+=strlen(word); actuallyMoveAhead();
			actuallyMoveAhead();
			identifier_list();
		} 
		else if(checkForMatch(word,"[")) 
		{
			i+=1;col+=strlen(word); actuallyMoveAhead();
			actuallyMoveAhead();
			 word=presently();
			 t_type=getTokenType();
			if(checkForMatch(t_type,"Numeric Constant")) 
			{
				i+=1;col+=strlen(word); actuallyMoveAhead();
				 word=presently();

	 			if(checkForMatch(word,"]")) 
	 			{
	 				i+=1;col+=strlen(word); actuallyMoveAhead();
	 				 word=lookahead();
					if(checkForMatch(word,",")) 
					{
						i+=1;col+=strlen(word); actuallyMoveAhead();
						actuallyMoveAhead();
						identifier_list();
					} 
					else 
					{
						return;
					}
				} 
				else 
				{
					printError("]");;
				}
			} 
			else 
			{
				printError("Numeric Constant");;
			}
		}
	}
}

void statement_list() {
	
	printf("in statement_list word=%s \n",word);

	statement();
	printf("back from st. word = %s\n",word);
	word=lookahead();
	printf("here %s\n",word);
	declarations();
	int ans=BegOfstat(word);
	printf("ans =%d\n",ans );
	if(ans==1)
	{	
		printf("calling oneself\n");
		statement_list();

	}
		
	// /printf("calling\n");
	
	//t_type=getTokenType();
	//if(checkForMatch(word,"}")|| word==NULL)
		//return;
	//if(checkForMatch(t_type,"Identifier")|| checkForMatch(word,"case") || checkForMatch(word,"default")|| checkForMatch(word,"break"))// nesting the switch statement 
	//{
	//	statement_list();
	//}
}
int BegOfstat(char* word)
{
	printf("in BegOfstat %s\n",word );
	t_type=getTokenType();
	printf("type = %s\n",t_type );
	return ( checkForMatch(t_type,"Identifier") || checkForMatch(word,"if") || checkForMatch(word,"switch") || checkForMatch(word,"while") || checkForMatch(word,"for") || checkForMatch(word,"case") || checkForMatch(word,"default") || checkForMatch(word,"break"));
}
void statement() {
		
	word=lookahead();// if had already looked, then get the already tokenized lexeme else get the next lexeme
	printf("in Statement() word =%s\n",word);
	t_type=getTokenType();
	if(checkForMatch(t_type,"Identifier")) 
	{
		printf("sendin. assign_stat\n");
		assign_stat();
	}
	if(checkForMatch(word,"if") || checkForMatch(word,"switch")) 
	{
		printf("sending decision_stat\n");
		decision_stat();
	}
	if (checkForMatch(word,"while") || checkForMatch(word,"for")) 
	{
		printf("sending looping_stat\n");
		looping_stat();
	}
	if(checkForMatch(word,"case") || checkForMatch(word,"default"))
	{
		printf("sending labeled_stat\n");
		labeled_stat();
	}
	if(checkForMatch(word,"break"))
	{
		printf("sending break_statement\n");
		break_statement();
	}

	else
		printf("NOT Sending anywhere\n");
		
	// else
	// 	statement_list();
}
void break_statement()
{
	printf("in break st\n");
	word=lookahead();
	if(checkForMatch(word,"break"))
	{
		i+=1;col+=strlen(word); actuallyMoveAhead();
		 word=presently();
		if(checkForMatch(word,";"))
		{	
			i+=1;col+=strlen(word); actuallyMoveAhead();
		}
		else
			printError(";");

	}
	else
		printError("break");
}


int check_for_number(char *str)
{
	if(str[0]==48)//the character only is 0
	{
		//i+=1;col+=strlen(word); actuallyMoveAhead();
		return 1;
	}
	else if(atoi(str)!=0)// cos atoi gives 0 for non numeric characters in str
	{
		//i+=1;col+=strlen(word); actuallyMoveAhead();
		printf("ret 1\n");
		return 1;
	}
//	printf("returing 0 %d\n",atoi(str) );
	return 0;
}
void constant_expn()
{
	printf(" in constant_expn\n");
	//word=presently();
	char *str=lookahead();
	if(str[0]=='\'' && strlen(str)==3 && str[2]=='\'')//i..e it is a character of form 'A' etc.
	{	i+=1;col+=strlen(word); actuallyMoveAhead();

	}
	else if(check_for_number(str))
	{	
		i+=1;col+=strlen(word); actuallyMoveAhead();
		printf("here1\n");

	}
	else
	{	
		printf("here2 %s\n",str);
		printError("constant");
	}
}


void labeled_stat()
{
	printf("in labeled_stat\n");
	word=lookahead();
	if(checkForMatch(word,"case"))
	{
		i+=1;col+=strlen(word); actuallyMoveAhead();
		constant_expn();
		printf("back in labeled_stat\n");
		 word=presently();
		if(checkForMatch(word,":"))
		{
			i+=1;col+=strlen(word); actuallyMoveAhead();
			statement_list();
		}
		else
			printError(":");
	}
	else if(checkForMatch(word,"default"))
	{
		i+=1;col+=strlen(word); actuallyMoveAhead();
		 word=presently();
		if(checkForMatch(word,":"))
		{
			i+=1;col+=strlen(word); actuallyMoveAhead();
			statement_list();
		}
		else
			printError(":");
	}
	else
		printError("case/default");
}

void assign_stat() 
{
	printf("in assign_stat\n");
	printf("here\n");
	
	word=lookahead();
	printf("in ass , word = %s\n",word );
	t_type=getTokenType();
	if(checkForMatch(t_type,"Identifier")) 
	{
		if(!lookupId(table,getCurrentToken()))
		{	
			printf("token not found\n");
			printError("token is NOT in ST");
		}
		printf("matched id\n");
		i+=1;col+=strlen(word); actuallyMoveAhead();
		 word=presently();
		if(checkForMatch(word,"=")) 
		{
			printf("matched =\n");
			i+=1;col+=strlen(word); actuallyMoveAhead();
			
			expn();
			printf("back in assign word = %s\n",word );
			 word=presently();
			 			printf("back in assign word = %s\n",word );
			if(checkForMatch(word,";")) 
			{
				printf("matched ;\n");
				i+=1;col+=strlen(word); actuallyMoveAhead();
				
				return;
			}
			else
			{	
				printf("AA1 %s\n",word);
				printError(";");;
			}
		} 
		else 
		{
			printf("BB");
			printError("=");;
		}
	}
	printf("out\n");
}

void assign_stat_loop() 
{
	printf("in assign_stat_loop\n");
	word=lookahead();
	t_type=getTokenType();
	if(checkForMatch(t_type,"Identifier")) 
	{
		if(!lookupId(table,getCurrentToken()))
		{	
			printf("token not found\n");
			printError("token is not in ST");
		}
		i+=1;col+=strlen(word); actuallyMoveAhead();
		 word=presently();
		if(checkForMatch(word,"=")) 
		{
			i+=1;col+=strlen(word); actuallyMoveAhead();
			
			expn();
		} 
		else 
		{
			printError("=");;
		}
	}
}

void expn() 
{
	printf("in expn word = %s\n",word);// =	
	word=lookahead();
	printf("in expn word = %s\n",word);// =	
	t_type=getTokenType();
	if (checkForMatch(t_type,"Identifier") || checkForMatch(t_type,"Numeric Constant")) 
	{
		simple_expn();
		eprime();
		printf("back in expn word = %s\n",word);
	} 
	else {
		printError("a valid exp");;
	}
}

void eprime() 
{	

	printf("in eprime %s\n",word);
	word=lookahead();
	printf("in eprime %s\n",word);
	if (checkForMatch(word,"==") || checkForMatch(word,"!=") || checkForMatch(word,"=") || checkForMatch(word,"=") || checkForMatch(word,"") || checkForMatch(word,"")) 
	{
		// the = here takes care of multiple innitialisations like a = b = c
		relop();
		simple_expn();
		printf("back in eprime\n");
	}
}

void simple_expn() 
{
	printf("in sinmple expn word = %s\n",word);
	word=lookahead();
	t_type=getTokenType();
		printf("in sinmple expn word = %s\n",word);
	if (checkForMatch(t_type,"Identifier") || checkForMatch(t_type,"Numeric Constant")) 
	{
		//actuallyMoveAhead();
		term();
		seprime();
	}
	printf("back in simple_expn\n");
}

void seprime() 
{
	
	printf("in seprime word = %s\n",word);
	word=lookahead();
	printf("in seprime word = %s\n",word);
	if (checkForMatch(word,"+") || checkForMatch(word,"-")|| checkForMatch(word,"*")) 
	{
		addop();
		term();
		seprime();
	}
}

void term() {
	
	printf("in term\n");
	word=lookahead();
	t_type=getTokenType();
	if (checkForMatch(t_type,"Identifier") || checkForMatch(t_type,"Numeric Constant")) 
	{
		factor();
		printf("in term curr_word = %s\n",curr_word );
		tprime();
		printf("back in term\n");
	} 
	else 
	{
		printError("a valid term");;
	}
}

void tprime() 
{
	printf("in tprime curr_word = %s, f = %d\n",curr_word,f);
	word=lookahead();
	printf("in tprime word = %s\n",word);
	if (checkForMatch(word,"*") || checkForMatch(word,"/") || checkForMatch(word,"%")) 
	{
		mulop();
		word=lookahead();
		factor();
		tprime();
	}
}

void factor() 
{
	printf("in facotr\n");
	word=lookahead();
	printf("factor %s\n",word );
	t_type=getTokenType();
	if (checkForMatch(t_type,"Identifier") || checkForMatch(t_type,"Numeric Constant")) 
	{
		if(!lookupId(table,getCurrentToken()))
		{	
			printf("token not found\n");
			printError("token is not in ST");
		}

		i+=1;col+=strlen(word); actuallyMoveAhead();
		
	} 
	else 
	{
		printError("a valid factor");;
	}
}

void decision_stat() 
{
	printf("In decision_stat word = %s\n",word);
	word=lookahead();
	if(checkForMatch(word,"if")) 
	{
		i+=1;col+=strlen(word); actuallyMoveAhead();
		 word=presently();
		if(checkForMatch(word,"(")) 
		{
			i+=1;col+=strlen(word); actuallyMoveAhead();
			
			expn();
			printf("back in decision_stat\n");
			 word=presently();
			if(checkForMatch(word,")")) 
			{
				i+=1;col+=strlen(word); actuallyMoveAhead();
				 word=presently();
				if(checkForMatch(word,"{")) 
				{
					i+=1;col+=strlen(word); actuallyMoveAhead();
					printf("going to statement_list\n");
//					labeled_stat();
					statement_list();
					 word=presently();
					if(checkForMatch(word,"}")) 
					{
						i+=1;col+=strlen(word); actuallyMoveAhead();
						
						dprime();
					} 
					else 
					{
						printError("}");;
					}
				} 
				else 
				{
					printError("{");;
				}
			} 
			else 
			{
				printError(")");;
			}
		} 
		else 
		{
			printError("(");;
		}
	} 
	else if(checkForMatch(word,"switch"))
	{
		printf("matched switch\n");
		i+=1;col+=strlen(word); actuallyMoveAhead();
		 word=presently();
		if(checkForMatch(word,"(")) 
		{
			i+=1;col+=strlen(word); actuallyMoveAhead();
			
			expn();
			//printf("back in decision_stat word = %s\n",word);
			 //printf("**\n");
			 word=presently();

			if(checkForMatch(word,")")) 
			{
				i+=1;col+=strlen(word); actuallyMoveAhead();
				 word=presently();
				if(checkForMatch(word,"{")) 
				{
					i+=1;col+=strlen(word); actuallyMoveAhead();
					printf("going to statement_list &&&&&&&&&&&&&&&&&&&&&&&&& %s\n",word);
					statement_list();
					 printf("in decision_stat  word = %s",word);
					 word=presently();
					// if(strcmp(word,"case")==0)

					 printf("word = %s\n",word );
					if(checkForMatch(word,"}")) // } after all cases or default
					{
						i+=1;col+=strlen(word); actuallyMoveAhead();
						
					} 
					else 
					{
						printf("A\n");
						printError("}");
					}
				}
				else
				{
					printf("B\n");
					printError("{");
				}
			}
			else
			{
				printf("C\n");
				printError(")");
			}
		}
		else
		{
			printf("D\n");
			printError("(");
		}
	}
	else
	{
		printf("E\n");
		printError("a decision construct");
	}

}

void dprime() 
{
	printf("in dprime\n");
	word=presently();
	if(checkForMatch(word,"else")) 
	{
		i+=1;col+=strlen(word); actuallyMoveAhead();
		 word=presently();
		if(checkForMatch(word,"{")) 
		{
			i+=1;col+=strlen(word); actuallyMoveAhead();
			
			statement_list();
			 word=presently();
			if(checkForMatch(word,"}"))
			{
				i+=1;col+=strlen(word); actuallyMoveAhead();
				
			} 
			else 
			{
				printError("}");
			}
		} 
		else 
		{
			printError("{");;
		}
	}
}

void looping_stat() {
		
	printf("in looping_stat\n");
	word=lookahead();
	if(checkForMatch(word,"while")) 
	{
		i+=1;col+=strlen(word); actuallyMoveAhead();
		 word=presently();
		if(checkForMatch(word,"(")) 
		{
			i+=1;col+=strlen(word); actuallyMoveAhead();
			
			expn();
			 word=presently();
			if(checkForMatch(word,")")) 
			{
				i+=1;col+=strlen(word); actuallyMoveAhead();
				 word=presently();
				if(checkForMatch(word,"{")) 
				{
					i+=1;col+=strlen(word); actuallyMoveAhead();
					
					statement_list();
					 word=presently();
					if(checkForMatch(word,"}")) 
					{
						i+=1;col+=strlen(word); actuallyMoveAhead();
						
					}
					else 
					{
						printError("}");;
					}
				} 
				else 
				{
					printError("{");;
				}
			} 
			else 
			{
				printError(")");;
			}
		} 
		else 
		{
			printError("(");;
		}
	} 
	else if(checkForMatch(word,"for")) 
	{
		i+=1;col+=strlen(word); actuallyMoveAhead();
		 word=presently();
		if(checkForMatch(word,"(")) 
		{
			i+=1;col+=strlen(word); actuallyMoveAhead();
			
			assign_stat_loop();
			 word=presently();
			if(checkForMatch(word,";")) 
			{
				i+=1;col+=strlen(word); actuallyMoveAhead();
				
				expn();
				 word=presently();
				if(checkForMatch(word,";")) 
				{
					i+=1;col+=strlen(word); actuallyMoveAhead();
					
					assign_stat_loop();
					 word=presently();
					if(checkForMatch(word,")")) 
					{
						i+=1;col+=strlen(word); actuallyMoveAhead();
						 word=presently();
						if(checkForMatch(word,"{")) 
						{
							i+=1;col+=strlen(word); actuallyMoveAhead();
							
							statement_list();
							 word=presently();
							if(checkForMatch(word,"}"))
							{
								i+=1;col+=strlen(word); actuallyMoveAhead();
								
							} 
							else 
							{
								printf("1");printError("}");;
							}
						} 
						else 
						{
							printf("2");printError("{");;
						}
					} 
					else 
					{
						printf("3");printError(")");;
					}
				} 
				else 
				{
					printf("4");printError(";");;
				}
			} 
			else 
			{
				printf("5");printError(";");;
			}
		} 
		else 
		{
			printf("6");printError("{");;
		}
	}
	 else 
	 {
		printf("7");printError("a looping construct");;
	}
}

void relop() 
{
	word=presently();
	if (checkForMatch(word,"==") || checkForMatch(word,"!=") || checkForMatch(word,"=") || checkForMatch(word,"=") || checkForMatch(word,"") || checkForMatch(word,"")) 
	{
		i+=1;col+=strlen(word); actuallyMoveAhead();
		
	} 
	else 
	{
		printError("a relop");;
	}
}

void addop() {
	//word=presently();
	if (checkForMatch(word,"+") || checkForMatch(word,"-")) 
	{
		actuallyMoveAhead();
		i+=1;col+=strlen(word); actuallyMoveAhead();
		
	} 
	else 
	{
		printError("an addop");;
	}
}

void mulop() 
{
	//word=presently();
	if (checkForMatch(word,"*") || checkForMatch(word,"/") || checkForMatch(word,"%")) {
		actuallyMoveAhead();
		i+=1;col+=strlen(word); actuallyMoveAhead();
		
	} 
	else 
	{
		printError("a mulop");;
	}
}

// ----------------------------

// void parse_input (char *intext) 
// {

// 	strcpy(buffer, intext);

// 	// Make a temp copy of the string
// 	char *cp = (char *)malloc(LENGTH * sizeof(char));
// 	strcpy(cp, buffer);

// 	char *token = (char *)malloc(256 * sizeof(char));

// 	do {
// 		// strsep - extract token from string, returns null if token is not found.
// 		token = strsep(&cp, delimiters);
// 		printf("token = %s\n",token );
// 		if (token != NULL && strlen(token) > 0) {
// 			strcpy(input[count++], token);
// 			// printf("%s || ", input[k-1]);
// 		}

// 	} while (token != NULL);
// 	strcpy(input[k], "$");

// 	program();

// }

int main () 
{

	char *intext = (char *)malloc(LENGTH * sizeof(char));
	//	int k = 0;

	FILE *fa1=fopen("out1.txt","r");
	fread(intext,1,2048,fa1);
	yy_scan_string(intext);	
	int k=0;
	while(1)
	{
			tk=yylex();
			if(tk==NULL)
				break;

			printf("token=  %s, type = %s\n",tk->lexeme, tk->type );
			count++;
	}
	printf("count = %d\n",count );
	yy_scan_string(intext);
	//creating symbol table
	s_no=0;
	int n_rows=50;
	table=createTable(n_rows);
	int cnt=0;
	FILE *fa=fopen("out1.txt","r");
	char *str=malloc(100*sizeof(char));

	total_scope=malloc(100*sizeof(char));

	while(1)
	{
			int p=0;
			str=fgets(str,100,fa);//gotten a line
			if(str==NULL)
				break;
			yy_scan_string(str);
			while((tk=yylex())) 
			{
				arr[p++]=tk;/* in arr we have the array of tokens in a row*/
			}
			func(arr,p,table,&total_scope,&s_no); 	
	}

	printf("table has:******************************************************************************************************\n");
	printf("Format:\n");
	printf("s_no\tcorr_id\t\tnme\t\tsize\t\ttyp\t\tscope\t\tn(args)\t\tret_type\t\targs\n");
	for(int i=0;i<60;i++)
		printf("--");
			printf("\n");

	for(int order=0;order<1000;order++)
	{
		
		for(int i=0;i<50;i++)
		{
			Node* beg=table->tab[i];
	
			while(beg!=NULL)
			{
				if(beg->val->sr_no==order)
				{printf("%d\t%s\t\t%s\t\t%d\t\t%s\t\t%s\t\t%d\t\t%s\t\t\t",beg->val->sr_no,beg->val->corr_id,beg->val->lexeme,beg->val->size,beg->val->type,beg->val->scope,beg->val->no_of_args,beg->val->ret_type);
			
				if(beg->val->args!=NULL)
							{	
								for(int m=0;m<50;m++)
								{

										if(beg->val->args[m]!=NULL)
										printf("%s\t",beg->val->args[m] );
								}
							}
							printf("\n");

				}
				beg=beg->next;
				
			}

		}
	}
	printf("table over******************************************************************************************************\n");
	yy_scan_string(intext);
	printf("in name =\n %s\ncount=%d\n",intext,count );
	program();
	return 0;
}