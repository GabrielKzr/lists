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

int main() 
{
    // printf("Hello, World!\n");
    linked_list_test();

    return 0;
}