#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hash.h"


struct Performance *newPerformance() {

    struct Performance *performance;
    performance = malloc(sizeof(struct Performance));

    if (performance == NULL) {
        fprintf(stderr, "Problem creating performance\n");
        exit(0);
    }

    performance->frees = 0;
    performance->writes = 0;
    performance->mallocs = 0;
    performance->reads = 0;

    return performance;
    
}


struct HashTable *createTable( struct Performance *performance, unsigned int capacity, int (*hash)(void *stored, int max_val), int (*compar)(const void *val1, const void *val2)) {
  
    struct HashTable *table;
    table = malloc(sizeof(struct HashTable));

    if (table == NULL) {
        fprintf(stderr, "Trouble creating the hash table\n");
        exit(0);
    }
    table->capacity = capacity;
    table->nel = 0;
    table->compar = compar;
    table->hash = hash;
    table->data = malloc(sizeof(char*) * capacity); 
    if (table->data == NULL) {
        fprintf(stderr, "Trouble creating the data\n");
        exit(0);        
    }
    for (int i = 0; i < capacity; i++) {
        table->data[i] = NULL;
        performance->reads++;
    }
    performance->mallocs++;

    return table;
}


void addElement(struct Performance *performance, struct HashTable *table, void *src){

    int hold = 0;
    int check = 0;


    if (table->nel == table->capacity) {
        fprintf(stderr, "Table is at capacity\n");
        exit(0);
    }

    int index = table->hash(src, table->capacity);

    for (int i = index; i <= table->capacity-1; i++) {
        if (i == (table->capacity - 1) && hold == 0) {
            i = 0;
            hold = 1;
        }
        if (table->data[i] == NULL && check == 0) {
            table->data[i] = src;
            performance->writes++;
            table->nel++;
            check = 1;
        }
        if (check == 0) {
            performance->reads++;
        }

    }

}


int getIdx(struct Performance *performance, struct HashTable *table, void *src) {

    int index = table->hash(src, table->capacity);
    int comparVal;


    while (table->data[index] != NULL) {
        if (index == table->capacity - 1) {
            index = 0;
        }
        comparVal = table->compar(table->data[index], src);
        performance->reads++;
        if (comparVal == 0) {
            return index;
        }
        index++;

    }
    return -1;

}


void freeTable(struct Performance *performance, struct HashTable *table) {
    
    free(table->data);
    free(table);
    performance->frees++;
}


void *getElement(struct Performance *performance, struct HashTable *table, void *src) {

    int index = getIdx(performance, table, src);
    if (index != -1) {
        return table->data[index];
    }
    else {
        return NULL;
    }
}


void removeElement(struct Performance *performance, struct HashTable *table, void *target) {

    int index = getIdx(performance, table, target);

    if (index != -1) {
        table->data[index] = NULL;
        performance->writes++;
        table->nel--;
    }

}


int hashAccuracy( struct HashTable *table ) {

    int index;
    int diff;
    int sum = 0;
    for (int i = 0; i < table->capacity; i++) {
        if (table->data[i]) {
            index = table->hash(table->data[i], table->capacity);
            if (index < i) {
                diff = i - index;
                sum = sum + diff;
            }
            else if (index > i) {
                diff = table->capacity - index + i - 1;
                sum = sum + diff;
            }
        }
    }
    return sum;

}


void rehash( struct HashTable *table ){

    int hash_id;
    int tmp;

    for (int i = 0; i < table->capacity; i++) {
        if (table->data[i]) {
            hash_id = table->hash(table->data[i], table->capacity);

            if (hash_id < i) {
                tmp = hash_id;
                while(tmp != i) {
                    if (!table->data[tmp]) {
                        table->data[tmp] = table->data[i];
                        table->data[i] = NULL;
                        break;
                    }
                    tmp++;
                }
            }
            else if (hash_id > i) {
                tmp = hash_id;
                while(tmp != table->capacity) {
                    if (!table->data[tmp]) {
                        table->data[tmp] = table->data[i];
                        table->data[i] = NULL;
                        break;
                    }
                    tmp++;
                }
            }
        }
    }

}