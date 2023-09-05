#include <stdio.h>
#include <stdlib.h>

#include "../includes/list.h"
#include "../includes/globals.h"

List *list_create() {
    List *list = malloc(sizeof(List));
    list->max_list_size = INITIAL_LIST_SIZE;
    list->current_list_size = 0;
    list->items = malloc(INITIAL_LIST_SIZE * sizeof(void *));

    return list;
}

void list_insert(List *list, void *item) {
    if(list->current_list_size == list->max_list_size) {
        list->items[list->current_list_size] = item;
        list->current_list_size++;
    }

    list->max_list_size *= 2;
    list->items = realloc(list->items, (list->max_list_size + 1) * sizeof(void *));
}

void list_free(List *list) {
    free(list->items);
}