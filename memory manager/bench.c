// Xiaoyi Ling, Tiffany Luu
// CSE 374 Homework 6
// bench.c
// Mar 2 2017

// This program takes in arguments in the form:
//   bench [ntrials[pctget[pctlarge[small_limit[large_limit[random_seed]]]]]]
// Executes calls to getmem and freemem which allocates/frees blocks of
// random sizes in a random order.

// Parameter descriptions:
// ntrials: total number of getmem/freemem calls, integer greater than 0,
//          default 10000
// pctget: percentage of calls that should be getmem,
//         integer 0 to 100 inclusive, default 50
// pctlarge: percent of getmem calls that should be large blocks,
//           int 0-100 inclusive, default 10
// small_limit: largest size of bytes of a "small" block, default 200
// large_limit: largest size of bytes of a "large" block, should be larger
//              than small_limit, default 20000
// random_seed: seeds the random number generator, default time-of-day clock
// Assumes that the user inputs valid positve integers for each parameter.
// If the user input for the parameter is blank, uses default values.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include "mem.h"

#define NTRIALS 10000  // Total number of getmem/freemem calls
#define PCTGET 50  // Percent of getmem/freemem calls that should be getmem
#define PCTLARGE 10  // Percent of getmem calls that should get "large" blocks
#define SMALL_LIMIT 200  // Largest size of bytes of a "small" block
#define LARGE_LIMIT 20000  // Largest size of bytes of a "large" block
#define RANDOM_SEED time(NULL)  // Random number generator value

// Takes in arguments for the above parameters, uses default values if the
// value is not specified by the user. Runs a number of getmem and freemem
// tests, acquring small or large blocks according to the parameters given.
int main(int argc, char** argv) {
  int ntrials = NTRIALS;
  int pctget = PCTGET;
  int pctlarge = PCTLARGE;
  int small_limit = SMALL_LIMIT;
  int large_limit = LARGE_LIMIT;
  int random_seed = RANDOM_SEED;

  // Checks the the user has entered the correct amount of arguments
  if (argc > 7) {
    fprintf(stderr, "Error: too many arguments\n");
    return 1;
  }

  // Replaces the defaults with user values
  if (argc >= 2)
    ntrials = atoi(argv[1]);
  if (argc >= 3)
    pctget = atoi(argv[2]);
  if (argc >= 4)
    pctlarge = atoi(argv[3]);
  if (argc >= 5)
    small_limit = atoi(argv[4]);
  if (argc >= 6)
    large_limit = atoi(argv[5]);
  if (argc == 7)
    random_seed  = atoi(argv[6]);

  // Seeds the randomizer and initializes the memory manager
  srand(random_seed);
  void ** pointers = (void**)malloc(ntrials*sizeof(void*));
  int psize = 0;  // Number of blocks memory manager currently has

  uintptr_t total_size;  // total amount of memory from underlying system
  uintptr_t total_free;  // total amount of memory in the free list
  uintptr_t n_free_blocks;  // total amount of blocks in the free list
  int percent = 1;  // output printing percentage
  clock_t start;  // start time of execution
  clock_t end;  // current time of execution
  start = clock();

  // Runs the test ntrials times
  for (int i = 0; i < ntrials; i++) {
    if ((rand() % 100) < pctget) {  // Calls getmem
      if ((rand() % 100) < pctlarge) {  // Gets large block
        int getlarge = rand() % (large_limit - small_limit) + small_limit + 1;
        pointers[psize] = getmem(getlarge);
        psize++;
      } else {  // Gets small block
        int getsmall = rand() % small_limit + 1;
        pointers[psize] = getmem(getsmall);
        psize++;
      }
    } else {  // Calls freemem
      if (psize > 0) {
        int free = rand() % psize;
        freemem(pointers[free]);
        pointers[free] = NULL;
        if (free != psize - 1) {
          pointers[free] = pointers[psize-1];
          pointers[psize-1] = NULL;
        }
        psize--;
      }
    }
    // Prints output per 10% of execution of all calls
    if ((i+1) == (int)ntrials * percent / 10 || ntrials < 10) {
      get_mem_stats(&total_size, &total_free, &n_free_blocks);
      printf("Call %d:\n", i+1);
      end = clock();
      double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
      printf("Total CPU time used so far is: %.30f s\n", cpu_time);
      printf("Total amount of storage from underlying system: ");
      printf("%lu\n", total_size);
      printf("Total number of blocks on the free list: %lu\n", n_free_blocks);
      uintptr_t average;
      if (n_free_blocks == 0) {
        average = 0;
      } else {
        average = total_free/n_free_blocks;
      }
      printf("Average number of bytes in the free list blocks: ");
      printf("%lu\n\n", average);
      percent++;
    }
  }

  // Print the address and size of blocks in the free list to the file
  // called "data". Note that the data will append to the file
  // each time print_heap is called
  if (ntrials > 1) {
    FILE *f = fopen("data", "ab+");
    print_heap(f);
  }
  return 0;
}

