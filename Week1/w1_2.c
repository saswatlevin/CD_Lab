#include <stdio.h>
#define MAX 80

int main()
{
  FILE *f_in, *f_out;
  int ca, cb;
  char sa[MAX];
  f_in = fopen("test33.c", "r");
  if(f_in == NULL){
    printf("File does not exist.\n");
    return 0;
  }

  f_out = fopen("test44.c", "w");
  
  
  
  


  while(fgets(sa, MAX, f_in) != NULL)
  {
    if(sa[0] != '#'){
      fprintf(f_out, "%s", sa);
    }
  }

  fclose(f_in);
  fclose(f_out);

  return 0;
}