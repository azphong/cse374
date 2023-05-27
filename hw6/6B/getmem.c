/* getmem.c
   implements getmem (malloc) for memory system
   CSE 374 HW6
*/

#include <assert.h>
#include "mem.h"
#include "mem_impl.h"

/* This code will be filled in by the students.  Your primary job is to
   implement getmem */

/* initialize global variables ?*/

freeNode* freelist = NULL;

/* Are there helper functions that only getmeme will need?  Declare here. */

/* Define your functions below: */

void* getmem(uintptr_t size) {
  /* make sure you return a pointer to the usable memory that
     is at least 'size' bytes long.
     To get you started we are 'stubbing in' a call that will
     return a usable value.  You will replace this code. */

   freeNode* curr = freelist;
   while(curr != NULL) {
      if(curr -> size > size) {
         return (void*)curr + NODESIZE;
      }
      curr = curr -> next;
   }

   curr = (freeNode*)malloc(BIGCHUNK);
   curr -> size = size;
   curr -> next = freelist;
   freelist = curr;

   return (void*)curr + NODESIZE;
}

