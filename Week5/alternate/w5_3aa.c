#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int i=0;

char input[30];

void procS();
void procA();
void procAA();
void procB();

void procE()
{
	if(input[i]=='a')
	{
		i++;
		procA();
		if(input[i]=='c')
		{
			i++;
			procB();
			if(input[i]=='e')
				i++;
			else
			{
				printf("\n ERROR \n");
				exit(0);
			}
		}
		else
		{
			printf("\n ERROR \n");
			exit(0);
		}
	}
	else
	{
		printf("\n ERROR \n");
		exit(0);
	}
}

void procA()
{
	if(input[i]=='b')
	{
		i++;
		procAA();
	}
	else
	{
		printf("\n ERROR \n");
		exit(0);
	}
}

void procAA()
{
	if(input[i]=='b')
	{
		i++;
		procAA();
	}
}

void procB()
{
	if(input[i]=='d')
		i++;
	else
	{
		printf("\n ERROR \n");
		exit(0);
	}
}


int main()
{
	
	printf("\n Enter the string:");
	scanf(" %s",input);
	int k=strlen(input);
	input[k]='$';
	procE();
	if(input[i]=='$' && i==k)
		printf("\n Matched string \n");
	else
		printf("\n Error \n");
	return 0;
}