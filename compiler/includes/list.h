#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct {
    void **items;
    size_t max_list_size;
    size_t current_list_size;
} List;

List *list_create();
void list_insert(List *list, void *item);
void list_free(List *list);

#endif