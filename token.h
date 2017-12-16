#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


//Enumeration for TokenType
typedef  enum {PLUS, MINUS, DIVIDE, MULT, REMAINDER, POWER, LPAREN, RPAREN, NUMBER, ERROR, EOL} TokenType;

//Struct definition for Token
struct Token{
	TokenType type;
	int value;	
	int character;
};

struct Token token;

//Functions
void command(void);
int expr(void);
int term(void);
int power(void);
int factor(void);
int factor1(void);
void error(void);
void parse(void);
void match(TokenType tkType);
TokenType getToken(void);
void list();
