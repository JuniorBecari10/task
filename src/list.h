#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct {
    void *list;

    size_t element_size;
    size_t cap;
    size_t len;
} List;

List new_list(size_t element_size);

void list_append(List *list, void *element);
void list_remove(List *list, size_t index);

void *list_get(List *list, size_t index);
void *list_get_unchecked(List *list, size_t index);

void free_list(List *list);

#endif
