#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "token.h"

void match(TokenType tkType){

	if(token.type == tkType){
		getToken();
	}else{
		printf("match ERROR: %c\n", token.character);
		error();
	}
}

void error(void){
	printf("\nError?\n");
	exit(1);
}

//Change factor1 for (expr) | Number
int factor1(void){
	int result;
	//Replace with expr
	if(token.type == LPAREN){
		match(LPAREN);
		result=expr();
		match(RPAREN);
	}else{
		//Replace with number
		getToken();
		result=token.value;
	}	
	return result;
}

//Change factor for [-]factor1
int factor(void){
	int result;
	if(token.type == MINUS){
		match(MINUS);
		// - factor1
		result=(-1)*factor1();
		return result;
	}	
	result=factor1();
	return result;
}

//Change power for factor[^power]
int power(void){
	//Call factor function
	int result = factor();

	if (token.type == POWER){
		match(POWER);
		result = (int)pow((double)result,(double)power());
	}
	return result;
}

//Change term fpr power {* power | / power| % power}
int term(void){
	//Call fpower function
	int result = power();
	while (token.type == MULT || token.type == DIVIDE || token.type == REMAINDER){

		if(token.type == MULT){
			match(MULT);
			result=result*power();
		}else if (token.type == DIVIDE){
			match(DIVIDE);
			result=result/power();
		}else{
			match(REMAINDER);
			result=result%power();
		}
	}
	return result;
}

//Change expr for {+ term | - term}
int expr(void){
	//Call term fuction
	int result = term();
	while (token.type == PLUS || token.type == MINUS){

		if(token.type == PLUS){
			match(PLUS);
			result+=term();
		}else{
			match(MINUS);
			result=result-term();
		}
	}
	return result;
}

//Change command for expr '\n' (EOL - end of expression)
void command(void){
	//Call expr function
	int result = expr();
	if (token.type == EOL){
	printf("\n\nResult: %d\n", result);
	}else{
	printf("Command Error\n");
	error();
	}
}

TokenType getToken(void){
	//Loop to skip Blanks
	while ((token.character=getchar()) == ' ');

	//If character is a digit
	if(isdigit(token.character)){
		token.type=NUMBER;
		token.value=0;

		while(isdigit(token.character)){
			//Convert character in respective digit
			token.value=10*token.value+token.character - '0';
			token.character=getchar();
		}

		//Push the charater so it is available for next operation
		ungetc(token.character, stdin);
		printf("%d\tNUMBER \n", token.value);

		return NUMBER;

	}else{
		//character library
		switch(token.character){

		case '+':  
			token.type=PLUS;
			printf("%c\tPLUS\n",token.character);
			return PLUS; 
			break;
		case '-':  
			token.type=MINUS;
			printf("%c\tMINUS\n",token.character);
			return MINUS; 
			break;
		case '/':  
			token.type=DIVIDE;
			printf("%c\tDIVIDE\n",token.character);
			return DIVIDE; 
			break;
		case '^':  
			token.type=POWER;
			printf("%c\tPOWER\n",token.character);
			return POWER; 
			break;
		case '*':  
			token.type=MULT;
			printf("%c\tMULT\n",token.character);
			return MULT; 
			break;
		case '%':  
			token.type=REMAINDER;
			printf("%c\tREMAINDER\n",token.character);
			return REMAINDER; 
			break;
		case '(':  
			token.type=LPAREN;
			printf("%c\tLPAREN\n",token.character);
			return LPAREN; 
			break;
		case ')':  
			token.type=RPAREN;
			printf("%c\tRPAREN\n",token.character);
			return RPAREN; 
			break;
		case '\n': 
			token.type=EOL;
			return EOL; 
			break;
		default: 
			token.type=ERROR;
			printf("ERROR: %c\n", token.character);
			return ERROR; 
			break;
		}
		
		return ERROR;
	}
}

void parse(void){
	getToken();
	command();
}

int main (){
	//Ask for user input
	printf("\nInput:\n");
	//start parse process
	parse();
	return 0;
}