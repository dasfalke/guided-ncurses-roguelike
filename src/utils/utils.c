#include <stdlib.h>
#include "utils.h"

/* Utility function for allocating memory on the heap. */
void *SafeMalloc(size_t size)
{
   void *vp;

   if ((vp = malloc(size)) == NULL)
   {
      fputs("malloc failure\n", stderr);
      exit(EXIT_FAILURE);
   }

   return vp;
}

