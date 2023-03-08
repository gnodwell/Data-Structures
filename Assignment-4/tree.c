#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Performance *newPerformance() {

    struct Performance *performance;
    performance = malloc(sizeof(struct Performance));
    if (performance == NULL) {
        fprintf(stderr, "Error making performance\n");
        exit (0);
    }
    performance->reads = 0;
    performance->writes = 0;
    performance->frees = 0;
    performance->writes = 0;

    return performance;
}


void attachNode(struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width) {
    struct Node *newNode;
    newNode = malloc(sizeof(struct Node));
    newNode->data = malloc(sizeof(char) * width);
    if (newNode == NULL) {
        fprintf(stderr, "Error making newNode\n");
        exit (0);
    }
    memcpy(newNode->data, src, width);
    newNode->gte = NULL;
    newNode->lt = NULL;
    *node_ptr = newNode;

    
    performance->mallocs++;
    performance->writes++;

}


int comparNode (struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *node1, const void *node2), void *target) {

    performance->reads++;
    return (compar(target, (*node_ptr)->data));

}


struct Node **next(struct Performance *performance, struct Node **node_ptr, int direction) {

    performance->reads++;


    if (*node_ptr == NULL) {
        fprintf(stderr, "This tree is empty\n");
        exit (0);
    }

    if (direction < 0) {
        return &((*node_ptr)->lt);
    }
    else {
        return &((*node_ptr)->gte);
    }
    
}


void readNode (struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width) {


    if (*node_ptr == NULL) {
        fprintf(stderr, "This tree is empty\n");
        exit (0);
    }

    struct Node *node;
    node = *node_ptr;

    memcpy(dest, node->data, width);

    performance->reads++;

}


void detachNode(struct Performance *performance, struct Node **node_ptr) {

    if (*node_ptr == NULL) {
        fprintf(stderr, "This tree is empty\n");
        exit (0);
    }

    struct Node *freeNode;

    freeNode = *node_ptr;
    node_ptr = NULL;
    free(freeNode->data);
    free(freeNode);
    performance->frees++;

}


int isEmpty (struct Performance *performance, struct Node **node_ptr) {

    if (*node_ptr == NULL) {
        return 1;
    } 
    else {
        return 0;
    }

}


void addItem (struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *node1, const void *node2), void *src, unsigned int width) {

    struct Node **node;
    node = node_ptr;
    int direction;
    int checkTree;

    checkTree = isEmpty(performance, node);


    if (checkTree == 1) {
        attachNode(performance, node, src, width);

    }
    else {

        while (checkTree == 0) {
           if (checkTree == 0) {
                direction = compar((*node)->data, src);
            }
            node = next(performance, node, direction);
            checkTree = isEmpty(performance, node);
        }
        if (checkTree == 1) {
            attachNode(performance, node, src, width);
            
        }
    }
}

    


void freeTree(struct Performance *performance, struct Node **node_ptr) {

    if (isEmpty(performance, node_ptr) != 1) {
        freeTree(performance, next(performance, node_ptr, 1));
        freeTree(performance, next(performance, node_ptr, -1));
        detachNode(performance, node_ptr);
    }

}


int searchItem(struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *node1, const void *node2), void *target, unsigned int width) {

    int result;
    void *dest = NULL;
    dest = malloc(sizeof(char) * width);
    int ret1 = 0;
    int ret2 = 0;

    if (isEmpty(performance, node_ptr) != 1) {
        readNode(performance, node_ptr, dest, width);
        result = compar(dest, target);
        if (result == 0) {
            free(dest);
            return 1;
        }
        else {
            ret1 = searchItem(performance, next(performance, node_ptr, -1), compar, target, width);
            ret2 = searchItem(performance, next(performance, node_ptr, 1), compar, target, width);

            if (ret1 == 1 || ret2 == 1) {
                free(dest);
                return 1;
            }
        }
    }
    free(dest);

    return 0;
}


