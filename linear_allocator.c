#include <stdio.h>
#include <stdlib.h>
#include "linear_allocator.h"

linear_allocator* linear_allocator_init(size_t size) {
	linear_allocator* ln = (linear_allocator*)malloc(sizeof(linear_allocator));
	if (ln == NULL)return NULL;

	ln->memory = malloc(size);
	if (ln->memory == NULL) {
		free(ln);
		return NULL;
	}
	ln->offset = 0;
	ln->size = size;
	return ln;
}

void* linear_alloc(linear_allocator* allocator, size_t size) {
	if (allocator == NULL) return NULL;
	if (allocator->size < allocator->offset + size) return NULL;

	void* pointer = allocator->memory + allocator->offset;
	allocator->offset += size;
	return pointer;
}

void linear_allocator_reset(linear_allocator* allocator) {
	if (allocator == NULL) return;
	allocator->offset = 0;
}

void linear_allocator_free(linear_allocator* allocator) {
	if (allocator == NULL)return;
	free(allocator->memory);
	free(allocator);
}