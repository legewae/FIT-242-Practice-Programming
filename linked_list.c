#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

node* list_create(double value) {
    node* list = (struct node*)malloc(sizeof(struct node));
    list->value = value;
    list->next = NULL;
    return list;
}

int list_length(node* list) {
    if (list == NULL) return 0;
    int length = 1;
    node* cur = list;
    while (cur->next != NULL) {
        length++;
        cur = cur->next;
    }
    return length;
}

node* list_get(node* list, int index) {
    if (list == NULL) return NULL;
    int len = list_length(list);
    if (len < index + 1 || index < 0)return NULL;

    node* cur = list;

    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }

    return cur;
}

void list_add_start(node** list, double value) {
    if (list == NULL) return;
    node* node = list_create(value);
    node->next = *list;
    *list = node;
}

void list_add_end(node** list, double value) {
    if (list == NULL) return;
    node* new_node = list_create(value);
    node* prev_node = *list;
    while (prev_node->next != NULL) {
        prev_node = prev_node->next;
    }
    prev_node->next = new_node;
}

void list_add_at(node** list, int index, double value) {
    if (list == NULL) return;
    if (index == 0) {
        list_add_start(list, value);
        return;
    }

    node* new_node = list_create(value);

    node* prev_node = *list;
    for (int i = 0; i < index - 1;i++) {
        if (prev_node->next != NULL) {
            prev_node = prev_node->next;
        }
        else return;
    }

    if (prev_node->next != NULL) {
        new_node->next = prev_node->next;
    }
    prev_node->next = new_node;
}

void list_add_middle(node** list, double value) {
    list_add_at(list, list_length(*list) / 2, value);
}

void list_delete_at(node** list, int index) {
    if (list == NULL) return;
    node* prev_node = *list;
    if (index == 0) {
        if (prev_node->next != NULL) {
            *list = prev_node->next;
        }
        free(prev_node);
        return;
    }
    for (int i = 0; i < index - 1; i++) {
        if (prev_node->next != NULL) {
            prev_node = prev_node->next;
        }
        else return;
    }
    if (prev_node->next == NULL) return;

    node* to_delete = prev_node->next;

    if ((to_delete)->next) {
        prev_node->next = to_delete->next;
    }

    free(to_delete);
}

void list_printf(node* list) {
    if (list == NULL) return;
    node* prev_node = list;
    printf("%f ", prev_node->value);
    while (prev_node->next != NULL) {
        prev_node = prev_node->next;
        printf("%f ", prev_node->value);
    }
    printf("\n");
}

void list_free(node* list) {
    if (list == NULL) return;

    node* cur = list;
    node* next = NULL;

    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
}
