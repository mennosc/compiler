#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>

#include "token.h"     

typedef struct {
    char *source;
    size_t source_size;
    size_t current_index;
} Lexer;

Lexer *lexer_create(char *src);
Token *lexer_next_token(Lexer *lexer);
char lexer_peek(Lexer *lexer, size_t offset);
void lexer_free(Lexer *lexer);
void lexer_skip_whitespace(Lexer *lexer);
void lexer_print(Lexer *lexer);
Token *lexer_parse_operationEquals(Lexer *lexer, TokenType type);
Token *lexer_parse_symbol(Lexer *lexer, char *c);
Token *lexer_parse_identifier(Lexer *lexer);
Token *lexer_parse_integer(Lexer *lexer);

#endif