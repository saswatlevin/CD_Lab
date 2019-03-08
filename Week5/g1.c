#include <stdio.h>
#include <stdlib.h>
#include "token.c"

Node procT1(FILE *fp, Node token);
Node procT(FILE *fp, Node token);
Node procS(FILE *fp);

int done=0;

Node procT1(FILE *fp, Node token)
{
    if(token == NULL)
        token = getNextToken(fp);
	if(strcmp(token->word, ",")==0)
	{
        //printf("E\n");
        token = procS(fp);
        token = procT1(fp, token);
        return token;
	}
	else if(strcmp(token->word, "$")==0)
	{
        printf("Success\n");
        done=1;
    }
	else
    {
        //printf("E %s\n", token->word);
        return token;
    }
	return NULL;
}

Node procT(FILE *fp, Node token)
{
    token = procS(fp);
    token = procT1(fp, token);
    return token;
}

Node procS(FILE *fp)
{
	Node token = getNextToken(fp);
	if(strcmp(token->word, "a")==0)
	{
        Node token = getNextToken(fp);
        if(strcmp(token->word, "$")==0)
        {
            printf("Success\n");
            done=1;
        }
        else
        {
            //printf("E\n");
            return token;
        }
	}
	else if(strcmp(token->word, ">")==0)
	{
        Node token = getNextToken(fp);
        if(strcmp(token->word, "$")==0)
        {
            printf("Success\n");
            done=1;
        }
        else
        {
            //printf("E\n");
            //printf("%s\n", token->word);
            return token;
        }
	}
	else if(strcmp(token->word, "(")==0)
	{
        Node token = procS(fp);
        if(token==NULL)
            printf("Yes\n");
        token = procT1(fp, token);
        if(token == NULL)
            token = getNextToken(fp);
        if(strcmp(token->word, ")")==0)
        {
            //printf("E\n");
            token = getNextToken(fp);
            if(strcmp(token->word, "$")==0)
            {
                //printf("E\n");
                printf("Success\n");
                done=1;
            }
            else return token;
        }
        else
        {
            printf("Error1\n");
            exit(0);
        }
	}
	else
    {
        printf("Error2\n");
        exit(0);
    }
    return NULL;
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

	Node token = procS(fp);
	if(done==0)
        printf("Errord\n");

	return 0;
}

