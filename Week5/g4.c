#include <stdio.h>
#include <stdlib.h>
#include "token.c"

Node lexp(FILE *fp, Node token);
Node lexp_seq(FILE *fp, Node token);
Node lexp_seq1(FILE *fp, Node token);
Node aterm(FILE *fp, Node token);
Node list(FILE *fp, Node token);

int done=0, brack=0;

Node lexp_seq1(FILE *fp, Node token)
{
    if(brack==1 && strcmp(token->word,")")==0)
        return token;
    token = lexp(fp, token);
    token = lexp_seq1(fp, token);
    if(token==NULL)
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

Node lexp_seq(FILE *fp, Node token)
{
    token = lexp(fp, token);
    token = lexp_seq1(fp, token);
    return token;
}

Node list(FILE *fp, Node token)
{
    if(token==NULL)
        token=getNextToken(fp);
    //printf("L%s\n", token->word);
    if(strcmp(token->word, "(")==0)
    {
        //printf("EL\n");
        brack=1;
        token=getNextToken(fp);
        token=lexp_seq(fp, token);
        //printf("L%s\n", token->word);
        if(token==NULL)
            token=getNextToken(fp);
        if(strcmp(token->word, ")")==0)
        {
            brack=0;
            token=getNextToken(fp);
            if(strcmp(token->word, "$")==0 && brack==0)
            {
                printf("Success\n");
                done=1;
                exit(0);
            }
            else
            {
                printf("Error\n");
                exit(0);
            }
        }
    }
    //printf("%s\n", token->word);
    return token;
}

Node aterm(FILE *fp, Node token)
{
    if(token==NULL)
        token = getNextToken(fp);
    //printf("A%s\n", token->word);
    if(strcmp(token->type, "NUMERIC CONSTANT")==0)
    {
        //printf("EA\n");
        token=getNextToken(fp);
        if(strcmp(token->word, "$")==0)
        {
            if(brack==0)
            {
                printf("Success\n");
                done=1;
                exit(0);
            }
            else
            {
                printf("Error\n");
                exit(0);
            }
        }
        else
            return token;
    }
    else if(strcmp(token->type, "IDENTIFIER")==0)
    {
        token=getNextToken(fp);
        if(strcmp(token->word, "$")==0)
        {
            if(brack==0)
            {
                printf("Success\n");
                done=1;
                exit(0);
            }
            else
            {
                printf("Error\n");
                exit(0);
            }
        }
        else
            return token;
    }
    return token;
}

Node lexp(FILE *fp, Node token)
{
    if(token==NULL)
        token=getNextToken(fp);
    //printf("E%s\n", token->word);
    token = aterm(fp, token);
    //printf("R%s\n", token->word);
    token = list(fp, token);
    //printf("RL%s\n", token->word);
    return token;
}

int main()
{
    FILE *fp = fopen("grammar.c", "r");
	//(11.2e02 abcde) and (11.02e02
	if(fp==NULL)
	{
		printf("File not found\n");
		exit(0);
	}
	//int line=1, col=1;

	Node token = lexp(fp, NULL);
	if(done==0)
        printf("Errord\n");

	return 0;
}


