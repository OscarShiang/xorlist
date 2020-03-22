#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define XOR(a, b) ((list *)((uintptr_t)(a) ^ (uintptr_t)(b)))

static inline void next_node(list **node, list **prev) {
  list *next = XOR((*node)->addr, *prev);
  *prev = *node;
  *node = next;
}

void print_list(list *head) {
  list *curr = head, *prev = NULL;
  while (curr) {
    printf("%d ", curr->data);
    next_node(&curr, &prev);
  }
  printf("\n");
}

void insert_node(list **l, int d) {
  list *tmp = malloc(sizeof(list));
  tmp->data = d;

  if (!(*l)) {
    tmp->addr = NULL;
  } else {
    (*l)->addr = XOR(tmp, (*l)->addr);
    tmp->addr = *l;
  }
  *l = tmp;
}

void delete_list(list *l) {
  while (l) {
    list *next = l->addr;
    if (next)
      next->addr = XOR(next->addr, l);
    free(l);
    l = next;
  }
}

list *sort(list *start) {
  if (!start || !start->addr)
    return start;

  list *left = start, *right = start->addr;
  left->addr = NULL;
  right->addr = XOR(right->addr, left);

  left = sort(left);
  right = sort(right);

  for (list *merge = NULL; left || right;) {
    if (!right || (left && left->data < right->data)) {
      list *next = left->addr;
      if (next)
        next->addr = XOR(left, next->addr);

      if (!merge) {
        start = merge = left;
        merge->addr = NULL;
      } else {
        merge->addr = XOR(merge->addr, left);
        left->addr = merge;
        merge = left;
      }
      left = next;
    } else {
      list *next = right->addr;
      if (next)
        next->addr = XOR(right, next->addr);

      if (!merge) {
        start = merge = right;
        merge->addr = NULL;
      } else {
        merge->addr = XOR(merge->addr, right);
        right->addr = merge;
        merge = right;
      }
      right = next;
    }
  }

  return start;
}

list *sort_list(list *start) {
  if (!start || !start->addr)
    return start;

  // divide the list into two parts
  list *left = start, *right = start->addr, *prevl = NULL, *prevr = start;

  while (right && XOR(right->addr, prevr)) {
    // slow = slow->next;
    next_node(&left, &prevl);

    // fast = fast->next->next;
    next_node(&right, &prevr);
    next_node(&right, &prevr);
  }

  right = XOR(left->addr, prevl);
  right->addr = XOR(right->addr, left);

  left->addr = XOR(left->addr, right);

  left = sort_list(start);
  right = sort_list(right);

  for (list *merge = NULL; left || right;) {
    if (!right || (left && left->data < right->data)) {
      list *next = left->addr;
      if (next)
        next->addr = XOR(left, next->addr);

      if (!merge) {
        start = merge = left;
        merge->addr = NULL;
      } else {
        merge->addr = XOR(merge->addr, left);
        left->addr = merge;
        merge = left;
      }
      left = next;
    } else {
      list *next = right->addr;
      if (next)
        next->addr = XOR(right, next->addr);

      if (!merge) {
        start = merge = right;
        merge->addr = NULL;
      } else {
        merge->addr = XOR(merge->addr, right);
        right->addr = merge;
        merge = right;
      }
      right = next;
    }
  }

  return start;
}
