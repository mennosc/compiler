 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 #include "../includes/globals.h"
 #include "../includes/token.h"

 char STRING_TYPES[30][20] = {
    "INTEGER",
    "IDENTIIER",
    "EQUALS",
    "PLUS",
    "MINUS",
    "TIMES",
    "DIVIDE",
    "MODULO",
    "PLUSEQUALS",
    "MINUSEQUALS",
    "TIMESEQUALS",
    "DIVIDEEQUALS",
    "MODULOEQUALS",
    "DOUBLEEQUALS",
    "LESSEQUAL",
    "GREATEREQUAL",
    "LESS",
    "GREATER",
    "DOT",
    "COMMA",
    "LBRACE",
    "RBRACE",
    "LBRACKET",
    "RBRACKET",
    "COLON",
    "LPAREN",
    "RPAREN",
    "SEMICOLON",
    "ARROW_RIGHT",
    "END_OF_FILE"
};

Token *token_create(TokenType type, char *value) {
    Token *token = malloc(sizeof(Token));
    if(!token) {
        printf("%s\n", "Malloc failed. Exiting the program");
        exit(EXIT_FAILURE);
    }
    token->type = type;

    if(value != NULL) {
        token->value = malloc((strlen(value) + 1) * sizeof(char));
        strcpy(token->value, value);
    } else {
        token->value = NULL;
    }

    return token;
}

void token_print(Token *token) {
    if(token->value != NULL) {
        printf("[TOKEN]: [type='%s'] | [value='%s']\n", STRING_TYPES[token->type], token->value);
    } else {
        printf("[TOKEN]: [type='%s'] | [value=NULL]\n", STRING_TYPES[token->type]);
    }
}

char *tokenType_to_string(TokenType type) {
    return STRING_TYPES[type];
}

char *token_to_string(Token *token) {
    return STRING_TYPES[token->type];
}

void token_free(Token *token) {
    free(token);
}
