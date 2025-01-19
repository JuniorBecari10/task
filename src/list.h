#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

// the function used to drop the list elements
typedef void (*DropFn)(void *);

typedef struct {
    void *list;
    DropFn drop_fn;

    size_t element_size;
    size_t cap;
    size_t len;
} List;

List new_list(size_t element_size, DropFn drop_fn);

void list_append(List *list, void *element);
void list_remove(List *list, size_t index);

void free_list(List *list);

#endif
