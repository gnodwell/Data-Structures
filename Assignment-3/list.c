#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
 

struct Performance *newPerformance() { // creates a new struct performance

    struct Performance *performance;
    performance = malloc(sizeof(struct Performance));
    if (performance == NULL ){
        fprintf(stderr, "error making performance");
        exit (0);
    }
    performance->reads = 0;
    performance->writes = 0;
    performance->frees = 0;
    performance->mallocs = 0;

    return performance;

} 

void push(struct Performance *performance, Node **list_ptr, void *src, unsigned int width) {

    Node *head;
    head = malloc(sizeof(Node));
    head->data = malloc(sizeof(char) * width);

    memcpy(head->data, src, width);

    head->next = *list_ptr;
    *list_ptr = head;

    performance->writes++;
    performance->mallocs++;

}


void readHead(struct Performance *performance, Node **list_ptr, void *dest, unsigned int width) {

    Node *head;
    head = *list_ptr;

    if (list_ptr == NULL) {
        fprintf(stderr, "error during readHead, list is empty");
        exit (0);
    }

    memcpy(dest, head->data, width);
    performance->reads++;

}

void pop(struct Performance *performance, Node **list_ptr, void *dest, unsigned int width) {

    Node *head;
    Node *temp;

    head = *list_ptr;

    if (head == NULL) {
        fprintf(stderr, "error during readHead, list is empty");
        exit (0);        
    }

    memcpy(dest, head->data, width);
    temp = head;
    head = head->next;
    free(temp->data);
    free(temp);
    *list_ptr = head;
    performance->frees++;
    performance->reads++;

}


Node **next(struct Performance *performance, Node **list_ptr) {

    Node *head; 
    head = *list_ptr;

    if (head->data == NULL) {
        fprintf(stderr, "error during readHead, list is empty");
        exit (0);
    }

    performance->reads++;

    return &head->next;
}


int isEmpty(struct Performance *performance, Node **list_ptr) {

    if (*list_ptr == NULL) {
        return 1;
    }
    else {
        return 0;
    }

}


void freeList(struct Performance *performance, Node **list_ptr) {

    Node *head;
    head = *list_ptr;
    int j;

    while (!isEmpty(performance, &head))
  {
    pop( performance, &head, &j, sizeof(int) );
  }

  *list_ptr = head;

}


void readItem( struct Performance *performance, Node **list_ptr, unsigned int index, void *dest, unsigned int width) {

    Node *head;
    Node **ptr;

    ptr = list_ptr;


    for (int i = 0; i < index; i++) {
        ptr = next(performance, ptr);
    }

    head = *ptr;

    memcpy(dest, head->data, width);
    performance->reads++;

}


void appendItem( struct Performance *performance, struct Node**list_ptr, void *src, unsigned int width) {

    Node **ptr;
    ptr = list_ptr;

    while (isEmpty(performance, ptr) != 1) {
        ptr = next(performance, ptr);
    }
    push(performance, ptr, src, width);

}




void insertItem(struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width) {

    Node **ptr;
    ptr = list_ptr;

    if (index == 0) {
        push(performance, ptr, src, width);
    }
    else {
        for (int i = 0; i < index; i++) {
            ptr = next(performance, ptr);
        }
        push(performance, ptr, src, width);
    }
}


void prependItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width) {

    push(performance, list_ptr, src, width);

}


void deleteItem(struct Performance *performance, struct Node **list_ptr, unsigned int index ) {

    Node *head;
    head = *list_ptr;
    Node **ptr;
    ptr = list_ptr;
    int hold;

    if (index == 0) {
        pop(performance, ptr, &hold, sizeof(head->data));
    }
    else {
        for (int i = 0; i < index; i++) {
            ptr = next(performance, ptr);
        }
        pop(performance, ptr, &hold, sizeof(head->data));
    }

}


int findItem( struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *node1, const void *node2), void *target, unsigned int width) {

    int index = 0;
    Node *head;
    Node **nodePtr;
    char *s1 = NULL;
    s1 = malloc(sizeof(char) * width + 1);
    nodePtr = list_ptr;
    int size = findSize(performance, list_ptr);

    while ((index) != size) {
        head = *nodePtr;

        strcpy(s1, head->data);
        if (compar(target, s1) == 0) {
            free(s1);
            return index;
        }
        nodePtr = next(performance, nodePtr);
        index++;
    }
    free(s1);
    return -1;
}


int findSize (struct Performance *performance, Node **list_ptr) {

    int size = 0;
    Node **ptr;
    ptr = list_ptr;

    while (isEmpty(performance, ptr) != 1) {
        ptr = next(performance, ptr);
        size++;
    }

    return size;
}
