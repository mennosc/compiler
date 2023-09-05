#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../includes/parser.h"

Parser *parser_create(Lexer *lexer) {
    Parser *parser = malloc(sizeof(*parser));
    parser->lexer = lexer;
    parser->current_token = lexer_next_token(parser->lexer);

    return parser;
}

void parser_free(Parser *parser) {
    free(parser);
}

void parser_advance(Parser *parser) {
    parser->current_token = lexer_next_token(parser->lexer);
}

Token *parser_eat(Parser *parser, TokenType type) {
    if(parser->current_token->type != type) {
        printf("[PARSER]: Unexpected token: '%s', was expecting '%s'\n", token_to_string(parser->current_token), tokenType_to_string(type));
        exit(EXIT_FAILURE);
    }
    parser_advance(parser);
    return parser->current_token;
}

// AST *parser_parse(Parser *parser) {
//     return parser_parse_compound(parser);
// }

// AST *parser_parse_id(Parser *parser) {
//     char *value = calloc(strlen(parser->current_token->value) + 1, sizeof(char));
//     strcpy(value, parser->current_token->value);
//     parser_eat(parser, IDENTIFIER);

//     if(parser->current_token->type == EQUALS) {
//         //assignment
//         parser_eat(parser, EQUALS);
//         AST *ast = ast_init(ASSIGNMENT);
//         ast->name = value;
//         ast->value = parser_parse_expr(parser);
//         return ast;
//     }

//     AST *ast = ast_init(VARIABLE);
//     ast->name = value;

//     if(parser->current_token->type == COLON) {
//         parser_eat(parser, COLON);

//         while(parser->current_token->type == IDENTIFIER) {
//             parser_eat(parser, IDENTIFIER);

//             if(parser->current_token->type == LESS) {
//                 parser_eat(parser, LESS);
//                 parser_eat(parser, IDENTIFIER);
//                 parser_eat(parser, GREATER);
//             }
//         }
//     }

//     return ast;
// }

// AST *parser_parse_compound(Parser *parser) {
//     AST *compound = ast_init(COMPOUND);
//     while(parser->current_token->type != END_OF_FILE) {
//         list_insert(compound->children, parser_parse_expr(parser));
//     }
//     return compound;
// }

// AST *parser_parse_expr(Parser *parser) {
//     switch(parser->current_token->type) {
//         case IDENTIFIER: return parser_parse_id(parser);
//         case LPAREN: return parser_parse_list(parser);
//         default: { printf("Unexpected token: '%s'\n", token_to_string(parser->current_token)); exit(EXIT_FAILURE); };
//     }
// }

// AST *parser_parse_list(Parser *parser) {
//     parser_eat(parser, LPAREN);
    
//     AST *compound = ast_init(COMPOUND);

//     list_insert(compound->children, parser_parse_expr(parser));

//     while(parser->current_token->type == COMMA) {
//         parser_eat(parser, COMMA);
//         list_insert(compound->children, parser_parse_expr(parser));
//     }

//     parser_eat(parser, RPAREN);

//     if(parser->current_token->type == COLON) {
//         parser_eat(parser, COLON);

//         while(parser->current_token->type == IDENTIFIER) {
//             parser_eat(parser, IDENTIFIER);

//             if(parser->current_token->type == LESS) {
//                 parser_eat(parser, LESS);
//                 parser_eat(parser, IDENTIFIER);
//                 parser_eat(parser, GREATER);
//             }
//         }
//     }

//     if(parser->current_token->type == ARROW_RIGHT) {
//         compound->type = FUNCTION;
//     }
//     return compound;
// }

// void parser_print_tokens(Parser *parser) {
//     do {
//         token_print(parser->current_token);
//         parser_advance(parser);
//     } while(parser->current_token->type != END_OF_FILE);
// }

AST *parser_parse_argument(Parser *parser) {
    AST *ast = ast_init(ARGUMENT);

    ast->name = calloc(strlen(parser->current_token->value) + 1, sizeof(char));
    strcpy(ast->name, parser->current_token->value);

    parser_eat(parser, IDENTIFIER);
    parser_eat(parser, COLON);

    

}

AST *parser_parse_argument_list(Parser *parser) {
    AST *ast = ast_init(ARGUMENT_LIST);
    parser_eat(parser, LPAREN);

    parser_parse_argument_list(parser);
}

AST *parser_parse_function_definition(Parser *parser) {
    AST *ast = ast_init(FUNCTION);
    if(parser->current_token->type != IDENTIFIER) {
        printf("Expected an identifier");
        exit(EXIT_FAILURE);
    }

    ast->name = calloc(strlen(parser->current_token->value) + 1, sizeof(char));
    strcpy(ast->name, parser->current_token->value);

    parser_eat(parser, IDENTIFIER);
    parser_eat(parser, EQUALS);

    list_insert(ast->children, parser_parse_argument_list(parser));

    printf("Made it to here\n");
}