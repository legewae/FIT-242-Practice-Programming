#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include "pool_allocator.h"

pool_allocator* pool_allocator_init(size_t block_amount, size_t block_size) {
	if (block_amount == 0 || block_size == 0) return NULL;
	pool_allocator* pool = malloc(sizeof(pool_allocator));
	if (!pool) return NULL;

	pool->memory = malloc(block_amount * block_size);
	if (!pool->memory) {
		free(pool);
		return NULL;
	}
	pool->block_size = block_size;
	pool->block_amount = block_amount;
	pool->free_blocks_bitmask = calloc((pool->block_amount + 7) / 8, 1);

	return pool;
}

void* pool_alloc(pool_allocator* pl) {
	if (pl == NULL)return NULL;
	for (size_t i = 0; i < pl->block_amount;i++) {
		size_t byte_id = i / 8;
		size_t bit_id = i % 8;
		if (!((pl->free_blocks_bitmask[byte_id]) & (1 << bit_id))) {
			pl->free_blocks_bitmask[byte_id] |= (1 << bit_id);
			return pl->memory + i * pl->block_size;
		}
	}
	return NULL;
}


void pool_free(pool_allocator* pl, void* pointer) {
	size_t block_id = (pointer - pl->memory) / pl->block_size;
	if (block_id >= pl->block_amount) return;

	size_t byte_id = block_id / 8;
	size_t bit_id = block_id % 8;
	pl->free_blocks_bitmask[byte_id] &= ~(1 << bit_id);
}

void pool_allocator_free(pool_allocator* pl) {
	if (pl == NULL) return;

	free(pl->memory);
	free(pl->free_blocks_bitmask);
	free(pl);
}
