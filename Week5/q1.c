#include <stdio.h>
#include <stdlib.h>
#include "token.c"

void procT(FILE *fp)
{
	Node token = getNextToken(fp);
	if(token != NULL)
	{
		char c= fgetc(fp);
		if(c==EOF)
		{
			printf("Success\n");
			return;
		}
		else
			ungetc(c, fp);
	}
	if(strcmp(token->word, "*")==0)
	{
		Node token = getNextToken(fp);
		if(token != NULL)
		{
			char c= fgetc(fp);
			if(c==EOF)
				return;
			else
				ungetc(c, fp);
		}
		if(strcmp(token->type, "NUMERIC CONSTANT")==0)
		{
			procT(fp);
		}
		else
			printf("Error\n");
	}
	else if(strcmp(token->word, "$")==0)
		printf("Success\n");
	else
		printf("Error\n");
}

void procE(FILE *fp)
{
	Node token = getNextToken(fp);
	if(token != NULL)
	{
		char c= fgetc(fp);
		if(c==EOF)
		{
			printf("Error\n");
			return;
		}
		else
			ungetc(c, fp);
	}
	if(strcmp(token->type, "NUMERIC CONSTANT")==0)
	{
		procT(fp);
	}
	else
		printf("Error\n");
}

int main()
{
	FILE *fp = fopen("grammar.c", "r");
	if(fp==NULL)
	{
		printf("File not found\n");
		exit(0);
	}
	//int line=1, col=1;

	procE(fp);

	return 0;
}