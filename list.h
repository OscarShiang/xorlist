#ifndef _LIST_H_
#define _LIST_H_

#include <stdint.h>

typedef struct __list list;
struct __list {
  int data;
  struct __list *addr;
};

void print_list(list *head);
void insert_node(list **l, int d);
void delete_list(list *l);

list *sort(list *start);
list *sort_list(list *start);

#endif /* _LIST_H_ */
