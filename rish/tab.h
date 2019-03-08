#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct token
{
		int sr_no;
		int size;//done1
		char *lexeme;//done1
		char* type; //done1
		char*scope;//done1
		int no_of_args;//done1
		char **args;
		char* ret_type;//done1
		char* corr_id;
};

typedef struct Node
{
	int key;
	struct token* val;
	struct Node* next;
}Node;

typedef struct Table
{
	Node **tab;// a 2D array of nodes is a table
}Table;


Table* createTable(int n_rows)
{
	Table *t = (Table*)malloc(sizeof(Table));
	t->tab=(Node**)malloc(sizeof(Node*)*n_rows);// total no. of rows is n_rows
	for(int i=0;i<50;i++)
		t->tab[i]=NULL;//length of each row is not fixed//(Node*)malloc(sizeof(Node)*50)

	return t;
}

int hashFunc(int inpKey)
{
	return inpKey%50;// so that the list no.(row no.) is always less than 50
}
void insert(Table *t,int inpKey, struct token* inpVal)
{
	int hash=hashFunc(inpKey);
	Node*  beg=t->tab[hash];//a list
	printf("hash= %d\n",hash );
	if(beg==NULL)
	{	t->tab[hash]=(Node*)malloc(sizeof(Node)*50);
		beg=t->tab[hash];
	}
	else
	{	while(beg->next!=NULL)//search in list
		{
//			printf("loop\n");
			beg=beg->next;
		}
		beg->next=(Node*)malloc(sizeof(Node));
		beg=beg->next;
	}
	beg->key=inpKey;
	beg->val=inpVal;
	beg->next=NULL;
//	printf("put %d %d\n",beg->key,beg->val );

}

int lookup(Table *t,struct token* search)
{

	int sum=0;
	for(int i=0;i<strlen(search->lexeme);i++)
		sum+=search->lexeme[i];
	int hash=hashFunc(sum);
	Node* beg=t->tab[hash];
	printf("hash= %d\n",hash );
	//printf("%s\n",beg );
	while(beg!=NULL)
	{
		printf("1111111111222111111111111111111122211111111111111111112221111111111%s %s %s %s\n",beg->val->lexeme,beg->val->scope,search->lexeme,search->scope );
		if(strcmp(beg->val->lexeme,search->lexeme)==0 )//&& strcmp(beg->val->scope,search->scope)==0)
			return 1;
		beg=beg->next;
	}
	printf("^^^\n");
	return -99;
}

int lookupId(Table *t,struct token* search)
{
	int sum=0;
	for(int i=0;i<strlen(search->lexeme);i++)
		sum+=search->lexeme[i];
	int hash=hashFunc(sum);
	Node* beg=t->tab[hash];
	printf("hash= %d\n",hash );
	//printf("%s\n",beg );
	// now we have found the particular LL
	//traversing the LL
	printf("in lookup id 999999999999009999999999990099999999999900999999999999009999999999990099999999999900999999999999009999999999990099999999999900999999999999009999999999990099999999999900\n");
	while(beg!=NULL)
	{
		//printf("1111111111222111111111111111111122211111111111111111112221111111111%s %s %s %s\n",beg->val->lexeme,beg->val->scope,search->lexeme,search->scope );
		// either the lexeme of the search token matches any token's or lexeme of the search token matches any corr_id
		if(strcmp(beg->val->lexeme,search->lexeme)==0 ||strcmp(beg->val->corr_id,search->lexeme)==0 )//&& strcmp(beg->val->scope,search->scope)==0)
			return 1;
		beg=beg->next;
	}
	printf("/////\n");
	return -99;
}


