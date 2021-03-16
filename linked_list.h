//#include "proc.h"

#ifndef LINKED_LIST_DOT_H
#define LINKED_LIST_DOT_H

typedef struct node {
  // include struct for process in proc.h
  int i;
  struct proc * process;
  struct node * next;
}  node;

void insert(struct proc * p, int i);
//void del(char * alias);
node * get(int pid);
int isEmpty(void);
//void list(void);

// added:
node* pop(void); // removes and returns head.

#endif
