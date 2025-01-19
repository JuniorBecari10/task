#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List new_list(size_t element_size) {
    return (List) {
        .list = malloc(element_size * 10),
        .element_size = element_size,
        .cap = 10,
        .len = 0,
    };
}

// Function to append an element to the list
void list_append(List *list, void *element) {
    // Resize the list if needed
    if (list->len >= list->cap) {
        list->cap *= 2;
        list->list = realloc(list->list, list->element_size * list->cap);
    }

    // Copy the element into the list
    void *target = (char *)list->list + list->len * list->element_size;
    memcpy(target, element, list->element_size);
    list->len++;
}

// Function to remove an element from the list by index
void list_remove(List *list, size_t index) {
    if (index >= list->len) {
        fprintf(stderr, "Index out of bounds: %ld, len: %ld\n", index, list->len);
        return;
    }

    // Shift elements after the index to the left
    void *target = (char *)list->list + index * list->element_size;
    size_t num_bytes_to_shift = (list->len - index - 1) * list->element_size;
    if (num_bytes_to_shift > 0) {
        memmove(target, (char *)list->list + (index + 1) * list->element_size, num_bytes_to_shift);
    }

    // Update length
    list->len--;
}

// Function to free the list
void free_list(List *list) {
    free(list->list);
    
    list->list = NULL;
    list->cap = 0;
    list->len = 0;
}
