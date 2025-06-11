#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void test_stack_create() {
    stack* st = stack_create(100);
    assert(st != NULL);
    assert(stack_is_empty(st));
    stack_free(st);
}

void test_stack_push() {
    stack* st = stack_create(100);
    int success = 0;
    
    assert(stack_push(st, 1) == SUCCESS);
	int value = 0;
    assert(stack_peek(st, &value) == SUCCESS);
    assert(value == 1);
    value = 0;
    assert(stack_pop(st, &value) == SUCCESS);
	assert(value == 1);
    assert(stack_is_empty(st));
    stack_free(st);
}

void test_stack_peek_empty() {
    stack* st = stack_create(10);
    int value = 0;
    
    assert(stack_peek(st, &value) == ERROR);
    assert(value == 0);
    stack_free(st);
}

void test_stack_overfilled() {
    stack* st = stack_create(10);
    int success = 0;

    for (int i = 0; i < st->size; i++) {
        assert(stack_push(st, i) == SUCCESS);
    }
    

    assert(stack_push(st, 123) == STACK_OVERFLOW);
    stack_free(st);
}

void test_stack_push_and_pop() {
    stack* st = stack_create(101);
    int value = 0;
    
    for (int i = 0; i <= 100; i++) {
        assert(stack_push(st, i) == SUCCESS);
    }

    for (int i = 100; i >= 0; i--) {
        assert(stack_pop(st, &value) == SUCCESS);
		assert(value == i);
    }

    assert(stack_is_empty(st));
    stack_free(st);
}

int main() {
    test_stack_create();
    test_stack_push();
    test_stack_peek_empty();
    test_stack_overfilled();
    test_stack_push_and_pop();
    return 0;
}
