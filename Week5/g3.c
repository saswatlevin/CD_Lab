#include <stdio.h>
#include <stdlib.h>
#include "token.c"

int procB(FILE *fp, int pos, Node token)
{
	//Node token = getNextToken(fp);
	if(token->word[pos]=='d')
        return pos+1;
	else
    {
        printf("Error1\n");
        return -1;
    }
}

int procA1(FILE *fp, int pos, Node token)
{
	//Node token = getNextToken(fp);
	if(token->word[pos]=='b')
	{
	    //printf("E\n");
	    pos+=1;
        int pos1 = procA1(fp, pos, token);
        if(pos1==-1)
            return -1;
        return pos1;
	}
	else if(pos+1 == strlen(token->word))
    {
        Node token = getNextToken(fp);
        if(strcmp(token->word, "$")==0)
        {
            printf("Success\n");
            return -1;
        }
    }
    return pos;
}


int procA(FILE *fp, int pos, Node token)
{
	//Node token = getNextToken(fp);
	if(token->word[pos]=='b')
	{
        int pos1 = procA1(fp, pos+1, token);
        if(pos1==-1)
            return -1;
        return pos1;
	}
	else
    {
        printf("Error3\n");
        return -1;
    }
}

void procS(FILE *fp)
{
	Node token = getNextToken(fp);
	//printf("%s\n", token->word);
	if(token->word[0]=='a')
	{
		int pos = procA(fp, 1, token);
		if(pos==-1)
            return;
		if(token->word[pos]=='c')
        {
            pos = procB(fp, pos+1, token);
            if(pos==-1)
                return;
            if(token->word[pos]=='e')
            {
                Node token = getNextToken(fp);
                if(strcmp(token->word, "$")==0)
                    printf("Success\n");
                else
                    printf("Error4\n");
            }
            else
                printf("Error5\n");
        }
        else
            printf("Error6\n");
	}
	else
		printf("Error7\n");
}

int main()
{
	FILE *fp = fopen("grammar.c", "r");
	//abcde$ and abbcde$
	if(fp==NULL)
	{
		printf("File not found\n");
		exit(0);
	}
	//int line=1, col=1;

	procS(fp);

	return 0;
}

