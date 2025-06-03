#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void test0() {
    stack* st = stack_create();
    assert(stack_is_empty(st));
    stack_free(st);
}

void test1() {
    stack* st = stack_create();
    stack_push(st, 1);

    assert(stack_peek(st) == 1);
    stack_pop(st);
    assert(stack_is_empty(st));
    stack_free(st);
}

void test2() {
    stack* st = stack_create();
    assert(stack_peek(st) == 0);
    stack_free(st);
}

void test3() {
    stack* st = stack_create();
    stack_increase(st);

    assert(st->size == DEFAULT_SIZE + PLUS_SIZE);
    stack_free(st);
}

void test4() {
    stack* st = stack_create();

    for (int i = 0; i <= 11; i++) {
        stack_push(st, i);
    }

    assert(stack_pop(st) == 11);
    stack_free(st);
}

void test5() {
    stack* st = stack_create();

    for (int i = 0; i <= 100; i++) {
        stack_push(st, i);
    }

    for (int i = 100; i >= 0; i--) {
        assert(stack_pop(st) == i);
    }

    assert(stack_is_empty(st));
    stack_free(st);
}

int main() {
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}