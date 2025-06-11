#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include "pool_allocator.h"

void test_allocator_init(){
	pool_allocator* pl = pool_allocator_init(100,4);
	assert(!(pl==NULL));
	pool_allocator_free(pl);
}

void test_allocator_alloc() {
	pool_allocator* pl = pool_allocator_init(100, 4);
	int32_t* number = pool_alloc(pl);
	*number = 123;
	assert(*number == 123);
	pool_allocator_free(pl);
}

void test_free() {
	pool_allocator* pl = pool_allocator_init(100, 4);
	int32_t* number = pool_alloc(pl);
	*number = 123;
	assert(*number == 123);
	pool_free(pl,number);
	number = pool_alloc(pl);
	assert(*number == 123);
	pool_allocator_free(pl);
}

void test_multiple_alloc() {
	pool_allocator* pl = pool_allocator_init(100, 4);
	int32_t* number1 = pool_alloc(pl);
	int32_t* number2 = pool_alloc(pl);
	int32_t* number3 = pool_alloc(pl);
	*number1 = 1;
	*number2 = 2;
	*number3 = 3;
	assert(*number1 == 1);
	assert(*number2 == 2);
	assert(*number3 == 3);
	pool_allocator_free(pl);
}

void test_alloc_overflow() {
	pool_allocator* pl = pool_allocator_init(3, 4);
	int32_t* number1 = pool_alloc(pl);
	int32_t* number2 = pool_alloc(pl);
	int32_t* number3 = pool_alloc(pl);
	*number1 = 1;
	*number2 = 2;
	*number3 = 3;
	assert(*number1 == 1);
	assert(*number2 == 2);
	assert(*number3 == 3);
	int32_t* number4 = pool_alloc(pl);
	assert(!number4);
	pool_allocator_free(pl);
}

void test_bitmask() {
	pool_allocator* pl = pool_allocator_init(8, 4);
	assert(pl != NULL);

	void* blocks[8];
	for (int i = 0; i < 8; i++) {
		blocks[i] = pool_alloc(pl);
		assert(blocks[i] != NULL);
	}

	assert(pool_alloc(pl) == NULL);

	for (int i = 1; i < 8; i += 2) {
		pool_free(pl, blocks[i]);
	}

	for (int i = 1; i < 8; i += 2) {
		assert(pool_alloc(pl) != NULL);
	}

	pool_allocator_free(pl);
}

int main() {
	test_allocator_init();
	test_allocator_alloc();
	test_free();
	test_multiple_alloc();
	test_alloc_overflow();
	test_bitmask();
	return 0;
}
