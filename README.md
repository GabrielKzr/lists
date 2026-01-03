# List Data Structures API

A C library implementing common list data structures with a simple and efficient API.

## Overview

This repository provides implementations of various list data structures in C. The library is designed to be lightweight, easy to use, and suitable for embedded systems and general-purpose applications.

## Current Implementations

### Singly Linked List

A complete implementation of a singly linked list with the following features:

- Dynamic memory management
- Generic data storage (void pointers)
- Comprehensive set of operations
- Forward-only traversal

#### Key Features

- **Insertion Operations**: Push front, push back, insert at index, insert after node
- **Removal Operations**: Pop front, pop back, remove by index, remove after node
- **Search Operations**: Find elements with custom comparison functions
- **List Manipulation**: Invert, rotate, move nodes between lists
- **Utilities**: Size tracking, empty check, iteration with callbacks

### Doubly Linked List

A complete implementation of a doubly linked list with bidirectional traversal capabilities:

- Dynamic memory management
- Generic data storage (void pointers)
- Bidirectional traversal with prev/next pointers
- Efficient insertion and removal in both directions

#### Key Features

- **Insertion Operations**: Push front, push back, insert at index, insert before/after node
- **Removal Operations**: Pop front, pop back, remove by index, remove specific nodes
- **Bidirectional Traversal**: Navigate forward and backward through the list
- **Search Operations**: Find elements with custom comparison functions
- **List Manipulation**: Invert, rotate, move nodes between lists
- **Utilities**: Size tracking, empty check, iteration with callbacks in both directions

## Roadmap

The following data structure will be added in future releases:

- [ ] **Dynamic Array** - Resizable array with automatic capacity management

## API Reference

### Singly Linked List

#### Data Structures

```c
struct llist_node_t {
    void* data;
    struct llist_node_t* next;
};

struct llist_t {
    int size;
    struct llist_node_t* head;
    struct llist_node_t* tail;
};
```

#### Functions

##### Initialization and Cleanup

```c
uint8_t llist_init(struct llist_t* list);
uint8_t llist_clean(struct llist_t* list);
uint8_t llist_destroy(struct llist_t* list);
```

##### Insertion Operations

```c
uint8_t llist_push_back(struct llist_t* list, void* data);
uint8_t llist_push_front(struct llist_t* list, void* data);
uint8_t llist_insert(struct llist_t* list, struct llist_node_t* prev_node, void* data);
uint8_t llist_insert_index(struct llist_t* list, void* data, int index);
```

##### Removal Operations

```c
void* llist_pop_back(struct llist_t* list);
void* llist_pop_front(struct llist_t* list);
void* llist_remove(struct llist_t* list, struct llist_node_t* prev_node);
void* llist_remove_index(struct llist_t* list, int index);
```

##### Search and Traversal

```c
void* llist_find(struct llist_t* list, uint8_t (*cmp)(void*, void*), void* data);
uint8_t llist_foreach(struct llist_t* list, void (*op)(struct llist_node_t*, void*), void* data);
struct llist_node_t* llist_index(struct llist_t* list, int index);
struct llist_node_t* llist_next(struct llist_node_t* node);
struct llist_node_t* llist_cnext(struct llist_t* list, struct llist_node_t* node);
```

##### List Manipulation

```c
uint8_t llist_invert(struct llist_t* list);
uint8_t llist_rotate(struct llist_t* list);
uint8_t llist_rotate_back(struct llist_t* list);
uint8_t llist_move(struct llist_t* list_dst, struct llist_t* list_src, struct llist_node_t* node);
```

##### Utility Functions

```c
uint8_t llist_is_empty(struct llist_t* list);
void llist_print(struct llist_t* list);
```

### Doubly Linked List

#### Data Structures

```c
struct dlist_node_t {
    void* data;
    struct dlist_node_t* next;
    struct dlist_node_t* prev;
};

struct dlist_t {
    int size;
    struct dlist_node_t* head;
    struct dlist_node_t* tail;
};
```

#### Functions

##### Initialization and Cleanup

```c
uint8_t dlist_init(struct dlist_t* list);
uint8_t dlist_clean(struct dlist_t* list);
uint8_t dlist_destroy(struct dlist_t* list);
```

##### Insertion Operations

```c
uint8_t dlist_push_back(struct dlist_t* list, void* data);
uint8_t dlist_push_front(struct dlist_t* list, void* data);
uint8_t dlist_insert(struct dlist_t* list, struct dlist_node_t* prev_node, void* data);
uint8_t dlist_insert_index(struct dlist_t* list, void* data, int index);
```

##### Removal Operations

```c
void* dlist_pop_back(struct dlist_t* list);
void* dlist_pop_front(struct dlist_t* list);
void* dlist_remove(struct dlist_t* list, struct dlist_node_t* prev_node);
void* dlist_remove_index(struct dlist_t* list, int index);
```

##### Search and Traversal

```c
void* dlist_find(struct dlist_t* list, uint8_t (*cmp)(void*, void*), void* data);
uint8_t dlist_foreach(struct dlist_t* list, void (*op)(struct dlist_node_t*, void*), void* data);
struct dlist_node_t* dlist_index(struct dlist_t* list, int index);
struct dlist_node_t* dlist_next(struct dlist_node_t* node);
struct dlist_node_t* dlist_cnext(struct dlist_t* list, struct dlist_node_t* node);
struct dlist_node_t* dlist_prev(struct dlist_node_t* node);
struct dlist_node_t* dlist_cprev(struct dlist_t* list, struct dlist_node_t* node);
```

##### List Manipulation

```c
uint8_t dlist_invert(struct dlist_t* list);
uint8_t dlist_rotate(struct dlist_t* list);
uint8_t dlist_rotate_back(struct dlist_t* list);
uint8_t dlist_move(struct dlist_t* list_dst, struct dlist_t* list_src, struct dlist_node_t* node);
```

##### Utility Functions

```c
uint8_t dlist_is_empty(struct dlist_t* list);
void dlist_print(struct dlist_t* list);
```

## Building

The project uses a Makefile for building:

```bash
# Build the project
make

# Build and run
make run

# Clean build artifacts
make clean
```

### Requirements

- GCC compiler
- C11 standard support
- Make build tool

### Compiler Flags

The project is compiled with the following flags:
- `-Wall -Wextra`: Enable comprehensive warnings
- `-std=c11`: Use C11 standard
- `-Wno-unused-parameter`: Suppress unused parameter warnings

## Usage Example

```c
#include "list.h"

// Custom comparison function
uint8_t compare_int(void* a, void* b) {
    int* ptr_a = (int*)a;
    int* ptr_b = (int*)b;
    return *ptr_a == *ptr_b;
}

int main() {
    // Create and initialize list
    struct llist_t* list = malloc(sizeof(struct llist_t));
    llist_init(list);
    
    // Add elements
    int data[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        llist_push_back(list, &data[i]);
    }
    
    // Find an element
    int search_value = 30;
    void* result = llist_find(list, compare_int, &search_value);
    
    // Remove element
    void* popped = llist_pop_front(list);
    
    // Clean up
    llist_destroy(list);
    free(list);
    
    return 0;
}
```

## Project Structure

```
.
├── Makefile          # Build configuration
├── README.md         # This file
├── inc/              # Header files
│   └── list.h        # List API declarations
├── src/              # Source files
│   ├── main.c        # Example usage and tests
│   └── list/
│       └── list.c    # Singly linked list implementation
└── obj/              # Object files (generated)
```

## License

This project is open source and available for use in personal and commercial projects.

## Contributing

Contributions are welcome! Feel free to submit issues and pull requests for:
- Bug fixes
- Performance improvements
- Documentation enhancements
- New data structure implementations

## Author

Developed as a comprehensive data structures library for C projects.

Gabriel Kaizer de Menezes  
Computer Engineering student at PUCRS  
GitHub: github.com/GabrielKzr