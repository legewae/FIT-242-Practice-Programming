#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void test_stack_create() {
    stack* st = stack_create();
    assert(st != NULL);
    assert(stack_is_empty(st));
    stack_free(st);
}

void test_stack_push() {
    stack* st = stack_create();
    int success = 0;
    
    assert(stack_push(st, 1) == SUCCESS);
    assert(stack_peek(st, &success) == 1);
    assert(success == SUCCESS);
    
    assert(stack_pop(st, &success) == 1);
    assert(success == SUCCESS);
    assert(stack_is_empty(st));
    stack_free(st);
}

void test_stack_peek_empty() {
    stack* st = stack_create();
    int success = SUCCESS;
    
    assert(stack_peek(st, &success) == 0);
    assert(success == ERROR);
    stack_free(st);
}

void test_stack_increase() {
    stack* st = stack_create();
    assert(stack_increase(st) == SUCCESS);
    assert(st->size == DEFAULT_SIZE + PLUS_SIZE);
    stack_free(st);
}

void test_stack_overfilled() {
    stack* st = stack_create();
    int success = 0;

    for (int i = 0; i <= DEFAULT_SIZE; i++) {
        assert(stack_push(st, i) == SUCCESS);
    }

    assert(stack_pop(st, &success) == DEFAULT_SIZE);
    assert(success == SUCCESS);
    stack_free(st);
}

void test_stack_push_and_pop() {
    stack* st = stack_create();
    int success = 0;
    
    for (int i = 0; i <= 100; i++) {
        assert(stack_push(st, i) == SUCCESS);
    }

    for (int i = 100; i > 0; i--) {
        assert(stack_pop(st, &success) == i);
        assert(success == SUCCESS);
    }

    assert(stack_is_empty(st));
    stack_free(st);
}

int main() {
    test_stack_create();
    test_stack_push();
    test_stack_peek_empty();
    test_stack_increase();
    test_stack_overfilled();
    test_stack_push_and_pop();
    return 0;
}
