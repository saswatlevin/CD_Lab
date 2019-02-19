#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TableLength 30

enum tokenType {EOFILE=-1, LESS_THAN,LESS_THAN_OR_EQUAL,GREATER_THAN,GREATER_THAN_OR_EQUAL,
EQUAL,NOT_EQUAL};

struct token
{
char *lexeme;
int index;
unsigned int rowno,colno;
enum tokenType type;
};

struct ListElement{
struct token tok;
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
}

int HASH(char *str){
//Develop an OpenHash function on a string
}

int SEARCH(char* str)
{
//Write a search function to check whether the lexeme exists in the symbol table
}

void INSERT(struct token tk){
if(SEARCH(tk,lexeme)==1){
return;//Before returning we check if element present already
}
int val=HASH(tk.lexeme);
struct ListElement* cur=(STRUCT ListElement*)malloc(sizeof(struct ListElement));

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
}}

