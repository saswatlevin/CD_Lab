#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fa,*fb;
  
	int ca,cb;
	fa=fopen("test1.c","r");
	if(fa==NULL){
		printf("\nCan't open file\n");
		exit(0);
	}
   fb=fopen("test2.c","w");
   ca=getc(fa);
   while(ca!=EOF){
   	//printf("\nIn 1st while loop");
   	if(ca=='/')
   	{
   	//printf("\nInside if 1");
   	cb=getc(fa);	
   	
   	if(cb=='/')
   	{ 
      //printf("\nIn if 2");
      while(ca!='\n')
      	ca=getc(fa);
   	}

   	else if(cb=='*')
   	{
   	do {
   	       while(ca!='*')
   	             ca=getc(fa);
   	        ca=getc(fa);     	
        }while(ca!='/');
    }
    
    else {
    putc(ca,fb);
    putc(cb,fb);
    }
}

else
putc(ca,fb);
ca=getc(fa);
}

fclose(fa);
fclose(fb);
return 0;
}    



  