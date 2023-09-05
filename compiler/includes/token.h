#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    INTEGER,
    IDENTIFIER,
    EQUALS,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    MODULO,
    PLUSEQUALS,
    MINUSEQUALS,
    TIMESEQUALS,
    DIVIDEEQUALS,
    MODULOEQUALS,
    DOUBLEEQUALS,
    LESSEQUAL,
    GREATEREQUAL,
    LESS,
    GREATER,
    DOT,
    COMMA,
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET,
    COLON,
    LPAREN,
    RPAREN,
    SEMICOLON,
    ARROW_RIGHT,
    END_OF_FILE,                            
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token *token_create(TokenType type, char *value);
char *tokenType_to_string(TokenType type);
char *token_to_string(Token *token);
void token_free(Token *token);
void token_print(Token *token);


#endif