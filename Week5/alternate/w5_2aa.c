#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int i=0;

char input[30];

void procE();
void procEE();
void procT();
void procF();
void procTT();

void procE()
{
	procT();
	procEE();
}

void procEE()
{
	if(input[i]=='+')
	{
		i++;
		procT();
		procEE();
	}
}

void procT()
{
	procF();
	procTT();
}

void procTT()
{
	if(input[i]=='*')
	{
		i++;
		procF();
		procTT();
	}
}

void procF()
{
	if(input[i]=='(')
	{
		i++;
		procE();
		if(input[i]==')')
			i++;
		else
		{
			printf("\n ERROR \n");
			exit(0);
		}	
	}
	else if(input[i]=='i'&& input[i+1]=='d')
		i+=2;
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
	//input[k]='$';
	k=k-1;
	procE();
	if(input[i]=='$' && i==k)
		printf("\n Matched string \n");
	else
		printf("\n Error \n");
	return 0;
}