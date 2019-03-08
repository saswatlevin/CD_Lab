#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.c"
char *lookahead;
void procE();
void procT();
void procF();
void procEE();
void procTT();


FILE *in;
char *lookahead;


void procE()
{  
   printf("\nIn procE");	
   procT();
   procEE();
}

void procEE()
{
	printf("\nIn procEE");
	
	lookahead=getNextToken(in);
    printf("\nLookahead=%s\t",lookahead);

	if((strcmp(lookahead,"+")==0))
	{
		lookahead=getNextToken(in);
		printf("\nInside if EE Lookahead=%s\t",lookahead);

		procT();
		procEE();
	}

}


void procT()
{   
    printf("\nIn procT");
	procF();
	procTT();
}

void procTT()
{
	printf("\nIn ProcTT");
    lookahead=getNextToken(in);
	printf("\nLookahead=%s",lookahead);
    
	if(strcmp(lookahead,"*")==0)
	{
		lookahead=getNextToken(in);
		printf("\nInside if TT Lookahead=%s\t",lookahead);

		procF();
		procTT();
	}
}


void procF()
{
	printf("\nIn ProcF");
	lookahead=getNextToken(in);
	printf("\nLookahead=%s\t",lookahead);
    
    if(strcmp(lookahead,"(")==0)
	{
		lookahead=getNextToken(in);
		procE();
		if(strcmp(lookahead,")")==0)
			lookahead=getNextToken(in);
		else
		{
			printf("\n ERROR \n");
			exit(0);
		}	
	}
	else if(strcmp(lookahead,"id")==0)
		lookahead=getNextToken(in);
	else
	{
		printf("\n ERROR \n");
		exit(0);
	}
	

}




void main()
{  
   in=fopen("strings.c","r");
    
     
    if(in==NULL){
    	printf("\nFile not found");
    	exit(0);
    }

    
    procE();
    
    
    printf("\nLookahead=%s",lookahead);
    
    if(strcmp(lookahead,"$")==0)

    	printf("\nSuccess");
	else
		printf("\nError");

	fclose(in);
}