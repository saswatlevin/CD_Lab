
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
char buf[MAX];

int index;
unsigned int row,col;
unsigned int type;	
}token;

int line=1;

token a;

void getRelop()
{
//printf("\ngetRelop started\n");

char c;
FILE *fp=fopen("simple.c","r");
c=fgetc(fp);
if(fp==NULL) {
printf("\nCannot open file");
exit(0);	
}
while(c!=EOF)
{
int i=0;
a.buf[0]='\0';
if(c=='\n')
{
++line;	
}
else
{
;	
}

if(c=='=')
{
	a.buf[i++]=c;
	c=fgetc(fp);
	           if(c=='\n')
	           {
                ++line;	
                }
                else
                {
                ;	
                }
	           if(c=='=')
	           {
	           	a.buf[i++]=c;
	           	a.buf[i]='\0';
	           	printf("\nRelational operator:%s",a.buf);
                if(c=='\n'){
                ++line;	
                }
	           printf("line:%d",line);
	           }
else{
a.buf[i]='\0';
printf("\nAssignment Operator:%s",a.buf);	
printf("line:%d",line);
/*if(c=='\n'){
                line++;	
                }
	           printf("line:%d",line);*/
}	
}

else 
{
if(c=='<'||c=='>'||c=='!')
{
a.buf[i++]=c;
c=fgetc(fp);

if(c=='\n')
{
++line;	
}

if(c=='=')
{
a.buf[i++]=c;

}	
a.buf[i]='\0';
printf("\n Relational operator:%s",a.buf);
printf("line:%d",line);

}
else {
a.buf[i]='\0';	
}
}
c=fgetc(fp);


}
fclose(fp);

//printf("\ngetRelop finished\n");
}



void getRelCharType(char c)
{
//printf("\ngetType started\n");

if(c=='!')
{
printf(c);
}


//printf("\ngetType finished\n");
}


int getNextToken()
{




getRelop();
//fclose(fp);
}



int main(int argc,char* argv[])
{

/*char c,buf[10];
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
fclose(fp);*/
getNextToken();

return 0;
}
