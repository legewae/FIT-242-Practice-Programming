#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linear_allocator.h"

void test_create_allocator() {
	linear_allocator* ln = linear_allocator_init(1024);
	assert(!(ln == NULL));
	linear_allocator_free(ln);
}
void test_alloc() {
	linear_allocator* ln = linear_allocator_init(sizeof(int)*2);

	int* a = (int*)linear_alloc(ln,sizeof(int));
	int* b = (int*)linear_alloc(ln,sizeof(int));
	int* c = (int*)linear_alloc(ln,sizeof(int));

	*a = 2;
	*b = 3;
	assert(c == NULL);
	assert(*a == 2);
	assert(*b == 3);
	linear_allocator_free(ln);
}
void test_alloc_reset() {
	linear_allocator* ln = linear_allocator_init(sizeof(int)*2);

	int* a = (int*)linear_alloc(ln,sizeof(int));
	linear_allocator_reset(ln);
	int* b = (int*)linear_alloc(ln,sizeof(int));

	*a = 3;
	*b = 5;

	assert(*a == *b);
	linear_allocator_free(ln);
}

void test_diff_types() {
	linear_allocator* ln = linear_allocator_init(sizeof(int) * 2);

	int* a = (int*)linear_alloc(ln, sizeof(int));
	char* b = (char*)linear_alloc(ln, sizeof(char));

	*a = 3;
	*b = 'c';

	assert(*a == 3 && *b == 'c');
	linear_allocator_free(ln);
}

int main() {
	test_create_allocator();
	test_alloc();
	test_alloc_reset();
	test_diff_types();
	return 0;
}