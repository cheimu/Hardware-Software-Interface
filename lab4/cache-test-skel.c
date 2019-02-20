/*
Gaohong Liu
CSE 351 - Winter 2018
Lab 4 - Mystery Caches

Mystery Cache Geometries:
mystery0:
    block size: 64 
    size: 262144 
    associativity: 1
mystery1:
    block size = 8 
    cache size = 16384
    associativity = 4
mystery2:
    block size = 16
    cache size = 65536
    associativity = 16
mystery3:
    block size = 2 
    cache size = 131072
    associativity = 2
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  flush_cache();
  access_cache(0);
  int size = 0;
  while(access_cache(size)) {
      size++;
  }
  return size;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
  int size = block_size;
  flush_cache();
  access_cache(0);
  access_cache(block_size);
  while(access_cache(0)) {
     size = size + block_size;
     for (int i = block_size; i <= size; i+= block_size){
        access_cache(i);
     }
  }
  return size;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {
  /* YOUR CODE GOES HERE */
  int size = cache_size;
  int asso = 0;
  flush_cache();
  access_cache(0);
  while (access_cache(0)) {
      asso = 0;
      for (int i = cache_size; i <= size; i+=cache_size){
      	access_cache(i);
      	asso++;
      }
      size = size + cache_size;
  }
  return asso;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
