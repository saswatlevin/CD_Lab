#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void procE();
void procT();
void procF();
void procEE();
void procTT();

char input[30];
int i=0;

void procE()
{
   procT();
   procEE();
}

void procEE()
{
	if(input[i]=='+'){
		i++;
		procT();
	    procEE();
	}
  /*else
  {
  	printf("\nError in +");
    exit(0);
  }*/
}

void procT()
{
	procF();
	procTT();
}

void procTT()
{
    if(input[i]=='*')
    {   i++;
        procF();
        procTT();
    }
    /*else
    {
    printf("\nError in *");
    exit(0);	
    }*/	
}

void procF()
{
	if(input[i]=='('){
		i++;
		procE();
		if(input[i]==')')
			i++;
	    else
	    {
	    printf("\nError in brackets");	
	    }
	 } 
	 else if(input[i]=='i' && input[i+1]=='d')
	    	i=i+2;

	    else{
	    	printf("\nError in id");
	        exit(0);
	    }
	  }
	  



int main(int argc, char *argv[])
{  
    

    printf("\nEnter a string ");
    scanf("%s",input);
    procE();
    int k=strlen(input);
    k=k-1;
    if(input[i]=='$' && i==k)

    	printf("\nSuccess");
	else
		printf("\nError");

	return 0;
}