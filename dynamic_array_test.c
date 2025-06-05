#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dynamic_array.h"

void test_create_array() {
    linear_allocator* al = linear_allocator_init(1024);
    assert(al != NULL);

    ArrayList* list = malloc(sizeof(ArrayList));
    arraylist_init(list, al);
    assert(list->data == NULL);
    assert(list->size == 0);
    assert(list->capacity == 0);
    assert(list->al == al);

    linear_allocator_free(al);
    free(list);
}

void test_add_element() {
    linear_allocator* al = linear_allocator_init(1024);
    assert(al != NULL);

    ArrayList* list = malloc(sizeof(ArrayList));
    arraylist_init(list, al);

    int a = 42;
    arraylist_add(list, &a, 0);
    assert(list->size == 1);
    assert(list->capacity == 8);
    assert(*(int*)arraylist_get(list, 0) == 42);

    linear_allocator_free(al);
    free(list);
}

void test_add_element_at_index() {
    linear_allocator* al = linear_allocator_init(1024);
    assert(al != NULL);

    ArrayList* list = malloc(sizeof(ArrayList));
    arraylist_init(list, al);

    int a = 42;
    arraylist_add(list, &a, 0);

    int b = 84;
    arraylist_add(list, &b, 1);

    assert(list->size == 2);
    assert(list->capacity == 8);
    assert(*(int*)arraylist_get(list, 0) == 42);
    assert(*(int*)arraylist_get(list, 1) == 84);

    linear_allocator_free(al);
    free(list);
}

void test_add_element_at_invalid_index() {
    linear_allocator* al = linear_allocator_init(1024);
    assert(al != NULL);

    ArrayList* list = malloc(sizeof(ArrayList));
    arraylist_init(list, al);

    int a = 42;
    arraylist_add(list, &a, 0);

    int b = 84;
    arraylist_add(list, &b, 2);

    assert(list->size == 1);
    assert(list->capacity == 8);
    assert(*(int*)arraylist_get(list, 0) == 42);

    linear_allocator_free(al);
    free(list);
}

void test_add_element_exceeding_capacity() {
    linear_allocator* al = linear_allocator_init(1024);
    assert(al != NULL);

    ArrayList* list = malloc(sizeof(ArrayList));
    arraylist_init(list, al);

    int values[10];
    for (int i = 0; i < 10; i++) {
        values[i] = i;
        arraylist_add(list, &values[i], list->size);
    }

    assert(list->size == 10);
    assert(list->capacity == 16);

    for (int i = 0; i < 10; i++) {
        assert(*(int*)arraylist_get(list, i) == i);
    }

    linear_allocator_free(al);
    free(list);
}

void test_del_middle() {
    linear_allocator* al = linear_allocator_init(1024);
    assert(al != NULL);

    ArrayList* list = malloc(sizeof(ArrayList));
    arraylist_init(list, al);

    int a = 42, b = 84, c = 126;
    arraylist_add(list, &a, 0);
    arraylist_add(list, &b, 1);
    arraylist_add(list, &c, 2);

    arraylist_del(list, 1);

    assert(list->size == 2);
    assert(list->capacity == 8);
    assert(*(int*)arraylist_get(list, 0) == 42);
    assert(*(int*)arraylist_get(list, 1) == 126);

    linear_allocator_free(al);
    free(list);
}

void test_add_middle() {
    linear_allocator* al = linear_allocator_init(1024);
    assert(al != NULL);

    ArrayList* list = malloc(sizeof(ArrayList));
    arraylist_init(list, al);

    int a = 42, b = 84, c = 126;
    arraylist_add(list, &a, 0);
    arraylist_add(list, &b, 1);
    arraylist_add(list, &c, 1);

    assert(list->size == 3);
    assert(list->capacity == 8);
    assert(*(int*)arraylist_get(list, 0) == 42);
    assert(*(int*)arraylist_get(list, 1) == 126);
    assert(*(int*)arraylist_get(list, 2) == 84);

    linear_allocator_free(al);
    free(list);
}

int main() {
    test_create_array();
    test_add_element();
    test_add_element_at_index();
    test_add_element_at_invalid_index();
    test_add_element_exceeding_capacity();
    test_del_middle();
    test_add_middle();
    return 0;
}