#include <stdio.h>
#include <string.h>
#define SIZE 20

char input[20];

void S();
void T();
void TT();

int count;

void S()
{
	if(input[count]=='a')
		count++;
	else if (input[count]=='<')
		count++;
    else
    	T();    
    
}

void T()
{
	S();
	TT();
}

void TT()
{
	if(input[count]==',')
	{	count++;
        S();
        TT();
    }
}

int main()
{
int i;

printf("\nEnter input \t");

scanf("%s",input);
int len=strlen(input);

S();
if(input[count]=='$' && len==count-1)
	printf("\nSuccess");

else
	printf("\nFailure");

return 0;
}