#include <stdlib.h>
#include <stdio.h>

#define true 0
#define false -1

// Unit conversion byte --> ?
#define kb(x) ((long) x) * 1024
#define mb(x) kb(x) * 1024 // x * 1024**2
#define gb(x) mb(x) * 1024

// Maxsize for allocation
#define maxalloc mb(512)

char* appname;

inline void fail(long size) {
  fprintf(stderr, "Could not allocate memory of length %li . Format:\n\n%s [size]\n\n", size, appname);
  exit(1);
}

/**
 * Allocate one block of memory
 */
inline char* blockalloc(long size) {
  char* pt = (char*) malloc(size);
  if (pt == NULL || size < 1) 
    fail(size);

  int cnt;
  for (cnt = 0; cnt < size; cnt++)
    pt[cnt] = (char)23;

  return pt;
}

/**
 * Allocate multiple block of memory of size n.
 */
inline char** alloc(long size) {
  long blocknum = size / maxalloc,
       lastsize = size % maxalloc;

  char** blocks = (char**) calloc(blocknum+1, sizeof(char*));

  int cnt;
  for (cnt = 0; cnt < blocknum; cnt++)
    blocks[cnt] = blockalloc(maxalloc);
  blocks[blocknum /*last*/] = blockalloc(lastsize);

  return blocks;
}

int main(int argc, char** argv) {
  appname = argv[0];

  if (argc < 2)
    fail(-1);
  long size = mb(atol(argv[1]));

  alloc(size);

  while (1) {
    sleep(500);
  }

  return 0;
}
