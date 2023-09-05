#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../includes/lexer.h"
#include "../includes/globals.h"

Lexer *lexer_create(char *src) {
    Lexer *lexer = malloc(sizeof(Lexer));
    if(!lexer) {
        printf("%s\n", "Malloc failed. exiting the program");
        exit(EXIT_FAILURE);
    }

    lexer->source = malloc((strlen(src) + 1) * sizeof(char));
    if(!lexer->source) {
        printf("%s\n", "Malloc failed. Exiting the program");
        exit(EXIT_FAILURE);
    }

    strcpy(lexer->source, src);
    lexer->current_index = 0;
    lexer->source_size = strlen(src);

    return lexer;
}

Token *lexer_parse_identifier(Lexer *lexer) {
    char identifier[MAX_IDENTIFIER_LENGTH];
    size_t identifier_index = 0;
    char current_character = lexer->source[lexer->current_index];
    while(isalpha(current_character) || isdigit(current_character) || current_character == '_') {
        identifier[identifier_index++] = current_character;
        lexer->current_index++;
        current_character = lexer->source[lexer->current_index];
    }
    identifier[identifier_index] = '\0';
    return token_create(IDENTIFIER, identifier);
}

Token *lexer_parse_integer(Lexer *lexer) {
    char integer[MAX_INTEGER_LENGTH];
    size_t integer_index = 0;
    char current_character = lexer->source[lexer->current_index];
    while(isdigit(current_character)) {
        integer[integer_index++] = current_character;
        lexer->current_index++;
        current_character = lexer->source[lexer->current_index];
    }

    if(integer_index > (MAX_INTEGER_LENGTH - 1)) {
        printf("%s\n", "The maximum integer size has been exceeded. Try a smaller number");
        exit(EXIT_SUCCESS);
    }

    integer[integer_index] = '\0';
    return token_create(INTEGER, integer);
}   

Token *lexer_parse_operationEquals(Lexer *lexer, TokenType type) {
    if(type == EQUALS && lexer_peek(lexer, 1) == '>') {
        lexer->current_index += 2;
        return token_create(ARROW_RIGHT, NULL);
    }

    if(lexer_peek(lexer, 1) == '=') {
        lexer->current_index += 2;
        if(type == PLUS) return token_create(PLUSEQUALS, NULL);
        if(type == MINUS) return token_create(MINUSEQUALS, NULL);
        if(type == TIMES) return token_create(TIMESEQUALS, NULL);
        if(type == DIVIDE) return token_create(DIVIDEEQUALS, NULL);
        if(type == MODULO) return token_create(MODULOEQUALS, NULL);
        if(LESS) return token_create(LESSEQUAL, NULL);
        if(GREATER) return token_create(GREATEREQUAL, NULL);
        if(EQUALS) return token_create(DOUBLEEQUALS, NULL);
    }

    lexer->current_index++;
    return token_create(type, NULL);
}

Token *lexer_next_token(Lexer *lexer) {
    lexer_skip_whitespace(lexer);

    char current_character = lexer->source[lexer->current_index];
    switch(current_character) {
        //Operations
        case '+': return lexer_parse_operationEquals(lexer, PLUS);
        case '-': return lexer_parse_operationEquals(lexer, MINUS);
        case '*': return lexer_parse_operationEquals(lexer, TIMES);
        case '/': return lexer_parse_operationEquals(lexer, DIVIDE);
        case '%': return lexer_parse_operationEquals(lexer, MODULO);

        //Relational operators
        case '=': return lexer_parse_operationEquals(lexer, EQUALS);
        case '<': return lexer_parse_operationEquals(lexer, LESS);
        case '>': return lexer_parse_operationEquals(lexer, GREATER);

        //symbols
        case '.': return lexer_parse_operationEquals(lexer, DOT);
        case ',': return lexer_parse_operationEquals(lexer, COMMA);
        case '{': return lexer_parse_operationEquals(lexer, LBRACE);
        case '}': return lexer_parse_operationEquals(lexer, RBRACE);
        case '[': return lexer_parse_operationEquals(lexer, LBRACKET);
        case ']': return lexer_parse_operationEquals(lexer, RBRACKET);
        case ':': return lexer_parse_operationEquals(lexer, COLON);
        case '(': return lexer_parse_operationEquals(lexer, LPAREN);
        case ')': return lexer_parse_operationEquals(lexer, RPAREN);
        case ';': return lexer_parse_operationEquals(lexer, SEMICOLON);
    }

    if(isalpha(current_character)) {
        return lexer_parse_identifier(lexer);
    } else if(isdigit(current_character)) {
        return lexer_parse_integer(lexer);
    }

    return token_create(END_OF_FILE, NULL);
}

char lexer_peek(Lexer *lexer, size_t offset) {
    return lexer->source[lexer->current_index + offset];
}

void lexer_skip_whitespace(Lexer *lexer) {
    char current_character = lexer->source[lexer->current_index];
    while(current_character == ' ' || current_character == '\n' || current_character == '\t') {
        lexer->current_index++;
        current_character = lexer->source[lexer->current_index];
    }
}

void lexer_print(Lexer *lexer) {
    Token *tok;
    while((tok = lexer_next_token(lexer))->type != END_OF_FILE) {
        token_print(tok);
    }
}

void lexer_free(Lexer *lexer) {
    free(lexer->source);
    free(lexer);
}
