#include <stdio.h>
#include <ctype.h>
#include "lexel.c"
#include <string.h>
char *lookahead;
int i=0;
FILE *in;

void proc_t();
void proc_e()
{
   lookahead=getNextToken(in);
  if(strcmp(lookahead,"NUMBER")==0)
  {
    lookahead=getNextToken(in);
     proc_t();
  }

  else
  {
    printf("\nError in proc_e");
  }

  
  if(strcmp(lookahead,"EOL")==0)
   printf("\nSuccessful");
  else
   printf("\nError in EOL");
}

void proc_t()
{
   //lookahead=getNextToken(in);
   if(strcmp(lookahead,"MUL")==0)
   {
     lookahead=getNextToken(in);
      proc_t();
   
      if(strcmp(lookahead,"NUMBER")==0)
      {
        lookahead=getNextToken(in);
        proc_t();
      }
     
    else
    {
      printf("\nError in proc_t");
    }
   }

   else
     return;
 
}


int main()
{
  in=fopen("file.c","r");
  lookahead=getNextToken(in);
  proc_e();
  proc_e();
  return 0;
}
