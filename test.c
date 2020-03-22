#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

#define RND_RANGE 1000

int main(int argc, char *argv[]) {
  srand(time(NULL));
  int n = atoi(argv[1]);

  list *a = NULL, *b = NULL;

  // insert nodes with the given n
  for (int i = 0; i < n; i++) {
    int tmp = rand() % RND_RANGE;
    insert_node(&a, tmp);
    insert_node(&b, tmp);
  }

  printf("the original list:\n");
  print_list(a);
  
  printf("the sorted list:\n");
  a = sort(a);
  print_list(a);

  b = sort_list(b);
  print_list(b);

  delete_list(a);
  delete_list(b);
  return 0;
}
