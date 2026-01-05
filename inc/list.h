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

struct dlist_node_t {
    void *data;
    struct dlist_node_t* next;
    struct dlist_node_t* prev;
};

struct dlist_t {
    int size;
    struct dlist_node_t* head;
    struct dlist_node_t* tail;
};

uint8_t dlist_init(struct dlist_t* list);
uint8_t dlist_clean(struct dlist_t* list);
uint8_t dlist_destroy(struct dlist_t* list);
uint8_t dlist_push_back(struct dlist_t* list, void* data);
uint8_t dlist_push_front(struct dlist_t* list, void* data);
uint8_t dlist_insert(struct dlist_t* list, struct dlist_node_t* prev_node, void* data);
uint8_t dlist_insert_index(struct dlist_t* list, void* data, int index);
void* dlist_pop_back(struct dlist_t* list);
void* dlist_pop_front(struct dlist_t* list);
void* dlist_remove(struct dlist_t* list, struct dlist_node_t* prev_node);
void* dlist_remove_index(struct dlist_t* list, int index);
void* dlist_find(struct dlist_t* list, uint8_t (*cmp)(void *, void *), void *data);
uint8_t dlist_invert(struct dlist_t* list);
uint8_t dlist_is_empty(struct dlist_t* list);
struct dlist_node_t* dlist_next(struct dlist_node_t* node);
struct dlist_node_t* dlist_cnext(struct dlist_t* list, struct dlist_node_t* node);
struct dlist_node_t* dlist_prev(struct dlist_node_t* node);
struct dlist_node_t* dlist_cprev(struct dlist_t* list, struct dlist_node_t* node);
uint8_t dlist_foreach(struct dlist_t* list, void (*op)(struct dlist_node_t*, void *), void *data);
uint8_t dlist_move(struct dlist_t *list_dst, struct dlist_t *list_src, struct dlist_node_t *node);
struct dlist_node_t* dlist_index(struct dlist_t *list, int index);
uint8_t dlist_rotate(struct dlist_t* list);
uint8_t dlist_rotate_back(struct dlist_t* list);
void dlist_print(struct dlist_t* list);

struct alist_node_t {
    void *data;
};

struct alist_t {
    size_t size;
    size_t capacity;
    struct alist_node_t* nodes;
    struct alist_node_t* begin;
    struct alist_node_t* end;
};

uint8_t alist_init(struct alist_t* list);
uint8_t alist_init_ex(struct alist_t* list, size_t size);
uint8_t alist_fill(struct alist_t* list, void* data);
uint8_t alist_resize(struct alist_t* list, size_t size);
uint8_t alist_reserve(struct alist_t* list, size_t size);
uint8_t alist_clean(struct alist_t* list);
uint8_t alist_destroy(struct alist_t* list);
uint8_t alist_push_back(struct alist_t* list, void* data);
uint8_t alist_insert(struct alist_t* list, void* data, size_t pos);
void* alist_pop_back(struct alist_t* list);
void* alist_erase(struct alist_t* list, size_t pos);
void* alist_at(struct alist_t* list, size_t pos);
void* alist_back(struct alist_t* list);
void* alist_front(struct alist_t* list);
uint8_t alist_is_empty(struct alist_t* list);
size_t alist_max_size();
uint8_t alist_shrink_to_fit(struct alist_t* list);
void alist_print(struct alist_t* list, void (*print_fn)(void *));

#endif