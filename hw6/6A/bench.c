/* bench.c is the benchmarking /test program for mem memory management
   bench.c is implemented as part of HW6, CSE374 22WI
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "mem.h"

/* print_stats is a helper function that prints performance
   information about the memory system.  Requires a clock_t start
   time, and prints elapsed time plus results from get_mem_stats()
*/
void print_stats(clock_t start);

/* fill_mem is a helper function that takes in an address and the
   size of the memory allocation at that address.  It should fill
   the first 16 bytes (or up to size) with hexedecimal values.*/
void fill_mem(void* ptr, uintptr_t size);

/* Synopsis:   bench (main)
   [ntrials] (10000) getmem + freemem calls
   [pctget] (50) % of calls that are get mem
   [pctlarge] (10) % of calls requesting more memory than lower limit
   [small_limit] (200) largest size in bytes of small block
   [large_limit] (20000) largest size in byes of large block
   [random_seed] (time) initial seed for randn
*/
int main(int argc, char** argv ) {
  // Initialize the parameters
  int NTRIALS = 10000;
  int PCTGET = 50;
  int PCTLARGE = 10;
  int SMALL_L = 200;
  int LARGE_L = 20000;

  srand((unsigned) time(NULL));

  /* write code to set the above values based on the input arguments
     if there is not a corresponding input argument use the
     default value in the spec. */
  if(argc > 1) NTRIALS        = atoi(argv[1]);
  if(argc > 2) PCTGET         = atoi(argv[2]);
  if(argc > 3) PCTLARGE       = atoi(argv[3]);
  if(argc > 4) SMALL_L        = atoi(argv[4]);
  if(argc > 5) LARGE_L        = atoi(argv[5]);
  if(argc > 6) srand((unsigned) atoi(argv[6]));

  printf("Running bench for %d trials, %d%% getmem calls.\n", NTRIALS, PCTGET);

  void* blocks[NTRIALS];  // upperbound block storage
  int ntrials = 0, nblocks = 0, print_ctr = 1;
  int size, to_free;
  clock_t start = clock();

  // perform NTRIALS mem operations

  /* Students will fill in this section according to the assignment
     specs.*/
  for(ntrials = 0; ntrials < NTRIALS; ntrials++) {
    if((rand() % 100) >= PCTGET) {
      if((rand() % 100) >= PCTLARGE) {
        size = (rand() % (LARGE_L - SMALL_L)) + SMALL_L + 1;
      } else {
        size = (rand() % SMALL_L) + 1;
      }
      blocks[nblocks] = getmem(size);
      if(blocks[nblocks] != NULL) {
        fill_mem(blocks[nblocks], size);
        nblocks++;
      }
    } else {
      if(nblocks <= 0) continue;
      to_free = rand() % nblocks;
      freemem(blocks[to_free]);
      if(to_free != (nblocks - 1)) {
        blocks[to_free] = blocks[nblocks - 1];
      }
      nblocks--;
    }
    if(ntrials > (NTRIALS / 10) * print_ctr) {
      print_stats(start);
      print_ctr++;
    }   
  }
  return EXIT_SUCCESS;
}

/* Define helper functions here. */
void fill_mem(void* ptr, uintptr_t size) {
  char* char_ptr;
  int fill_amount = (size > 16) ? 16 : size;
  for(int i = 0; i < fill_amount; i++) {
    char_ptr = (char*)ptr + i;
    *char_ptr = 0xFE;
  }
}

void print_stats(clock_t start) {
  uintptr_t total_size, total_free, n_free_blocks;
  get_mem_stats(&total_size, &total_free, &n_free_blocks);
  printf("CPU Time: %lu\t", clock() - start);
  printf("Storage acquired: %lu\t", total_size);
  printf("Free blocks: %lu\t", n_free_blocks);
  printf("Average bytes per free block: %lu\n", total_free/n_free_blocks);
}
