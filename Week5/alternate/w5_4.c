#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i=0;
char input[50];

void lexp();
void aterm();
void list();
void lexp_seq();
void lexp_seqlexp();

void lexp()
{   
	printf("\nIn lexp");
	aterm();
	list();
}

void aterm()
{   
	
	printf("\nIn aterm");
	
	if((input[i]>='0' && input[i]<='9')||(input[i]>='a' && input[i]<='z')||(input[i]>='A' && input[i]<='Z'))
		i++;
	else
	{
      printf("\naterm error");
	}
}

void list()
{
	if(input[i]=='(')
	{
       i++;
       lexp_seq();
	   if(input[i]==')')
	   	i++;
	   else
	   	printf("\nError in )");
	}
   
}

void lexp_seq()
{
   lexp_seqlexp();
   lexp();
}

void lexp_seqlexp()
{
	if(input[i]=='='||input[i]=='>'||input[i]=='<')
		i++;
}

int main(int argc, char *argv[])
{  
    

    printf("\nEnter a string ");
    scanf("%s",input);
    lexp();
    int k=strlen(input);
    k=k-1;
    if(input[i]=='$' && i==k)

    	printf("\nSuccess");
	else
		printf("\nError");
    return 0;
}