#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stddef.h>
#include "linear_allocator.h"
#include "dynamic_array.h"

void arraylist_init(ArrayList* list, linear_allocator* al) {
    list->data = NULL;
    list->al = al;
    list->size = 0;
    list->capacity = 0;
}

void arraylist_add(ArrayList* list, void* value, size_t index) {
    if (index > list->size)return;

    if (list->size >= list->capacity) {
        if (list->capacity == 0) {
            list->capacity = 8;
        }
        else list->capacity *= 2;
        void** newdata = linear_alloc(list->al, list->capacity * sizeof(void*));
        if (newdata == NULL)return;

        memmove(newdata, list->data, list->size * sizeof(void*));

        list->data = newdata;
    }

    if (index < list->size) {
        memmove(&list->data[index + 1], &list->data[index],
            (list->size - index) * sizeof(void*));
    }

    list->data[index] = value;
    list->size++;
}

void* arraylist_get(ArrayList* list, size_t index) {
    if (index >= list->size) return NULL;
    return list->data[index];
}

void arraylist_del(ArrayList* list, size_t index) {
    if (index >= list->size) return;
    if (index < list->size - 1) {
        memmove(&list->data[index], &list->data[index + 1],
            (list->size - index - 1) * sizeof(void*));
    }
    list->size--;
}

void arraylist_free(ArrayList* list) {
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
    list->al = NULL;
}
