#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void procS();
void procT();
void procTT();

char input[30];
int i=0;

void procS(){
  
     if(input[i]=='a')
         i++;
      else if(input[i]=='>')
              i++;
       else if(input[i]=='('){
            i++; 
            procT();
        if(input[i]==')') 
            i++;
         else{
            printf("\nError in )");
            exit(0);
         }
       }
  else{
  printf("\nError in a");  
  exit(0);
}



}

void procT(){

  procS();
  procTT();

}

void procTT(){

  
    if(input[i]==','){
       i++;
       procS();
       procTT();     
     }


}

int main(int argc,char *argv[])
{
  printf("\nEnter the input string ");
  scanf("%s",input);
  procS(); 
  int k=strlen(input);
  if(input[i]=='$' && i==k)
  {
    printf("\nSuccess");
  }
  else
  {
    printf("\nError");	
  }
  
  return 0;
}
