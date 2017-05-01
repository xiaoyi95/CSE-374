// Xiaoyi Ling, Tiffany Luu
// CSE 374 Homework 6
// mem_impl.h
// Mar 2 2017

// Header files for memory implementation that is not
// a part of the public interface

#ifndef MEM_IMPL_H
#define MEM_IMPL_H

// Defines the free_node structure
struct free_node {
  uintptr_t size;
  struct free_node * next;
};

// Creates the free list node
extern struct free_node * free_list;
typedef struct free_node free_node;

// Declares the check_heap function
void check_heap();
void print_freelist(free_node * list);

// global variable for total memory allocated by underlying system
extern uintptr_t total_alloc;
// global variable for minimum block size
extern uintptr_t min_size;

#endif
