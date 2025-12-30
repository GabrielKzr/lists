#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct llist_node_t
{
    void* data;
    struct llist_node_t* next;
};

struct llist_t
{
    int size;
    struct llist_node_t* head;
    struct llist_node_t* tail;
};

uint8_t llist_init(struct llist_t* list);
uint8_t llist_clean(struct llist_t* list);
uint8_t llist_destroy(struct llist_t* list);
uint8_t llist_push_back(struct llist_t* list, void* data);
uint8_t llist_push_front(struct llist_t* list, void* data);
uint8_t llist_insert(struct llist_t* list, struct llist_node_t* prev_node, void* data);
uint8_t llist_insert_index(struct llist_t* list, void* data, int index);
void* llist_pop_back(struct llist_t* list);
void* llist_pop_front(struct llist_t* list);
void* llist_remove(struct llist_t* list, struct llist_node_t* prev_node);
void* llist_remove_index(struct llist_t* list, int index);
void* llist_find(struct llist_t* list, uint8_t (*cmp)(void *, void *), void *data);
uint8_t llist_invert(struct llist_t* list);
uint8_t llist_is_empty(struct llist_t* list);
struct llist_node_t* llist_next(struct llist_node_t* node);
struct llist_node_t* llist_cnext(struct llist_t* list, struct llist_node_t* node);
uint8_t llist_foreach(struct llist_t* list, void (*op)(struct llist_node_t*, void *), void *data);
uint8_t llist_move(struct llist_t *list_dst, struct llist_t *list_src, struct llist_node_t *node);
struct llist_node_t* llist_index(struct llist_t *list, int index);
uint8_t llist_rotate(struct llist_t* list);
uint8_t llist_rotate_back(struct llist_t* list);
void llist_print(struct llist_t* list);

#endif