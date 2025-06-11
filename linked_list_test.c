#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void test_list_create() {
	node* list = list_create(123);
	assert(list_length(list) == 1 && list->value == 123);
	list_free(list);
}

void test_list_end_start() {
	node* list = list_create(1);
	list_add_end(&list, 2);
	list_add_start(&list, 3);
	assert(list_get(list, 0)->value == 3 && list_get(list, 1)->value == 1 && list_get(list, 2)->value == 2);
	list_free(list);
}

void test_delete_at() {
	node* list = list_create(1);
	list_add_end(&list, 2);
	list_add_start(&list, 3);
	list_delete_at(&list, 1);
	assert(list_get(list, 0)->value == 3 && list_get(list, 1)->value == 2);
	list_free(list);
}

void test_delete_at_0() {
	node* list = list_create(1);
	list_add_end(&list, 2);
	list_add_start(&list, 3);
	list_delete_at(&list, 1);
	list_delete_at(&list, 0);
	assert(list_get(list, 0)->value == 2);
	list_free(list);
}

void test_fill_to_100() {
	node* list = list_create(1);
	for (int i = 2; i <= 100;i++) {
		list_add_end(&list, i);
	}
	assert(list_get(list, 63)->value == 64 && list_length(list) == 100);
	list_free(list);
}

void test_remove_middle() {
	node* list = list_create(1);
	list_add_end(&list, 2);
	list_add_end(&list, 3);
	list_add_end(&list, 4);
	list_add_end(&list, 5);
	list_delete_at(&list, 2);

	assert(list_get(list, 2)->value == 4);
}

void test_add_middle() {
	node* list = list_create(1);
	list_add_end(&list, 2);
	list_add_end(&list, 3);
	list_add_end(&list, 4);
	list_add_end(&list, 5);
	list_delete_at(&list, 2);
	list_add_middle(&list, 3);

	assert(list_get(list, 2)->value == 3);
}

int main() {
	test_list_create();
	test_list_end_start();
	test_delete_at();
	test_delete_at_0();
	test_fill_to_100();
	test_remove_middle();
	test_add_middle();
	return 0;
}
