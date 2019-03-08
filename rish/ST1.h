#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tab.h"


int f=0;
char *fun_scope;
int isfunc(int i,struct token* arr[100])
{
		struct token* t=arr[i];
		struct token* t1=arr[i+1];
		if(strcmp(t1->lexeme,"(")==0)
			return 1;
		return -1;
}
int retSize(char *word)
{
		//printf("cal size of %s\n",t1->lexeme );
		if(strcmp("int",word)==0)return 4;
		if(strcmp("float",word)==0)return 4;
		if(strcmp("double",word)==0)return 8;
		return -1;// for func
}
int isVar(int i,struct token* arr[100])
{

		struct token* t=arr[i];
		printf("hi %s\n",t->lexeme);
		struct token* t1=arr[i+1];
		printf("in isVar %s %s\n",t->lexeme, t1->lexeme );
		if((strcmp(t1->lexeme,";")==0	||	strcmp(t1->lexeme,"=")==0 ||	strcmp(t1->lexeme,",")==0  ||strcmp(t1->lexeme,")")==0 ||strcmp(t1->lexeme,"[")==0) && strcmp(t->type,"Identifier")==0)
		{	
			//printf("var as next is %s\n",t1->lexeme );
			return 1;
		}
		else
			return -1;
}
int is_Extended_var(int i, struct token* arr[100])
{
		struct token* t=arr[i];
		struct token* t1=arr[i-1];
		printf("in isExtendedVar %s %s\n",t->lexeme, t1->lexeme );
		if(strcmp(t1->lexeme,",")==0   && strcmp(t->type,"Identifier")==0)
		{	
			//printf("var as next is %s\n",t1->lexeme );
			return 1;
		}
		else
			return -1;
}

char* type_of_extended(int i, struct token* arr[100])
{
		//reaches here only when token at i is an extended var.
	printf("finding type of %s\n",arr[i]->lexeme );
		i--;
		while(i>=0)
		{
			if(strcmp(arr[i]->type,"KEYW")==0)
			{	
					printf("Returning to%s\n\n",arr[i]->lexeme);
					return arr[i]->lexeme;

			}
			i--;
		}
		return NULL;
}
int ret_arr_size(int i,struct token* arr[100])
{
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ %s\n",arr[i]->lexeme);
		struct token* t=arr[i];
		struct token* t1=arr[i+1];
	//	printf("lexemes are : %s, %s \n",t->lexeme,t1->lexeme );
		if(strcmp(t1->lexeme,"[")==0)
		{

				t1=arr[i+2];// the numreic value
				// printf("in\n");
				// printf("in %s \n",t1->lexeme);
				printf("1234567890$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$44returning %s\n",t1->lexeme);
				return atoi(t1->lexeme);
		}
		printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$returning 1\n");
		return 1;
}
int isScopeBegin(struct token* t1)
{
		if((strcmp(t1->lexeme,"for")==0	||	strcmp(t1->lexeme,"do")==0	||	strcmp(t1->lexeme,"while")==0  ||strcmp(t1->lexeme,"switch")==0||strcmp(t1->lexeme,"if")==0||strcmp(t1->lexeme,"else")==0))
			return 1;
		else
			return -1;
}
void add(struct token* t1,Table *table)
{
		//printf("adding %s\n",t1->lexeme);
		int sum=0;
		for(int i=0;i<strlen(t1->lexeme);i++)
			sum+=t1->lexeme[i];
		insert(table,sum,t1);
}

int lookFor(struct token* t1,Table *table)
{
		//printf("loof for %s\n",t1->lexeme );
		int v=lookup(table,t1);
		// if(v==1)
		// 	printf("got!\n");

		return v;
}
void func(struct token* arr[100],int p,Table *table,char** t_scope, int* s_no)
{

	
		//char* t_scope=malloc(sizeof(char)*50);

		int i=0;//int cnt=0;
		while(i!=p)
		{	


				 arr[i]->args=(char**)malloc(sizeof(char*)*50);//50 args max for a func.
				// 	for(int m=0;m<50;m++)
				// 		arr[i]->args[m]=(char*)malloc(sizeof(char)*50);
				
				struct token* t=arr[i];
				//printf("lex is:%d %s %s\n",cnt,t->lexeme,t->type);

				if(strcmp(t->type,"Identifier")==0)
				{
					//arr[i]->args=NULL;
					// (char**)malloc(sizeof(char*)*50);//50 args max for a func.
					// for(int m=0;m<50;m++)
					// 	arr[i]->args[m]=NULL;
				//identifying ids
						if(isfunc(i,arr)==1)
						{	
								*t_scope="local\0" ;//arr[i]->lexeme;
								printf("is Func : %s\n",arr[i]->lexeme );

								//arr[i]->scope=*t_scope;	
								int v=lookFor(arr[i],table);
								int n_args=0;
								if(v!=1)
								{	

									printf("HEYYYA1 %s\n",arr[i]->lexeme);
									int k=i;
									printf("in\n");
									k++;// at'(''
									k++;
									int fill=0;
									arr[i]->scope=(char*)malloc(sizeof(char)*20);
									arr[i]->scope="global\0" ;
									printf("in %s\n",arr[i]->scope);
									arr[i]->ret_type=(char*)malloc(sizeof(char)*50);
									arr[i]->ret_type=arr[i-1]->lexeme;
									printf("in\n");
									arr[i]->size=retSize(arr[i]->type);
									arr[i]->type="null";

									printf("adding Func : %s\n",arr[i]->lexeme );

									arr[i]->sr_no=*s_no;
									*s_no=*s_no+1;
									arr[i]->corr_id=(char*)malloc(sizeof(char)*20);
									sprintf(arr[i]->corr_id,"%s%d","id",arr[i]->sr_no);
									add(arr[i],table);
									printf("added\n");
									while(1)
									{
										printf("**HEYYYA %s\n",arr[k]->lexeme);
										
										if(strcmp(arr[k]->lexeme,")")==0)
											break;
										if(isVar(k,arr)==1)// ||strcmp(t1->lexeme,")")==0)
										{	
											printf("in if\n");
											arr[k]->scope=*t_scope;	
											int v1=lookFor(arr[k],table);
											printf("is VAR\n");
											if(v1!=1)
											{

													printf("checking ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ %s\n",arr[k]->lexeme );
													int ans=ret_arr_size(k,arr);

													arr[k]->type=arr[k-1]->lexeme;
													arr[k]->scope=*t_scope;
													arr[k]->ret_type="null";
													arr[k]->no_of_args=-1;	

													arr[k]->size=retSize(arr[i]->type)*ans;
													arr[k]->sr_no=*s_no;
													*s_no=*s_no+1;
													arr[i]->corr_id=(char*)malloc(sizeof(char)*20);
									sprintf(arr[i]->corr_id,"%s%d","id",arr[i]->sr_no);
													add(arr[k],table);
													n_args++;
														//printf("******* %s\n",arr[i]->lexeme);
													
													char conv[50];
													sprintf(conv,"%d",arr[k]->sr_no);//int to string
													printf("\njust befoe\n");
													//arr[i]->args[fill++]=conv;//arr[k]->lexeme;
													arr[i]->args[fill]=(char*)malloc(sizeof(char)*50);
													strcpy(arr[i]->args[fill++],conv);
													printf("############################################# %s",arr[i]->args[fill-1]);
													// printf("*******\n");
													printf("added %s %s INC no. tp %d min %s %d\n",arr[i]->args[fill-1],arr[k]->scope,n_args,arr[i]->args[fill-1],fill-1 );
													// if(arr[i]->args!=NULL)
													// {	
													// 	for(int m=0;m<50;m++)
													// 	{
															
													// 			if(arr[i]->args[m]!=NULL)
													// 			//printf(" m = %d, %s\t",m,arr[i]->args[m] );
													// 	}
													// }

												}
												 else
												 	printf("FOUND! %s \n",arr[k]->lexeme );	

												//	printf("var name : %s\n",t->lexeme );
											}
											else
												printf("noy a var\n");
											
											k++;// to skip the ending ) of the function
									}// inner while
									//	printf("out\n");
									
									arr[i]->no_of_args=n_args;
									i=k;
									
								}
								//else
									//printf("FOUND! %s \n",arr[i]->lexeme );
								//printf("func is %s\n",t->lexeme );
								

								//since it is a finction defntn means we have to now deal with args
								// and each of these have to be added to the ST with scope = the fucn Name
								//scope=t->lexeme;//set the scope
							
						
						}
						else if(isVar(i,arr)==1)// ||strcmp(t1->lexeme,")")==0)
						{	
							//if(not present):
								printf("isVAR yes\n");
								arr[i]->scope=*t_scope;	
								int v=lookFor(arr[i],table);
								if(v!=1)
								{
										int d=is_Extended_var(i,arr);
										if(d==1)
										{	arr[i]->type=type_of_extended(i,arr);
											printf("setting type to %s\n",arr[i]->type );
										}
										else
											arr[i]->type=arr[i-1]->lexeme;	
										printf("not found\n");
										int ans=ret_arr_size(i,arr);

										printf("done check for ans %d\n",ans);
										
										printf("&&\n");
										arr[i]->scope=*t_scope;//repeat
										arr[i]->ret_type="null";
										arr[i]->no_of_args=-1;	
										printf("&&\n");
										arr[i]->size=retSize(arr[i]->type)*ans;
										printf("setting size of %s to %d**\n",arr[i]->lexeme,arr[i]->size);

										arr[i]->sr_no=*s_no;
													*s_no=*s_no+1;
										arr[i]->corr_id=(char*)malloc(sizeof(char)*20);
									sprintf(arr[i]->corr_id,"%s%d","id",arr[i]->sr_no);
										add(arr[i],table);printf("added var %s\n",arr[i]->lexeme);
								}
							else
								printf("FOUND! %s \n",arr[i]->lexeme );
							//	printf("var name : %s\n",t->lexeme );
						}
						// else
						// 	printf("noting\n");
				}
				else if(strcmp(t->type,"KEYW")==0 && i==0)
				{
						if(isScopeBegin(t)==1)
						{
								//beg of a new scope
								fun_scope=malloc(sizeof(char)*50);
								f=1;
								//printf("changed to %s\n", );
								fun_scope=*t_scope;
								*t_scope="local\0" ;//t->lexeme;// new short scope

						}
				}
				else if(strcmp(t->lexeme,"}")==0 && f==1)
				{
						//end of temporary scope
						f=0;
						*t_scope="local\0" ;//fun_scope;
				}
				//cnt++; 
				i++;
		
		}//outer while

		//for(int k=3,j=4;j<k;k++);
		
}