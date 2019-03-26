#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int i=0;

char input[30];

void procT();

void procS()
{
	if(input[i]=='a')
		i++;
	else if(input[i]=='>')
			i++;
	else if(input[i]='(')
		{
			i++;
			procT();
			if(input[i]==')')
				i++;
			else
			{
				printf("\n Error occured");
				exit(0);
			}
		}
	else
	{
		printf("\n Error occured");
		exit(0);
	}
}

void procTT()
{
	if(input[i]==',')
	{
		i++;
		procS();
		procTT();
	}
}

void procT()
{
	procS();
	procTT();
}



int main()
{
	
	printf("\n Enter the string:");
	scanf(" %s",input);
	int k=strlen(input);

	input[k]='$';
	procS();
	if(input[i]=='$' && i==k)
		printf("\n Matched string");
	else
		printf("\n Error");
	return 0;
}