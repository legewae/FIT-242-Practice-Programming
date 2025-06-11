#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack* stack_create(int capacity) {
	stack* st = malloc(sizeof(stack));
	st->size = capacity;
	st->top = 0;
	st->data = malloc(st->size * sizeof(int));
	if (st->data == NULL) {
		free(st);
		return NULL;
	}
	return st;
}


int stack_is_empty(stack* st) {
	return st->top == 0;
}

int stack_push(stack* st,int value){
	if (st->top >= st->size) {
		return STACK_OVERFLOW;
	};

	st->data[st->top] = value;
	st->top++;
	return SUCCESS;
}

int stack_pop(stack* st, int* res) {
	if (stack_is_empty(st)){ *res = 0; return ERROR;}

	st->top--;
	*res = st->data[st->top];
	return SUCCESS;
}


int stack_peek(stack* st, int* res) {
	if (stack_is_empty(st)){ *res = 0; return ERROR;}
	*res = st->data[st->top - 1];

	return SUCCESS;
}

void stack_free(stack* st) {
	free(st->data);
	free(st);
}

