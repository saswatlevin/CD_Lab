#include <stdio.h>

int main()
{
  FILE *f_in, *f_out;
  int ca, cb;

  f_in = fopen("test11.c", "r");
  if(f_in == NULL){
    printf("File does not exist.\n");
    return 0;
  }

  f_out = fopen("test22.c", "w");

  ca = getc(f_in);
  while(ca != EOF)
  {
    if(ca == '\t')
    {
      putc(' ', f_out);
    }

    else if(ca == ' ')
    { 
      cb = getc(f_in);

      while(cb == ' ')
      {
        cb = getc(f_in);
      }

      putc(ca, f_out);
      putc(cb, f_out);
    }

    else{
      putc(ca, f_out);
    }

    ca = getc(f_in);
  }

  fclose(f_in);
  fclose(f_out);

  return 0;
}