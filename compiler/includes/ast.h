#ifndef AST_H
#define AST_H

#include "../includes/list.h"

typedef enum {
    COMPOUND,
    ASSIGNMENT,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    VARIABLE,
    FUNCTION,
    ARGUMENT_LIST,
    ARGUMENT,
} AST_Type;

typedef struct {
    AST_Type type;
    char *name;
    struct AST *value;
    List *children;
} AST;

AST *ast_init(AST_Type type);
#endif