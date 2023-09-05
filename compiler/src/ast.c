#include <stdlib.h>

#include "../includes/ast.h"

AST *ast_init(AST_Type type) {
    AST *ast = malloc(sizeof(AST));
    ast->type = type;

    if(type == COMPOUND) {
        ast->children = list_create();
    }

    return ast;
}
