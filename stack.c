#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack* stack_create() {
	stack* st = malloc(sizeof(stack));
	st->size = DEFAULT_SIZE;
	st->top = 0;
	st->data = malloc(st->size * sizeof(int));
	if (st->data == NULL) {
		free(st);
		return NULL;
	}
	return st;
}

int stack_increase(stack* st) {
	st->size += PLUS_SIZE;
	st->data = realloc(st->data, st->size * sizeof(int));
	if (st->data == NULL) return ERROR; 
	return SUCCESS;
}

int stack_is_empty(stack* st) {
	return st->top == 0;
}

int stack_push(stack* st,int value){
	if (st->top >= st->size) {
		int success = stack_increase(st);
		if (success == ERROR) return ERROR;
	};

	st->data[st->top] = value;
	st->top++;
	return SUCCESS;
}

int stack_pop(stack* st) {
	if (stack_is_empty(st)) return 0;

	st->top--;
	return st->data[st->top];
}


int stack_peek(stack* st) {
	if (stack_is_empty(st)) return 0;

	return st->data[st->top-1];
}

void stack_free(stack* st) {
	free(st->data);
	free(st);
}

