#include <stdio.h>
#include <stdlib.h>
#include "token.c"

Node procE(FILE *fp, Node token);
Node procE1(FILE *fp, Node token);
Node procT(FILE *fp, Node token);
Node procT1(FILE *fp, Node token);
Node procF(FILE *fp, Node token);

int done=0, brack=0;

Node procF(FILE *fp, Node token)
{
    //printf("%s\n", token->word);
    if(token==NULL)
        token = getNextToken(fp);
    if(strcmp(token->word, "(")==0)
    {
        //printf("E\n");
        brack=1;
        token=getNextToken(fp);
        //printf("%s\n", token->word);
        token = procE(fp, token);
        //printf("%s\n", token->word);
        if(token==NULL)
            token=getNextToken(fp);
        if(strcmp(token->word, ")")==0)
        {
            brack=0;
            //printf("E\n");
            token=getNextToken(fp);
            if(strcmp(token->word, "$")==0 && brack==0)
            {
                printf("Success\n");
                done=1;
                exit(0);
            }
            else
                return token;
        }
        else
        {
            printf("Error1\n");
            exit(0);
        }
    }
    else if(strcmp(token->word, "id")==0)
    {
        token=getNextToken(fp);
        if(strcmp(token->word, "$")==0 && brack==0)
        {
            printf("Success\n");
            done=1;
            exit(0);
        }
        else
        {
            //printf("%s\n", token->word);
            return token;
        }
    }
    else
    {
        printf("Error\n");
        exit(0);
    }
    return NULL;
}

Node procT1(FILE *fp, Node token)
{
    if(token==NULL)
        token = getNextToken(fp);
    if(strcmp(token->word, "*")==0)
    {
        token = procF(fp, token);
        token = procT1(fp, token);
    }
    else if(brack==0)
    {
        token=getNextToken(fp);
        if(strcmp(token->word, "$")==0 && brack==0)
        {
            printf("Success\n");
            done=1;
            exit(0);
        }
    }
    return token;
}

Node procT(FILE *fp, Node token)
{
    token = procF(fp, token);
    token = procT1(fp, token);
    return token;
}

Node procE1(FILE *fp, Node token)
{
    if(token==NULL)
        token = getNextToken(fp);
    if(strcmp(token->word, "+")==0)
    {
        token = procT(fp, token);
        token = procE1(fp, token);
    }
    if(strcmp(token->word, "$")==0 && brack==0)
    {
        printf("Success\n");
        done =1;
        exit(0);
    }
    return token;
}

Node procE(FILE *fp, Node token)
{
    if(token==NULL)
        token=getNextToken(fp);
    //printf("E%s\n", token->word);
    token = procT(fp, token);
    token = procE1(fp, token);
    return token;
}

int main()
{
	FILE *fp = fopen("grammar.c", "r");
	//a and > and (a) and (a,>) and (>,>) and ((a)) and ((,))
	if(fp==NULL)
	{
		printf("File not found\n");
		exit(0);
	}
	//int line=1, col=1;

	Node token = procE(fp, NULL);
	if(done==0)
        printf("Errord\n");

	return 0;
}

