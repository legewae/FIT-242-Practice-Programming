#include <stdio.h>
#include <stdint.h>

typedef struct {
	void* memory;
	uint8_t* free_blocks_bitmask;
	size_t block_amount;
	size_t block_size;
} pool_allocator;

pool_allocator* pool_allocator_init(size_t block_amount, size_t block_size);
void* pool_alloc(pool_allocator* pl);
void pool_free(pool_allocator* pl, void* pointer);
void pool_allocator_free(pool_allocator* pl);
