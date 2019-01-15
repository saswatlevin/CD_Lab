#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 80
int main()
{
  FILE *f_in;
  char* sa;
  sa = malloc(MAX*sizeof(char));

  char* keyword_list[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", 
                        "else", "enum", "extern", "float", "or", "goto", "if", "int", "long", "register", 
                        "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", 
                        "union", "unsigned", "void", "volatile", "while"};


  f_in = fopen("test33.c", "r");
  if(f_in == NULL){
    printf("File does not exist.\n");
    return 0;
  }

  int col, line=1;


  while(fgets(sa, MAX, f_in) != NULL)
  { //printf("%s\n", sa);


    for(int i=0; i<32; i++)
    {
      char* match = strstr(sa, keyword_list[i]);
      
      if(match != NULL)
      {
        //printf("%s\n", match);
        col = match - sa + 1;
        if(col!=1)
        {
          if((*(match-1) == ' ' || *(match-1) == '\t' ))
          {
            printf("%s line:%d col:%d\n",keyword_list[i], line, col );
          }
        }
        else
        {
          printf("%s line:%d col:%d\n",keyword_list[i], line, col );
        }
        
      }
    }

    line++;
    
  }
  fclose(f_in);
  return 0;

}