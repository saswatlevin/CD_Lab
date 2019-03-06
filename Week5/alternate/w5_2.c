#include <stdio.h>
#include <ctype.h>
#include "lexel.c"
#include <string.h>
char *lookahead;
int i=0;
FILE *in;

void one();
void two();
void three();

void proc_b1();
void proc_b2();
void proc_t();

void one_b1();
void two_b1();
void three_b1();

void proc_b1()
{
lookahead=getNextToken(in);
   if(strcmp(lookahead,"(")==0)
      {
        lookahead=getNextToken(in);
        proc_b2();
      }  
   
   if(strcmp(lookahead,"id")==0)
      {
        lookahead=getNextToken(in);
        proc_b2();
      }  
  
   if(strcmp(lookahead,")")==0)
      {
        lookahead=getNextToken(in);
        proc_b2();
      }  
  
  else
  {
    printf("\nError in proc_b1");
  }

  if(strcmp(lookahead,"$")==0)
   printf("\nSuccessful");
  else
   printf("\nError in $");

}



void proc_b2()
{
 if(strcmp(lookahead,"+")==0)
   {
     lookahead=getNextToken(in);
      proc_b2();

   if(strcmp(lookahead,"(")==0)
      {
        lookahead=getNextToken(in);
        proc_b2();
      }      
     

      if(strcmp(lookahead,"id")==0)
      {
        lookahead=getNextToken(in);
        proc_b2();
      }
     
     if(strcmp(lookahead,")")==0)
      {
        lookahead=getNextToken(in);
        proc_b2();
      }  
    
    if(strcmp(lookahead,"*"))
     {
     lookahead=getNextToken(in);
     proc_b2();
     }
     
     /*if(strcmp(lookahead,"(")==0)
      {
        lookahead=getNextToken(in);
        proc_b2();
      }*/  

      if(strcmp(lookahead,"id")==0)
      {
        lookahead=getNextToken(in);
        proc_b2();
      }
     
     /*if(strcmp(lookahead,")")==0)
      {
        lookahead=getNextToken(in);
        proc_b2();
      }*/  
     
    else
    {
      printf("\nError in proc_b2");
    }
   }

   else
     return;
 
}



void proc_e()
{
   lookahead=getNextToken(in);
   

   if(strcmp(lookahead,"id")==0)
      {
        lookahead=getNextToken(in);
        proc_t();
      }  
  
  else
  {
    printf("\nError in proc_e");
  }

  if(strcmp(lookahead,"$")==0)
   printf("\nSuccessful");
  else
   printf("\nError in $");
  
}





void proc_t()
{
   //lookahead=getNextToken(in);
   if(strcmp(lookahead,"+")==0)
   {
     lookahead=getNextToken(in);
      proc_t();
    
     

      if(strcmp(lookahead,"id")==0)
      {
        lookahead=getNextToken(in);
        proc_t();
      }
     
    
     
     if(strcmp(lookahead,"*"))
     {
     lookahead=getNextToken(in);
     proc_t();
     }
  
    if(strcmp(lookahead,"id")==0)
      {
        lookahead=getNextToken(in);
        proc_t();
      }
    if(strcmp(lookahead,"$")==0)
      {
        printf("\nSuccess");
      }
     
    else
    {
      printf("\nError in proc_t");
    }
   }

   else
     return;
 
}


void one_b1()
{
  proc_b1();
}

void two_b1()
{
  proc_b1();
  proc_b1();

}


void one()
{
  proc_e();
}

void two()
{
  proc_e();
  proc_e();
}

void three()
{
  proc_e();
  proc_e();
  proc_e();
  
}

int main()
{
  in=fopen("file2.c","r");
  
  char x;
  int count=0;
  
  
  lookahead=getNextToken(in);
  while((x=fgetc(in))!=EOF)
  {
    count=count+1;
  }    
  //fclose(in);
  //in=fopen("file2.c","r");
  count=count-1;
  printf("\nLength=%d\t",count);
  fseek(in, 0, SEEK_SET);
  if(count==3)
    one();
  
    
  
  //fclose(in); 
  return 0; 
}
