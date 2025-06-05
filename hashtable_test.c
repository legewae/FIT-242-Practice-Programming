#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hashtable.h"
#include "pool_allocator.h"

void test_hashtable_init() {
    pool_allocator* pl = pool_allocator_init(100, sizeof(bucket));
    HashTable* ht = malloc(sizeof(HashTable));
    hashtable_init(ht, 10, pl);

    assert(ht->capacity == 10);
    assert(ht->pl == pl);
    assert(ht->buckets != NULL);

    hashtable_free(ht);
    free(ht);
    pool_allocator_free(pl);
}

void test_hashtable_insert_get() {
    pool_allocator* pl = pool_allocator_init(100, sizeof(bucket));
    HashTable* ht = malloc(sizeof(HashTable));
    hashtable_init(ht, 10, pl);

    int value1 = 42;
    char* key1 = "test";
    hashtable_insert(ht, key1, &value1);

    int* retrieved = (int*)hashtable_get(ht, key1);
    assert(retrieved != NULL);
    assert(*retrieved == value1);

    hashtable_free(ht);
    free(ht);
    pool_allocator_free(pl);
}

void test_hashtable_del() {
    pool_allocator* pl = pool_allocator_init(100, sizeof(bucket));
    HashTable* ht = malloc(sizeof(HashTable));
    hashtable_init(ht, 10, pl);

    int value1 = 42;
    char* key1 = "test_key";
    hashtable_insert(ht, key1, &value1);

    // Verify insertion worked
    int* retrieved = (int*)hashtable_get(ht, key1);
    assert(retrieved != NULL);

    // Delete and verify
    hashtable_del(ht, key1);
    retrieved = (int*)hashtable_get(ht, key1);
    assert(retrieved == NULL);

    hashtable_free(ht);
    free(ht);
    pool_allocator_free(pl);
}

void test_hashtable_collision() {
    pool_allocator* pl = pool_allocator_init(100, sizeof(bucket));
    HashTable* ht = malloc(sizeof(HashTable));
    hashtable_init(ht, 1, pl);

    int value1 = 42;
    int value2 = 84;
    char* key1 = "key1";
    char* key2 = "key2";

    hashtable_insert(ht, key1, &value1);
    hashtable_insert(ht, key2, &value2);

    int* retrieved1 = (int*)hashtable_get(ht, key1);
    int* retrieved2 = (int*)hashtable_get(ht, key2);

    assert(retrieved1 != NULL);
    assert(retrieved2 != NULL);
    assert(*retrieved1 == value1);
    assert(*retrieved2 == value2);

    hashtable_free(ht);
    free(ht);
    pool_allocator_free(pl);
}

void test_hashtable_final() {
    pool_allocator* pl = pool_allocator_init(100, sizeof(bucket));
    HashTable* ht = malloc(sizeof(HashTable));
    hashtable_init(ht, 10, pl);

    int values[5] = { 10, 20, 30, 40, 50 };
    char* keys[5] = { "one", "two", "three", "four", "five" };

    for (int i = 0; i < 5; i++) {
        hashtable_insert(ht, keys[i], &values[i]);
    }

    for (int i = 0; i < 5; i++) {
        int* retrieved = (int*)hashtable_get(ht, keys[i]);
        assert(retrieved != NULL);
        assert(*retrieved == values[i]);
    }

    hashtable_del(ht, keys[1]);
    hashtable_del(ht, keys[3]);

    assert(hashtable_get(ht, keys[1]) == NULL);
    assert(hashtable_get(ht, keys[3]) == NULL);

    assert(hashtable_get(ht, keys[0]) != NULL);
    assert(hashtable_get(ht, keys[2]) != NULL);
    assert(hashtable_get(ht, keys[4]) != NULL);

    hashtable_free(ht);
    free(ht);
    pool_allocator_free(pl);
}

int main() {
    test_hashtable_init();
    test_hashtable_insert_get();
    test_hashtable_del();
    test_hashtable_collision();
    test_hashtable_final();

    return 0;
}