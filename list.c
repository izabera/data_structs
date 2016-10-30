#include <string.h>

// normal doubly linked list:
// struct node {
//   struct node *next, *previous;
//   void *data;
// };


// instead of storing pointers to the next and previous element, use
// separate arrays with ints to indicate the positions
// - index array is divided in 64 byte blocks
// - use short up to 32k elements, then int up to 2b, then stop using lists
// - the user is responsible for allocating and freeing data
// - push back doesn't even require allocation

struct {
  int used,
      allocated,
      head, // index of first element (not always 0)
      tail;

  void **data; // an array of pointers to the actual content

  union { // *next and *prev store all the indeces of next and previous elements
    struct { short *snext, *sprev; }; // for lists up to 32k elems
    struct { int   *inext, *iprev; }; // beyond 32k
    struct { void   *next,  *prev; }; // this is just for ease of use
  };

  // when a 64 byte block is emptied, add it to this stack
  int freeblockcount;
  void *freeblocks;
} List;


// allocation strategy:
// - start by allocating 854 bytes
// - resize by 1.5x and mask with & ~ 63
// 
// why 854?
// in x * 1.5 & ~63, all numbers in 854..895 reach 32320
// which is just below SHRT_MAX
//
//   854 => 32320
// 14422 => 32448
//  4310 => 32512
//  9686 => 32640
// 14550 => 32704
//
// if 854 is too large as a first allocation, the next best is to get to 30336:
// 100..213, 256..298, 384..426, 555..597, 811..853


void delete_list(list *l, 
void insert_list(list *l, 



// benchmark:
// - insert 100k elements in random positions in the list
// - then remove the (rand() % 10k)-th
// - then insert 90k elements in random positions again
// - then print the elements
