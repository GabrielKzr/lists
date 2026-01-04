#include <list.h>

/*
struct llist_node_t
{
    void* data;
    llist_node_t* next;
};

struct llist_t
{
    int size;
    llist_node_t* head;
    llist_node_t* tail;
};
*/

uint8_t llist_init(struct llist_t* list) {

    if(list == NULL)
        return 0;

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return 1;
}

uint8_t llist_clean(struct llist_t* list) {

    if(list == NULL)
        return 0;

    struct llist_node_t* node = list->head;
    struct llist_node_t* temp = NULL;

    while (node != NULL)
    {
        if(node->data != NULL)
            free(node->data);

        temp = node->next;
        free(node);

        node = temp;
    }
    
    free(list);

    return 1;
}

uint8_t llist_destroy(struct llist_t* list) {
    
    if(list == NULL)
        return 0;

    struct llist_node_t* node = list->head;
    struct llist_node_t* temp = NULL;

    while (node != NULL)
    {
        temp = node->next;
        free(node);

        node = temp;
    }
    
    free(list);

    return 1;
}

uint8_t llist_push_back(struct llist_t* list, void* data) {
    if(list == NULL || data == NULL)
        return 0;

    struct llist_node_t* node = malloc(sizeof(struct llist_node_t));
    if(node == NULL)
        return 0;
    
    node->data = data;
    node->next = NULL;

    if(llist_is_empty(list)) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;

    return 1;
}

uint8_t llist_push_front(struct llist_t* list, void* data) {
    if(list == NULL || data == NULL)
        return 0;

    struct llist_node_t* node = malloc(sizeof(struct llist_node_t));
    if(node == NULL)
        return 0;
    
    node->data = data;
    
    if(llist_is_empty(list)) {
        node->next = NULL;
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head = node;
    }

    list->size++;

    return 1;
}

uint8_t llist_insert(struct llist_t* list, struct llist_node_t* prev_node, void* data) {

    if(list == NULL || prev_node == NULL || data == NULL)
        return 0;

    if(prev_node == list->tail)
        llist_push_back(list, data);

    struct llist_node_t* node = malloc(sizeof(struct llist_node_t));
    if(node == NULL)
        return 0;

    node->data = data;
    node->next = prev_node->next;
    prev_node->next = node;
    list->size++;

    return 1;
}

uint8_t llist_insert_index(struct llist_t* list, void* data, int index) {

    if(list == NULL || data == NULL)
        return 0;

    if(index > list->size || index < 0)
        return 0;

    if(index == 0)
        return llist_push_front(list, data);

    if(index == list->size)
        return llist_push_back(list, data);

    int count = 0;

    struct llist_node_t* prev_node = list->head;
    struct llist_node_t* node = malloc(sizeof(struct llist_node_t));
    if(node == NULL)
        return 0;

    node->data = data;

    while (prev_node != NULL)
    {   
        if(count+1 == index)
            break;

        count++;
        prev_node = prev_node->next;
    }
    
    node->next = prev_node->next;
    prev_node->next = node;
    list->size++;

    return 1;
}

void* llist_pop_back(struct llist_t* list) {
    if(list == NULL)
        return list;
    
    if(llist_is_empty(list))
        return NULL;

    struct llist_node_t* node = list->head;
    void* data = NULL;
    
    if(list->size == 1) {
        
        data = node->data;
        list->head = NULL;
        list->tail = NULL;
        
    } else {        
        while (node->next->next != NULL)
            node = node->next;
        
        list->tail = node;
        node = node->next;
        list->tail->next = NULL;
        data = node->data;
    }
    
    free(node);
    list->size--;
    return data;
}

void* llist_pop_front(struct llist_t* list) {
    
    if(list == NULL)
        return list;

    if(llist_is_empty(list))
        return NULL;

    struct llist_node_t* node = list->head;
    void *data = NULL;
    
    if(list->size == 1)
        list->tail = NULL;
    
    list->head = node->next;
    data = node->data;
    list->size--;
    free(node);

    return data;
}

void* llist_remove(struct llist_t* list, struct llist_node_t* prev_node) {

    if(list == NULL || prev_node == NULL)
        return NULL;

    if(llist_is_empty(list))
        return NULL;

    struct llist_node_t* node = prev_node->next;
    void *data = NULL;

    if(prev_node->next == list->tail) {
        list->tail = prev_node;
    }

    prev_node->next = node->next;
    data = node->data;
    list->size--;

    free(node);

    return data;
}

void* llist_remove_index(struct llist_t* list, int index) {
    if(list == NULL)
        return list;

    if(index > list->size || index < 0)
        return NULL;

    if(index == 0)
        return llist_pop_front(list);

    if(index == list->size-1) 
        return llist_pop_back(list);

    struct llist_node_t* prev_node = list->head;
    struct llist_node_t* node = NULL;
    void *data = NULL;

    int count = 0;

    while (prev_node != NULL)
    {
        if(count+1 == index)
            break;

        count++;
        prev_node = prev_node->next;
    }
    
    node = prev_node->next;
    prev_node->next = node->next;
    data = node->data;
    list->size--;

    free(node);

    return data;
}

void* llist_find(struct llist_t* list, uint8_t (*cmp)(void *, void *), void *data) {
    if(list == NULL || cmp == NULL || data == NULL)
        return NULL;

    struct llist_node_t* node = list->head;

    while(node != NULL) {
        if(cmp(node->data, data))
            return node->data;

        node = node->next;
    }

    return NULL;
}


static struct llist_node_t* _llist_invert(struct llist_t* list, struct llist_node_t* node, struct llist_node_t* last) {

    if(node == NULL) 
        return node;

    if(_llist_invert(list, node->next, node) == NULL)
        list->head = node;

    node->next = last;
    return node;
}

uint8_t llist_invert(struct llist_t* list) {

    if(list == NULL)
        return 0;

    if(list->size == 1)
        return 1;

    list->tail = _llist_invert(list, list->head, NULL);

    return 1;
}

uint8_t llist_is_empty(struct llist_t* list) {
    if(list == NULL)
        return 1;

    return list->size == 0;
}

struct llist_node_t* llist_next(struct llist_node_t* node) {
    if(node == NULL)
        return node;

    return node->next;
}
struct llist_node_t* llist_cnext(struct llist_t* list, struct llist_node_t* node) {
    if(node == NULL)
        return node;

    if(node->next == NULL)
        return list->head;

    return node->next;
}

uint8_t llist_foreach(struct llist_t* list, void (*op)(struct llist_node_t*, void *), void *data) {

    if(list == NULL || op == NULL)
        return 0; 

    struct llist_node_t* node = list->head;

    while (node != NULL)
    {
        op(node, data);
        node = node->next;
    }

    return 1;
}

uint8_t llist_move(struct llist_t *list_dst, struct llist_t *list_src, struct llist_node_t *node) {

    if(list_dst == NULL || list_src == NULL || node == NULL)    
        return 0;

    struct llist_node_t* cur = list_src->head;
    struct llist_node_t* prev = NULL;

    while (cur != NULL && cur != node)
    {
        prev = cur;
        cur = cur->next;
    }
    
    if(cur == NULL)
        return 0;

    if(prev == NULL)
        list_src->head = node->next;
    else
        prev->next = node->next;

    if(node == list_src->tail)
        list_src->tail = prev;

    list_src->size--;

    node->next = NULL;

    if(llist_is_empty(list_dst)) {
        list_dst->head = node;
        list_dst->tail = node;
    }
    else {
        list_dst->tail->next = node;
        list_dst->tail = node;
    }

    list_dst->size++;

    return 1;
}

struct llist_node_t* llist_index(struct llist_t *list, int index) {
    
    if(list == NULL)
        return (void *)list;

    if(index >= list->size || index < 0)
        return NULL;

    int count = 0;
    struct llist_node_t* node = list->head;

    while (node != NULL)
    {
        if(count == index) 
            return node;
        
        count++;
        node = node->next;
    }

    return NULL;
}

uint8_t llist_rotate(struct llist_t* list) {
    if(list == NULL)
        return 0;

    if(llist_is_empty(list))
        return 0;

    list->tail->next = list->head;
    list->head = list->tail;

    list->tail = list->tail->next;
    while(list->tail->next != list->head)
        list->tail = list->tail->next;

    list->tail->next = NULL;

    return 1;
}

uint8_t llist_rotate_back(struct llist_t* list) {
    if(list == NULL)
        return 0;

    if(llist_is_empty(list))
        return 0;
                                    //   ... -> tail -> NULL
    list->tail->next = list->head;  //   ... -> tail -> head -> head_next -> ...
    list->head = list->head->next;  //   ... -> tail -> tail_next -> head -> head_next -> ...
    list->tail = list->tail->next;  //   ... -> tail_prev -> tail -> head -> head_next -> ...
    list->tail->next = NULL;        //   ... -> tail_prev -> tail -> NULL

    return 1;
}

void llist_print(struct llist_t* list) {
    if(list == NULL)
        return;

    struct llist_node_t* node = list->head;
    int count = 0;

    while (node != NULL)
    {
        printf("node_%d -> ", count);
        count++;
        node = node->next;
    }
    printf("NULL\n");

    return;
}

/*
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
*/

uint8_t dlist_init(struct dlist_t* list) {

    if(list == NULL)
        return 0;

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return 1;
}

uint8_t dlist_clean(struct dlist_t* list) {

    if(list == NULL)
        return 0;

    struct dlist_node_t* node = list->head;
    struct dlist_node_t* temp = NULL;

    while (node != NULL)
    {
        if(node->data != NULL)
            free(node->data);

        temp = node;
        node = node->next;

        free(temp);
    }
    
    return 1;
}

uint8_t dlist_destroy(struct dlist_t* list) {

    if(list == NULL)
        return 0;

    struct dlist_node_t* node = list->head;
    struct dlist_node_t* temp = NULL;

    while (node != NULL)
    {
        temp = node;
        node = node->next;

        free(temp);
    }
    
    return 1;
}

uint8_t dlist_push_back(struct dlist_t* list, void* data) {

    if(list == NULL || data == NULL)
        return 0;

    struct dlist_node_t* node = malloc(sizeof(struct dlist_node_t));
    if(node == NULL)
        return 0;
    
    node->data = data;

    if(dlist_is_empty(list)) {
        node->prev = NULL;
        list->head = node;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
    }
    
    node->next = NULL;
    list->tail = node;

    list->size++;
    return 1;
}

uint8_t dlist_push_front(struct dlist_t* list, void* data) {
    if(list == NULL || data == NULL)
        return 0;

    struct dlist_node_t* node = malloc(sizeof(struct dlist_node_t));
    if(node == NULL)
        return 0;

    node->data = data;

    if(dlist_is_empty(list)) {
        node->next = NULL;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
    }
    
    node->prev = NULL;
    list->head = node;
    list->size++;

    return 1;
}

uint8_t dlist_insert(struct dlist_t* list, struct dlist_node_t* prev_node, void* data) {
    if(list == NULL || prev_node == NULL || data == NULL)
        return 0;

    if(prev_node == list->tail)
        return dlist_push_back(list, data);

    struct dlist_node_t* node = malloc(sizeof(struct dlist_node_t));
    if(node == NULL)
        return 0;

    node->data = data;

    prev_node->next->prev = node; // never seg fault 'cause never gonna insert back (handled before)
    node->next = prev_node->next;
    node->prev = prev_node;
    prev_node->next = node;

    list->size++;

    return 1;
}

uint8_t dlist_insert_index(struct dlist_t* list, void* data, int index) {
    if(list == NULL || data == NULL)
        return 0;
    
    if(index > list->size || index < 0)
        return 0;

    if(index == 0)
        return dlist_push_front(list, data);

    if(index == list->size)
        return dlist_push_back(list, data);

    struct dlist_node_t* node = malloc(sizeof(struct dlist_node_t));
    if(node == NULL)
        return 0;

    struct dlist_node_t* prev = list->head;
    node->data = data;
    int count = 0;

    while (1)
    {
        if(count+1 == index)
            break;
        count++;
        prev = prev->next;
    }

    prev->next->prev = node; // never seg fault 'cause never gonna insert back (handled before)
    node->next = prev->next;
    node->prev = prev;
    prev->next = node;

    list->size++;
    return 1;
}

void* dlist_pop_back(struct dlist_t* list) {

    if(list == NULL)
        return list;

    void* data = list->tail->data;
    list->tail = list->tail->prev;
    free(list->tail->next);
    list->tail->next = NULL;
    list->size--;

    return data;
}

void* dlist_pop_front(struct dlist_t* list) {
    if(list == NULL)
        return list;

    void* data = list->head->data;
    list->head = list->head->next;
    free(list->head->prev);
    list->head->prev = NULL;
    list->size--;

    return data;
}

void* dlist_remove(struct dlist_t* list, struct dlist_node_t* prev_node) {

    if(list == NULL || prev_node == NULL || prev_node->next == NULL)   
        return NULL;

    struct dlist_node_t* node = list->head;

    while (node != NULL)
    {
        if(node == prev_node)
            break;
        node = node->next;
    }
    
    if(node == NULL) // do not contains prev_node
        return node;

    void* data = prev_node->next->data;
    node = prev_node->next;

    if(node == list->tail) 
        list->tail = prev_node;
    else
        node->next->prev = prev_node;
    
    prev_node->next = node->next;

    free(node);
    list->size--;

    return data;
}

void* dlist_remove_index(struct dlist_t* list, int index) {
    if(list == NULL)
        return list;

    if(index >= list->size || index < 0)
        return NULL;

    if(index == 0)
        return dlist_pop_front(list);

    if(index == list->size-1)
        return dlist_pop_back(list);

    int count = 1;
    struct dlist_node_t* node = list->head->next;
    void* data = NULL;

    while (node != NULL)
    {
        if(count == index)
            break;

        count++;
        node = node->next;
    }

    if(node == NULL)
        return node;

    data = node->data;
    node->next->prev = node->prev;
    node->prev->next = node->next;
    list->size--;
    free(node);
    return data;
}

void* dlist_find(struct dlist_t* list, uint8_t (*cmp)(void *, void *), void *data) {
    if(list == NULL || cmp == NULL || data == NULL)
        return NULL;

    struct dlist_node_t* node = list->head;

    while (node != NULL)
    {
        if(cmp(node->data, data))
            return node->data;   

        node = node->next;
    }

    return NULL;
}

uint8_t dlist_invert(struct dlist_t* list) {
    if(list == NULL)
        return 0;

    struct dlist_node_t* node = list->head;
    struct dlist_node_t* next = NULL;

    while (node != NULL)
    {
        next = node->next;
        node->next = node->prev;
        node->prev = next;
        node = next;
    }
    
    next = list->tail;
    list->tail = list->head;
    list->head = next;

    return 1;
}

uint8_t dlist_is_empty(struct dlist_t* list) {
    if(list == NULL)
        return 0;

    return list->size == 0;
}

struct dlist_node_t* dlist_next(struct dlist_node_t* node) {
    if(node == NULL)
        return node;

    return node->next;
}

struct dlist_node_t* dlist_cnext(struct dlist_t* list, struct dlist_node_t* node) {
    if(list == NULL || node == NULL)
        return NULL;

    if(node == list->tail)
        return list->head;

    return node->next;
}

struct dlist_node_t* dlist_prev(struct dlist_node_t* node) {
    if(node == NULL)
        return node;

    return node->prev;
}

struct dlist_node_t* dlist_cprev(struct dlist_t* list, struct dlist_node_t* node) {
    if(list == NULL || node == NULL)
        return NULL;

    if(node == list->head)
        return list->tail;
    
    return node->prev;
}

uint8_t dlist_foreach(struct dlist_t* list, void (*op)(struct dlist_node_t*, void *), void *data) {
    if(list == NULL || op == NULL)
        return 0;

    struct dlist_node_t* node = list->head;

    while (node != NULL)
    {
        op(node, data);
        node = node->next;
    }

    return 1;
}

uint8_t dlist_move(struct dlist_t *list_dst, struct dlist_t *list_src, struct dlist_node_t *node) {

    if(list_dst == NULL || list_src == NULL || node == NULL) 
        return 0;

    struct dlist_node_t* _find = list_src->head;

    while (_find != NULL)
    {
        if(_find == node)
            break;
        
        _find = _find->next;
    }

    if(_find == NULL)
        return 0;

    if (node->prev != NULL)
        node->prev->next = node->next;
    else
        list_src->head = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;
    else
        list_src->tail = node->prev;

    list_src->size--;

    if(dlist_is_empty(list_dst)) {
        list_dst->head = node;
        node->prev = NULL;
    } else {
        list_dst->tail->next = node;
        node->prev = list_dst->tail;
    }
    
    list_dst->tail = node;
    node->next = NULL;
    list_dst->size++;

    return 1;
}

struct dlist_node_t* dlist_index(struct dlist_t *list, int index) {
    if(list == NULL)
        return (void *)list;

    if(index >= list->size || index < 0)
        return NULL;

    int count = 0;
    struct dlist_node_t* node = list->head;

    while (node != NULL)
    {
        if(count == index)
            return node;

        count++;
        node = node->next;
    }
    
    return NULL;
}

uint8_t dlist_rotate(struct dlist_t* list) {

    if(list == NULL)
        return 0;

    if(dlist_is_empty(list))
        return 0;

    list->tail->next = list->head;      //  ... <-> tail -> head <-> ...
    list->head->prev = list->tail;      //  ... <-> tail <-> head <-> ...
    list->head = list->tail;            //  ... <-> tail/head <-> head_next <-> ...
    list->tail = list->tail->prev;      //  ... <-> tail <-> head <-> ...
    list->tail->next = NULL;            //  ... <-> tail -> NULL
                                        //            |<-head
    list->head->prev = NULL;            //  ... <-> tail -> NULL

    return 1;
}   

uint8_t dlist_rotate_back(struct dlist_t* list) {

    if(list == NULL)
        return 0;

    if(dlist_is_empty(list))
        return 0;

    list->tail->next = list->head;
    list->head->prev = list->tail;
    list->tail = list->head;
    list->head = list->head->next;
    list->tail->next = NULL;
    list->head->prev = NULL;
    
    return 1;
}

void dlist_print(struct dlist_t* list) {
    if(list == NULL)
        return;

    int count = 0;
    struct dlist_node_t* node = list->head;

    printf("NULL ");
    while (node != NULL)
    {
        printf("<-> node_%d ", count);
        count++;
        node = node->next;
    }
    printf("<-> NULL\n");
}

/*
struct alist_node_t {
    void *data;
};

struct alist_t {
    int size;
    int real_size;
    struct alist_node_t* nodes;
    struct alist_node_t* begin;
    struct alist_node_t* end;
};
*/

uint8_t alist_init(struct alist_t* list) {
    
    if(list == NULL)
        return 0;

    list->size = 0;
    list->real_size = 0;
    list->nodes = NULL;
    list->begin = NULL;
    list->end = NULL;

    return 1;
}

uint8_t alist_init_ex(struct alist_t* list, int size) {

    if(list == NULL)    
        return 0;

    if(size < 0)
        return 0;

    if(size == 0) {
        alist_init(list);
        return 1;
    }

    list->size = size;
    list->real_size = size*2;
    list->nodes = malloc(list->real_size*sizeof(struct alist_node_t));

    for(int i = 0; i < list->real_size; i++) {
        list->nodes[i].data = NULL;
    }

    list->begin = &list->nodes[0];
    list->end = &list->nodes[list->size-1];

    return 1;
}

