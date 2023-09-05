#include <stdio.h>

#include "../includes/lexer.h"
#include "../includes/token.h"
#include "../includes/io.h"
#include "../includes/globals.h"
#include "../includes/parser.h"
#include "../includes/ast.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("%s\n", "The file could not be found. Please specify the correct file path");
        exit(EXIT_SUCCESS);
    }

    char *src = read_file(argv[1]);
    Lexer *lexer = lexer_create(src);
    Parser *parser = parser_create(lexer);
    
    AST *root = parser_parse_function_definition(parser);
    lexer_print(lexer);
}                                                                                                           