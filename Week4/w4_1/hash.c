#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TableLength 30


enum tokenType{
    EOFILE=-1,

    RELATIONAL_OPERATOR=0,

    IDENTIFIER=1,

    KEYWORD=2,

    NUMERICAL_CONSTANT=3,

    LOGICAL_OPERATOR=4,

    ARITHMETIC_OPERATOR=5,

    SPECIAL_SYMBOL=6,

    SYMBOL=7,

    ASSIGNMENT_OPERATOR=8
};




struct token
{
    char *lexeme;
    int index;
    int rowno,colno;
    enum tokenType type;
    int scope;
    int varType;
    
}token;

struct token *tk;

struct ListElement{
   struct token *tok;
   struct ListElement *next;
};

struct ListElement *TABLE[TableLength];


void initialize(){
   for(int i=0;i<TableLength;i++){
       TABLE[i]=NULL;
     }
   }
void Display(){
      //iterate thru the Linked List and display
      struct ListElement *disp=TABLE[0];
      while(disp->next!=NULL)
      {
           printf("%s\t%d\t%d\t%d\t%d\t",disp->tok->lexeme,disp->tok->index,disp->tok->rowno,disp->tok->colno,disp->tok->type);
           disp=disp->next;
      }
}

int HASH(char *str){
        //Develop an OpenHash function on a string
        int len=0,i=0;
        int hash_val=0;
        len=strlen(str);
        printf("\nIn HASH");
        for(i=0;str[i]!='\0';++i){
            hash_val=(hash_val+str[i])%len;
        }
        
        return hash_val; 
}

int SEARCH(char* str)
{
      //Write a search function to check whether the lexeme exists in the symbol table
      struct ListElement *ser=TABLE[0];
      while(ser->next!=NULL)
      {
         if(strcmp(str,ser->tok->lexeme)==0){
            printf("\nLexeme %s found at position %d",ser->tok->lexeme,(ser->tok->index+1));
            break;
         }
          ser=ser->next;
      }
}

void INSERT(struct token *tk){
     if(SEARCH(tk->lexeme)==1){
        return;//Before returning we check if element present already
     }
    int val=HASH(tk->lexeme);
    struct ListElement* cur=(struct ListElement*)malloc(sizeof(struct ListElement));

    cur->tok=tk;
    cur->next=NULL;
    if(TABLE[val]==NULL){
      TABLE[val]=cur;
    }
   else{
        struct ListElement* ele=TABLE[val];
         while(ele->next!=NULL){
           ele=ele->next;
         }
         ele->next=cur;
  }
}


int main(int argc,char *argv[]){
   
   char l[100];
   printf("\nEnter a lexeme");
   scanf("%s",l);
   
   INSERT();
   return 0; 
}
