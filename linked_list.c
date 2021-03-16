#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "proc.h"
#include "linked_list.h"
#include "param.h"

struct node * head = NULL;
struct node * tail = NULL;

void insert(struct proc * p, int i) {
    
    struct node * n = (struct node *) malloc(sizeof(struct node));
    n->process = p;
    n->next = NULL;
    n->i = i;
    
    if (head == NULL) {  // create new list if there isnt one yet
        head = n;
        tail = n;
        return;
    }
    
    tail->next = n;
    tail = n;
}

// removes head from list. Rn it does nothing with it.
node* pop() {
  if (head == NULL) {
          return NULL;
  }
  struct node * temp = head;
  head = head->next;
  return temp;
}

int isEmpty() {
  if (head == NULL)
    return 1;
  return 0;
}


// I dont think we will need the other functions but I won't delete them yet just in case
/*
void del(char * alias) {
    struct node * curr = head;
    struct node * prev = NULL;

    // if list is empty
    if (head == NULL) {
        return;
    }

    // until we find the right alias
    while (strcmp(curr->alias , alias) != 0) {
        // if end is reached
        if (curr->next == NULL) {
            return;
        } else {  // else keep looking
            prev = curr;
            curr = curr->next;
        }
    }

    // at this point the match has been found

    // if the match is first
    if (curr == head) {
        head = head->next;
    } else {
        prev->next = curr->next;  // remove node from chain
    }

    return;
}
*/
node * get(int pid) {
    struct node * curr = NULL;
    struct node * invalid = (struct node *) malloc(sizeof(struct node));
    invalid->i = -1;

    // if list is empty
    if (head == NULL) {
        return invalid;
    }

    curr = head;

    // until we find the right alias
    while (curr->process->pid != pid) {
        // if end is reached
        if (curr->next == NULL) {
            return invalid;
        } else {  // else keep looking
            curr = curr->next;
        }
    }

    // at this point the match has been found
    return curr;
}
/*
void list() {
    struct node * curr = head;
    while (curr != NULL) {
        printf("%s %s\n", curr->alias, curr->orig);
        curr = curr->next;
    }
    return;
    */
//}
