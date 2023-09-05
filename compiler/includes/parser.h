#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#include "lexer.h"
#include "token.h"
#include "ast.h"

typedef struct {
    Lexer *lexer;
    Token *current_token;
} Parser;

// AST *parser_parse(Parser *parser);
// AST *parser_parse_expr(Parser *parser);
// AST *parser_parse_compound(Parser *parser);
// AST *parser_parse_id(Parser *parser);
// AST *parser_parse_list(Parser *parser);
AST *parser_parse_function_definition(Parser *parser);
AST *parser_parse_argument_list(Parser *parser);
Parser *parser_create(Lexer *lexer);
Token *parser_eat(Parser *parser, TokenType type);

void parser_free(Parser *parser);
void parser_print_tokens(Parser *parser);
void parser_advance(Parser *parser);

#endif