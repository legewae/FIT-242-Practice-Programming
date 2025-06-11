void test_stack_push() {
    stack* st = stack_create();
    int success = 0;
    
    stack_push(st, 1);

    assert(stack_peek(st, &success) == 1);
    assert(success == SUCCESS);
    
    stack_pop(st, &success);
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

void test_stack_overfilled() {
    stack* st = stack_create();
    int success = 0;

    for (int i = 0; i <= 11; i++) {
        stack_push(st, i);
    }

    assert(stack_pop(st, &success) == 11);
    assert(success == SUCCESS);
    stack_free(st);
}

void test_stack_push_and_pop() {
    stack* st = stack_create();
    int success = 0;
    
    for (int i = 0; i <= 100; i++) {
        stack_push(st, i);
    }

    for (int i = 100; i >= 0; i--) {
        assert(stack_pop(st, &success) == i);
        assert(success == SUCCESS);
    }

    assert(stack_is_empty(st));
    stack_free(st);
}
