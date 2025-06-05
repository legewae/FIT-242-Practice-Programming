#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pool_allocator.h"
#include "hashtable.h"

int hashfunction(const char* key, size_t size) {
	int hash = 0;
	while (*key) {
		hash = (hash * 31 + *key++) % size;
	}
	return hash;
}

void hashtable_init(HashTable* ht, size_t capacity, pool_allocator* pl) {
	ht->capacity = capacity;
	ht->pl = pl;
	ht->buckets = calloc(capacity, sizeof(bucket*));
	if (!ht->buckets) return;
}

void hashtable_insert(HashTable* ht, const char* key, void* value) {
	if (!ht)return;
	if (!key)return;

	size_t index = hashfunction(key, ht->capacity);	
	bucket* bucket_entry = pool_alloc(ht->pl);

	if (!bucket_entry) return;
	bucket_entry->data = value;
	bucket_entry->key = strdup(key);

	bucket_entry->next = ht->buckets[index];
	ht->buckets[index] = bucket_entry;
}

void* hashtable_get(HashTable* ht, const char* key) {
	if (!ht)return NULL;
	if (!key)return NULL;

	long index = hashfunction(key, ht->capacity);

	bucket* current = ht->buckets[index];

	while (current) {
		if (strcmp(current->key, key) == 0) {
			return current->data;
		}
		current = current->next;
	}

	return NULL;
}

void hashtable_del(HashTable* ht, const char* key) {
	if (!ht)return;
	if (!key)return;

	size_t index = hashfunction(key, ht->capacity);

	bucket* current = ht->buckets[index];
	bucket* prev = NULL;

	while (current) {
		if (strcmp(current->key, key) == 0) {
			if (prev) {
				prev->next = current->next;
			}
			else {
				ht->buckets[index] = current->next;
			}
			free(current->key);
			pool_free(ht->pl, current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

void hashtable_free(HashTable* ht) {
	if (!ht) return;
	for (size_t i = 0; i < ht->capacity; i++) {
		bucket* current = ht->buckets[i];
		while (current) {
			bucket* to_free = current;
			current = current->next;
			free(to_free->key);
			pool_free(ht->pl, to_free);
		}
	}
	free(ht->buckets);
}

