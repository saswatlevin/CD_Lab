#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
char c,buf[10];
FILE *fp=fopen("digit.c","r");
c=fgetc(fp);
if(fp==NULL) {
printf("\nCannot open file");
exit(0);	
}
while(c!=EOF)
{
int i=0;
buf[0]='\0';
if(c=='=')
{
	buf[i++]=c;
	c=fgetc(fp);
	           if(c=='=')
	           {
	           	buf[i++]=c;
	           	buf[i]='\0';
	           	printf("\nRelational operator:%s",buf);

	           }
else{
buf[i]='\0';
printf("\nAssignment Operator:%s",buf);	
}	
}

else 
{
if(c=='<'||c=='>'||c=='!')
{
buf[i++]=c;
c=fgetc(fp);
if(c=='=')
{
buf[i++]=c;

}	
buf[i]='\0';
printf("\n Relational operator:%s",buf);
}
else {
buf[i]='\0';	
}
}
c=fgetc(fp);


}
fclose(fp);
return 0;	
}
