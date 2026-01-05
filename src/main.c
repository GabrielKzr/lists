#include "list.h"

void list_print_data(struct llist_node_t* node, void *data) {

    int* ptr = (int *)node->data;
    int val = *ptr;

    printf("val %d -> ", val);
}

uint8_t cmp(void *a, void *b) {

    int* ptra = (int*)a;
    int* ptrb = (int*)b;

    return *ptra == *ptrb;
}

void linked_list_test() {
    struct llist_t *list = malloc(sizeof(struct llist_t));
    struct llist_t *list2 = malloc(sizeof(struct llist_t));

    llist_init(list);
    llist_init(list2);

    int num_data = 10;
    int data[num_data];

// Tests - Add

    for(int i = 0; i < num_data; i++) {
        data[i] = i;
        llist_push_back(list, &data[i]);
        llist_push_back(list2, &data[i]);
    }

    for(int i = 0; i < num_data; i++) {
        llist_push_front(list, &data[i]);
    }

    int data_test = 123;
    llist_insert(list, list->head->next->next->next, &data_test);
    llist_insert_index(list, &data_test, 10);
    llist_insert_index(list, &data_test, 0);


// Tests - Remove

    int* ptr1 = (int *)llist_pop_back(list);
    printf("ptr1 val -> %d\n", *ptr1);
    
    int* ptr2 = (int *)llist_pop_front(list);
    printf("ptr2 val -> %d\n", *ptr2);

    int* ptr3 = (int *)llist_remove(list, list->head->next->next);
    printf("ptr3 val -> %d\n", *ptr3);

    int* ptr4 = (int *)llist_remove_index(list, 1);
    printf("ptr3 val -> %d\n", *ptr4);

// Tests - aux

    int cmp_val = 8;
    if(llist_find(list, cmp, &cmp_val) != NULL) {
        printf("found\n");
    } else {
        printf("not found\n");
    }

    llist_invert(list);

    if(llist_is_empty(list)) {
        printf("empty\n");
    } else {
        printf("not empty\n");
    }

    printf("val head_next %d\n", *((int *)llist_next(list->head)->data));

    printf("val tail_cnext %d\n", *((int *)llist_cnext(list, list->tail)->data));


    llist_move(list2, list, list->head->next->next);

    int *ptr_index = (int *)(llist_index(list, 6)->data);
    printf("val ptr_index %d\n", *ptr_index);

    llist_rotate(list2);
    llist_rotate(list2);
    llist_rotate(list2);
    llist_rotate(list2);
    llist_rotate_back(list2);

// Tests - Prints/Debug

    printf("-------------- LIST 1 -------------\n");

    llist_foreach(list, list_print_data, NULL);
    printf("NULL\n");

    printf("list size -> %d\n", list->size);
    llist_print(list);
    llist_destroy(list);

    printf("-------------- LIST 2 -------------\n");

    llist_foreach(list2, list_print_data, NULL);
    printf("NULL\n");

    printf("list2 size -> %d\n", list2->size);
    llist_print(list2);
    llist_destroy(list2);

    printf("ok\n");
}

void double_list_print_data(struct dlist_node_t* node, void *data) {

    int* ptr = (int *)node->data;
    int val = *ptr;

    printf("val %d <-> ", val);
}

void double_linked_list_test() {

    struct dlist_t* list = malloc(sizeof(struct dlist_t));
    struct dlist_t* list2 = malloc(sizeof(struct dlist_t));

    int num_values = 10;
    int values[10];

    dlist_init(list);
    dlist_init(list2);

// Tests -  Add

    for(int i = 0; i < num_values; i++) {
        values[i] = i;
        dlist_push_back(list, &values[i]);
    }

    for(int i = 0; i < num_values; i++) {
        values[i] = i;
        dlist_push_front(list, &values[i]);
    }

    /*
    for(int i = 0; i < num_values; i++) {
        values[i] = i;
        dlist_push_back(list2, &values[i]);
    }
    */

    printf("val AAAAAAAAa %d\n", *(int *)list->tail->prev->data);

    int insert_data = 12345;
    dlist_insert(list, list->tail->prev, &insert_data);
    dlist_insert_index(list, &insert_data, (list->size)-1);

// Tests - remove

    int* ptr1 = (int *)dlist_pop_back(list);
    printf("ptr1 val -> %d\n", *ptr1);
    
    int* ptr2 = (int *)dlist_pop_front(list);
    printf("ptr2 val -> %d\n", *ptr2);

    int* ptr3 = (int *)dlist_remove(list, list->tail->prev);
    printf("ptr3 val -> %d\n", *ptr3);

    int* ptr4 = (int *)dlist_remove_index(list, list->size-1);
    printf("ptr3 val -> %d\n", *ptr4);

// Tests - aux

    int cmp_val = 123456;
    if(dlist_find(list, cmp, &cmp_val) != NULL) {
        printf("found\n");
    } else {
        printf("not found\n");
    }

    dlist_push_back(list, &cmp_val);

    dlist_invert(list);

    if(dlist_is_empty(list)) {
        printf("empty\n");
    } else {
        printf("not empty\n");
    }

    printf("head_next val %d\n", *(int *)dlist_next(list->head)->data);
    printf("tail_cnext val %d\n", *(int *)dlist_cnext(list, list->tail)->data);
    printf("tail_prev val %d\n", *(int *)dlist_prev(list->tail)->data);
    printf("tail_prev val %d\n", *(int *)dlist_cprev(list, list->head)->data);

    dlist_move(list2, list, list->head);
    dlist_move(list, list2, list2->head);
    dlist_move(list2, list, list->tail);

    int *ptr_index = (int *)(dlist_index(list, list->size-2)->data);
    printf("val ptr_index %d\n", *ptr_index);

    dlist_rotate(list);
    dlist_rotate_back(list);



    printf("\n ------------------------------- \n\n");
    
    printf("NULL <-> ");
    dlist_foreach(list, double_list_print_data, NULL);
    printf("NULL\n");

    printf("\n ------------------------------- \n\n");

    printf("\n ------------------------------- \n\n");
    
    printf("NULL <-> ");
    dlist_foreach(list2, double_list_print_data, NULL);
    printf("NULL\n");

    printf("\n ------------------------------- \n\n");

    dlist_print(list);
    dlist_destroy(list);
    dlist_destroy(list2);
    printf("ok\n");
}

void print_fn(void *data) {

    int* ptr = (int *)data;
    int val = *ptr;

    printf("%d, ", val);
}

void array_list_test() {
    
    struct alist_t* list = malloc(sizeof(struct alist_t));
    alist_init_ex(list, 10);

    int fill_data = 123;
    alist_fill(list, &fill_data);

    int more_data = 987;    
    for(int i = 0; i < 10; i++) {
        alist_push_back(list, &more_data);
    }
    int test_data = 1234556678;
    alist_push_back(list, &test_data);

    int insert_data = 675483;
    alist_insert(list, &insert_data, 0);
    alist_insert(list, &insert_data, list->size);
    alist_insert(list, &insert_data, list->size-1);


    list->nodes[1].data = &test_data;
    
    alist_print(list, print_fn);
    
    printf("list->begin.data %d\n", *(int *)list->begin->data);
    printf("list->end.data %d\n", *(int *)list->end->data);
    printf("list->size %ld\n", list->size);
    printf("list->capacity %ld\n", list->capacity);

    alist_destroy(list);
    free(list);

    printf("ok\n");
}

int main() 
{
    // printf("Hello, World!\n");
    // linked_list_test();
    // double_linked_list_test();
    array_list_test();

    /*
    int* test = malloc(5*sizeof(int));
    
    for(int i = 0; i < 5; i++) {
        test[i] = i;
        printf("val %d\n", test[i]);
    }
    
    free(test);
    */

    return 0;
}