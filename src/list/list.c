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
    struct llist_node_t* temp;

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
    struct llist_node_t* temp;

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

    struct llist_node_t* node = NULL;
    node = malloc(sizeof(struct llist_node_t));
    
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

    struct llist_node_t* node = NULL;
    node = malloc(sizeof(struct llist_node_t));
    
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
    node->data = data;
    node->next = prev_node->next;
    prev_node->next = node;
    list->size++;

    return 1;
}

uint8_t llist_insert_index(struct llist_t* list, void* data, int index) {

    if(list == NULL || data == NULL)
        return 0;

    if(index > list->size)
        return 0;

    if(index == 0)
        return llist_push_front(list, data);

    if(index == list->size)
        return llist_push_back(list, data);

    int count = 0;

    struct llist_node_t* prev_node = list->head;
    struct llist_node_t* node = malloc(sizeof(struct llist_node_t));

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

    if(index > list->size)
        return NULL;

    if(index == 0)
        return llist_pop_front(list);

    if(index == list->size) 
        return llist_pop_back(list);

    struct llist_node_t* prev_node = list->head;
    struct llist_node_t* node = NULL;
    void *data;

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
    {
        list->head = node;
    }

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

    struct llist_node_t* temp = list_src->head;

    while(temp->next != node || temp->next == NULL)
        temp = temp->next;

    if(temp->next == NULL) 
        return 0;

    temp->next = node->next;
    list_src->size--;

    node->next = NULL;
    list_dst->tail->next = node;
    list_dst->tail = node;
    list_dst->size++;

    return 1;
}

struct llist_node_t* llist_index(struct llist_t *list, int index) {
    
    if(list == NULL)
        return (void *)list;

    if(index >= list->size)
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

    if(prev_node->next = list->tail)
        return dlist_push_back(list, data);

    struct dlist_node_t* node = malloc(sizeof(struct dlist_node_t));
    node->data = data;

    prev_node->next->prev = node;
    node->next = prev_node->next;
    node->prev = prev_node;
    prev_node->next = node;

    list->size++;

    return 1;
}

uint8_t dlist_insert_index(struct dlist_t* list, void* data, int index) {
    if(list == NULL || data == NULL)
        return 0;

    if(index > list->size)
        return 0;

    if(index == 0)
        return dlist_push_front(list, data);

    if(index == list->size)
        return dlist_push_back(list, data);

    struct dlist_node_t* node = malloc(sizeof(struct dlist_node_t));
    struct dlist_node_t* prev = list->head;
    int count = 0;

    while (1)
    {
        if(count+1 == index)
            break;

        count++;
        prev = prev->next;
    }
    
    prev->next->prev = node;
    node->next = prev->next;
    node->prev = prev;
    prev->next = node;

    list->size++;
    return 1;
}

void* dlist_pop_back(struct dlist_t* list);
void* dlist_pop_front(struct dlist_t* list);
void* dlist_remove(struct dlist_t* list, struct dlist_node_t* prev_node);
void* dlist_remove_index(struct dlist_t* list, int index);
void* dlist_find(struct dlist_t* list, uint8_t (*cmp)(void *, void *), void *data);
uint8_t dlist_invert(struct dlist_t* list);

uint8_t dlist_is_empty(struct dlist_t* list) {
    if(list == NULL)
        return 0;

    return list->size == 0;
}

struct dlist_node_t* dlist_next(struct dlist_node_t* node);
struct dlist_node_t* dlist_cnext(struct dlist_t* list, struct dlist_node_t* node);
uint8_t dlist_foreach(struct dlist_t* list, void (*op)(struct dlist_node_t*, void *), void *data);
uint8_t dlist_move(struct dlist_t *list_dst, struct dlist_t *list_src, struct dlist_node_t *node);
struct dlist_node_t* dlist_index(struct dlist_t *list, int index);
uint8_t dlist_rotate(struct dlist_t* list);
uint8_t dlist_rotate_back(struct dlist_t* list);
void dlist_print(struct dlist_t* list);