#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i;
char input[30];
void procS();
void procA();
void procAA();
void procB();

void procS(){
	printf("\nIn procS");	
	if(input[i]=='a'){
		i++;
		procA();
		
	if(input[i]=='c'){
	    i++;
	    procB();

    if(input[i]=='e')
    	i++;
    else{
    	printf("\nError in e");
    }
   
  }
 else
 {
 printf("\nError in c");	
   }
 }
}

void procA()
{
	if(input[i]=='b'){
		printf("\nIn procA");
		i++;
		procAA();
	
	}
   /*if(input[i-1]=='b' && input[i+1]=='b' && i>0){
  	printf("\nSuccess");
  	exit(0);
  }*/ 
}

void procAA()
{
	if(input[i]=='b'){
		i++;
	printf("\nIn procAA");	
	procAA();
	}
  /*if(input[i-1]=='b' && input[i+1]=='b' && i>0){
  	printf("\nSuccess");
  	exit(0);
  }*/
}

void procB()
{
	if(input[i]=='d'){
		i++;
	printf("\nIn procB");	
	}
    
}

int main(int argc, char *argv[])
{  
    

    printf("\nEnter a string ");
    scanf("%s",input);
    procS();
    int k=strlen(input);
    k=k-1;
    if(input[i]=='$' && i==k){

    	printf("\nSuccess");
	    printf("\nInput[i]=%c\t",input[i]);
	    printf("\ni=%d\t",i);
	}
	else{
		printf("\nError");
	    printf("\nInput[i]=%c\t",input[i]);
	    printf("\ni=%d\t",i);
	}

	return 0;
}