#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>
#include "linear_allocator.h"

typedef struct {
    void** data;
    size_t size;
    size_t capacity;
    linear_allocator* al;
} ArrayList;

void arraylist_init(ArrayList* list, linear_allocator* al);
void arraylist_add(ArrayList* list, void* value, size_t index);
void* arraylist_get(ArrayList* list, size_t index);
void arraylist_del(ArrayList* list, size_t index);
void arraylist_free(ArrayList* list);
#endif 