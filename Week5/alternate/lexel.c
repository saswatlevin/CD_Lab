#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* const token_types[] = {
	"ARITHMETIC OPERATOR",
	"RELATIONAL OPERATOR",
	"LOGICAL OPERATOR",
	"SPECIAL SYMBOL",
	"KEYWORD",
	"NUMERICAL CONSTANT",
	"STRING LITERAL",
	"IDENTIFIER"
	};

int row,column,nl;

void preprocess(FILE *in,FILE *out) {
	int ch = fgetc(in);
	while(ch != EOF) {
		int presp = 1;
		int p = 1;
		while(ch!='\n' && ch!=EOF){
			while(ch == ' ' || ch == '\t'){
				fputc(ch,out);
				ch = fgetc(in);
			}
			if(ch == '#' && presp) p = 0;
			presp = 0;
			if(p) fputc(ch,out);
			ch = fgetc(in);
		}
		if(ch != EOF) {
			fputc(ch,out);
			ch = fgetc(in);	
		}
	}
	fclose(in);
	fclose(out);
}

int isKeyword(char word[256], int len) {
	char keywords[32][32] = {
		"auto",
		"break",
		"case",
		"char",
		"const",
		"continue",
		"default",
		"do",
		"double",
		"else",
		"enum",
		"extern",
		"float",
		"for",
		"goto",
		"if",
		"int",
		"long",
		"register",
		"return",
		"short",
		"signed",
		"sizeof",
		"static",
		"struct",
		"switch",
		"typedef",
		"union",
		"unsigned",
		"void",
		"volatile",
		"while"
	};
	for(int i=0;i<32;i++) {
		if(strcmp(word,keywords[i]) == 0)
			return 1;
	}
	return 0;
}

int isArithmeticOperator(char word[256], int len) {
	if(len > 2)
		return 0;
	if(word[0] == '=' && len == 1)
		return 1;
	if(word[0] != '+' && word[0] != '-' && word[0] != '*' && word[0] !='/' && word[0] != '%')
		return 0;
	return 1;
}

int isRelOp(char word[256],int len) {
	if(len > 2)
		return 0;
	if(word[0] == '>' || word[0] == '<' || word[0] == '=')
		return 1;
	if((word[0] == '&' || word[0] == '|') && word[0] == word[1])
		return 1;
	if(word[0] == '!' && word[1] == '=')
		return 1;
	return 0;
}

int isLogicalOp(char word[256],int len) {
	if(len != 1)
		return 0;
	return word[0] == '!' || word[0] == '&' || word[0] == '|' || word[0] == '^';
}

int isNumericConstant(char word[256],int len) {
	int i;
	for(i=0;i<len;i++) {
		if((word[i]!='.') && (word[i]<'0' || word[i]>='9'))
			return 0;
	}
	return 1;
}

int isStringLiteral(char word[256],int len) {
	return (word[0]=='\'' || word[0] == '"') && word[len-1] == word[0];
}

int isSpecialSymbol(char word[256],int len) {
	if(len!=1)
		return 0;
	char ch = word[0];
	return ch == ';' || ch == '(' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == ',';
}
int isWhiteSpace(char ch) {
	return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0';
}

int isAlphaNumUnder(char ch) {
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '_';
}

int isIdentifier(char word[256], int len) {
	if(!isAlphaNumUnder(word[0]) || (word[0]>='0' && word[0] <= '9'))
		return 0;
	for(int i=1;i<len;i++)
		if(!isAlphaNumUnder(word[i]))
			return 0;
	return 1;
}

int isOperator(char ch) {
	return ch == '=' || ch == '>' || ch == '<' || ch == '!' || ch == '*' || ch == '+' || ch == '-' || ch == '/' || ch =='&' || ch == '|' || ch=='%' || ch=='^';
}

char* getNextToken(FILE *in) {
	int prechar = '\0';
	int curr = '\0';
	char* buf = malloc(sizeof(char) * 256);
	int h = 0;
	int literal = 0;
	int escaped = 0;
	int starting = 0;
	while(1 && prechar != EOF) {
		curr = fgetc(in);
		column++;
		if(nl) {
			row++;
			column=1;
		}
		if(curr == '\n')
			nl = 1;
		else
			nl = 0;
		if(curr == EOF)
			break;
		if(literal && curr==starting && !escaped) {
			buf[h++] = curr;
			literal = 0;
			break;
		}
		else if(literal == 0 && escaped == 0 && (curr=='"' || curr =='\'')) {
			if(h!=0) {
				ungetc(curr,in);
				column--;
				break;
			}
			literal = 1;
			starting = curr;
		}
		if(curr == '\\' && escaped == 0)
			escaped = 1;
		else
			escaped = 0;
		if(literal) {
			buf[h++] = curr;
			prechar = curr;
			continue;
		}
		if(isWhiteSpace(curr) && h==0)
			continue;
		else if(isWhiteSpace(curr))
			break;
		if(h==0){
			buf[h++] = (char)curr;
			prechar = curr;
			continue;
		}
		if(curr>='0' && curr<='9') {
			if(isAlphaNumUnder(prechar))
				buf[h++] = curr;
			else {
				ungetc(curr,in);
				column--;
				break;
			}
		} else if(isOperator(curr)) {
			if(isOperator(prechar))
				buf[h++] = curr;
			else {
				ungetc(curr,in);
				column--;
				break;
			}
		} else if(isAlphaNumUnder(curr) && isAlphaNumUnder(prechar)) {
			buf[h++] = curr;
		} else {
			ungetc(curr,in);
			column--;
			break;
		}
		prechar = curr;
	}
	buf[h++] = '\0';
	return buf;
}

void displayLexeme(char* name, int len,int type) {
	printf("< %s , %d , %d , %s >\n",name,row,column-len+1,token_types[type]);
}

/*int main(int argc, char const *argv[])
{
	FILE *in,*temp;
	if(argc != 2) {
		printf("USAGE: ./lexer infile.c\n");
		exit(1);
	}
	in = fopen(argv[1],"r");
	if(in == NULL) {
		printf("Cannot open file\n");
		exit(0);
	}
	row = 1;
	column = 0;
	nl=0;
	temp = fopen("temp.c","w");
	preprocess(in,temp);
	temp = fopen("temp.c","r");
	char *token = NULL;
	while(1) {
		token = getNextToken(temp);
		int len = strlen(token);
		if(len == 0) break;
		if(isArithmeticOperator(token,len)) displayLexeme(token,len,0);
		else if(isRelOp(token,len)) displayLexeme(token,len,1);
		else if(isLogicalOp(token,len)) displayLexeme(token,len,2);
		else if(isSpecialSymbol(token,len)) displayLexeme(token,len,3);
		else if(isKeyword(token,len)) displayLexeme(token,len,4);
		else if(isNumericConstant(token,len)) displayLexeme(token,len,5);
		else if(isStringLiteral(token,len)) displayLexeme(token,len,6);
		else if(isIdentifier(token,len)) displayLexeme(token,len,7);
		else {
			printf("Invalid token %s at line %d column %d\n", token, row,column);
			exit(0);
		}
	}
	fclose(temp);
	remove("temp.c");
	return 0;
}*/
