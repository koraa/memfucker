#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define true 0
#define false -1

// Unit conversion byte <--> ?
#define kb(x) (((size_t) x) * 1024)
#define mb(x) (kb(x) * 1024) // x * 1024**2
#define gb(x) (mb(x) * 1024) // x * 1024**3

#define to_kb(x) ((x) / 1024)
#define to_mb(x) (to_kb(x) / 1024)
#define to_gb(x) (to_mb(x) / 1024)

// Maxsize for allocation
#define maxalloc mb(512)

char* appname;

inline void fail(size_t size) {
  fprintf(stderr, "Could not allocate memory of length %li . Format:\n\n%s [size]\n\n", size, appname);
  exit(1);
}

/**
 * Allocate one block of memory
 */
inline char* blockalloc(size_t size) {
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
inline char** alloc(size_t size) {
  size_t blocknum = size / maxalloc;
  size_t lastsize = size % maxalloc;

  char** blocks = (char**) calloc(blocknum+1, sizeof(char*));

  long int cnt;
  for (cnt = 0; cnt < blocknum; cnt++) {
    blocks[cnt] = blockalloc(maxalloc);
    fprintf(stderr, "Block %li done: %li mb allocated.\n", 
      cnt, to_mb((cnt+1) * maxalloc));
  }

  if (lastsize > 0)
    blocks[blocknum /*last*/] = blockalloc(lastsize);  
  fprintf(stderr, "Block %li done! %li mb allocated.\n", 
    blocknum, to_mb(size));

  return blocks;
}

int main(int argc, char** argv) {
  appname = argv[0];

  if (argc < 2)
    fail(-1);
  size_t size = mb(atol(argv[1]));

  alloc(size);

  while (1) {
    sleep(500);
  }

  return 0;
}
