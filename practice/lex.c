#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 
int isKeyword(char buffer[]){
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i, flag = 0;
	
	for(i = 0; i < 32; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			printf("\n %s , KEYWORD",buffer);
			flag = 1;
			break;
		}
        
        

return flag;
}


}

char isArithOp(char ch)
{

    if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
    {
       return ch;
    
    }
else
    return '@';
}
 

char isRelOp(char ch)
{
	
	
	
	
	if(ch=='<'){
    	//ch=buffer[i];
        return ch;
    }

    else if(ch=='>')
    {
    	//ch=buffer[i];
        return ch;
    }

    else if(ch=='=')
	{
		//ch=buffer[i];
        return ch;	
	}
  
  else{

	ch='@';
	return ch;
  }

}


char isLogOp(char ch)
{
	
	if(ch=='&'){
    	//ch=buffer[i];
        return ch;
    }

    else if(ch=='!')
    {
    	//ch=buffer[i];
        return ch;
    }

    else if(ch=='|')
	{
		//ch=buffer[i];
        return ch;	
	}
  
  else{

	ch='@';
	return ch;
  }
}


char isSpecialSymbol(char ch)
{
	if(ch=='#'||ch=='/'||ch==':'||ch==';'||ch=='{'||ch=='}'||ch=='('||ch==')'||ch=='['||ch==']'||ch==',')
	{
		return ch;
	}	
	return '@';
}


char isIdentifier(char ch){
	if(isalpha(ch)){
		return ch;
	}
}

int main(){
	char ch,buffer[10]; 
	FILE *fp;
	int i,j=0;
	
	fp = fopen("program.txt","r");
	
	if(fp == NULL){
		printf("\nerror while opening the file\n");
		exit(0);
	}
	
	while((ch = fgetc(fp)) != EOF){
   		


   		if(isArithOp(ch)!='@'){
   			
   			printf("\n %c , ARITHMETIC_OPERATOR\n",ch);
   		}
    
        
        if(isRelOp(ch)!='@'){

        		printf("\n %c , RELATIONAL_OPERATOR\n",ch);
        }
        
        if(isLogOp(ch)!='@'){

        	   printf("\n %c , LOGICAL_OPERATOR\n",ch);
        }

		if(isSpecialSymbol(ch)!='@'){

        	   printf("\n %c , SPECIAL_SYMBOL\n",ch);
        }

        if(isIdentifier(ch)!='@'){
        		printf("\n %c , IDENTIFIER\n",ch);
        }
		
		if(isalnum(ch)){
   			buffer[j++] = ch;
   		}



		if((ch == ' ' || ch == '\n') && (j != 0)){
   				
   			buffer[j] = '\0';
   			j = 0;
   				   				
   			if(isKeyword(buffer) == 0)
   					;
   			else
   				;
   		}
}
        
fclose(fp);
	
return 0;
}

