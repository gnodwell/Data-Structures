#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Performance *newPerformance() { // creates a new struct performance

    struct Performance *performance;
    performance = malloc(sizeof(struct Performance));
    performance->reads = 0;
    performance->writes = 0;
    performance->frees = 0;
    performance->mallocs = 0;

    return performance;

} 


struct Array *newArray (struct Performance *performance, unsigned int width, unsigned int capacity) { // creates a new struct of type array

    struct Array *array;
    array = malloc(sizeof(struct Array));

    unsigned int hold = width * capacity;

    array->width = width;
    array->capacity = capacity;
    array->nel = 0;


    array->data = malloc(hold);;

    performance->mallocs++;

    return array;


}


void readItem (struct Performance *performance, struct Array *array, unsigned int index, void *dest) { // reads the data array and returns index

    
    if (index >= array->nel) {
        fprintf(stderr, "error during readItem\n");
        exit (0);
    }
    else {
        memcpy(dest, (char*)array->data + (array->width*index), array->width);
    }

    performance->reads++;
    

}


void writeItem (struct Performance *performance, struct Array *array, unsigned int index, void *src) { //adds an item into an array

    
    if (index > array->nel || array->nel >= array->capacity ) {
        fprintf(stderr, "Error during writeItem\n");
        exit(0);
    }
    else {
        memcpy((char*)(array->data) + (array->width*index), src, array->width);
        array->nel++;

    }
    
    performance->writes++;
}


void contract (struct Performance *performance, struct Array *array) { //takes the last item off the array

    if (array->nel == 0) {
        fprintf(stderr, "array->nel is empty");
        exit(0);
    }
    else {
        array->nel--;
    }

}


void freeArray (struct Performance *performance, struct Array *array) { // frees the array

    free(array->data);
    free(array);
    performance->frees++;

}


void appendItem (struct Performance *performance, struct Array *array, void *src) { // adds item to the end of the array

    writeItem(performance, array, array->nel, src);

}


void insertItem (struct Performance *performance, struct Array *array, unsigned int index, void *src) { // inserts item into the array at destination index


    void *holder = malloc(array->width);
    void *holder2 = malloc(array->width);


    readItem(performance, array, index, holder);
    writeItem(performance, array, index, src);
    array->nel--;
    index++;
    readItem(performance, array, index, holder2);
    array->nel++;
    while (index != array->nel) {
        readItem(performance, array, index, holder2);
        writeItem(performance, array, index, holder);
        index++;
        memcpy(holder, holder2, array->width);
        array->nel--;
    }

    free(holder);
    free(holder2);



}


void prependItem (struct Performance *performance, struct Array *array, void *src) { // adds item into the array at index 0

    insertItem(performance, array, 0, src);

}


void deleteItem (struct Performance *performance, struct Array *array, unsigned int index) { // deletes item at index 


    int counter = array->nel - 2;
    void *holder = malloc(array->width);
    void *holder2 = malloc(array->width);



    readItem(performance, array, array->nel-1, holder);

    contract (performance, array);

    while (counter > index-1) {
    readItem(performance, array, counter, holder2);
    writeItem(performance, array, counter, holder);
    memcpy(holder, holder2, array->width);
    array->nel--;
    counter--;
    }


    free(holder);
    free(holder2);


}