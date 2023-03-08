#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Array
{
    unsigned int width; // represents size in bytes of each element in the array
    unsigned int nel; // represents number of element currently in the array
    unsigned int capacity; // represents the total number of elements that can be stored in the array
    void *data; // pointer to the contents of the array
};

struct Performance
{
    unsigned int reads;
    unsigned int writes;
    unsigned int mallocs;
    unsigned int frees;
};

struct Performance *newPerformance();

struct Array *newArray (struct Performance *performance, unsigned int width, unsigned int capacity);

void readItem (struct Performance *performance, struct Array *array, unsigned int index, void *dest);

void writeItem (struct Performance *performance, struct Array *array, unsigned int index, void *src); void printArray(struct Array *array);

void contract (struct Performance *performance, struct Array *array);

void freeArray (struct Performance *performance, struct Array *array);

void appendItem(struct Performance *performance, struct Array *array, void *src);

void insertItem (struct Performance *performance, struct Array *array,unsigned int index, void *src);

void prependItem (struct Performance *performance, struct Array *array, void *src);

void deleteItem (struct Performance *performance, struct Array *array, unsigned int index);
