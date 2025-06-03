#include <stdlib.h>

typedef struct {
	void* memory;
	size_t offset;
	size_t size;
} linear_allocator;

linear_allocator* linear_allocator_init(size_t size);

void linear_allocator_free(linear_allocator* allocator);
void linear_allocator_reset(linear_allocator* allocator);
void* linear_alloc(linear_allocator* allocator, size_t size);