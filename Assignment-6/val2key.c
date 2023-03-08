#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

#define STRLEN 256

void getFileName(char *fileName, char *extension, char *newFile) {

    strncpy(newFile, fileName, strlen(fileName)-2);
    strcat(newFile, extension);

}


int main (int argc, char *argv[]) {

    if (argc != 3) {
        fprintf( stderr, "Usage: %s filename.kv ‘search term’\n", argv[0]);
    }
    else {
        FILE *fptr;
        FILE *vhsPtr;
        fptr = fopen(argv[1], "rb");

        char *vhsFileName = NULL;
        vhsFileName = malloc(sizeof(char) * STRLEN);
        getFileName(argv[1], "vhs", vhsFileName);
        vhsPtr = fopen(vhsFileName, "rb");

        int checkLoc = 1234;
        int reachedEOF = 0;
        int capacity = get_capacity(fptr);
        int hashVal = hashfn(argv[2], capacity*2);
        char key[STRLEN];
        char val[STRLEN];


        read_index(vhsPtr, hashVal, &checkLoc);
        read_val(fptr, checkLoc, val);


        if (strcmp(val, argv[2]) == 0) {
            read_key(fptr, checkLoc, key);
        }
        else {
            while(checkLoc != -1) {
                hashVal += 256;
                read_index(vhsPtr, hashVal, &checkLoc);
                read_val(fptr, checkLoc, val); 
                if (strcmp(val, argv[2]) == 0) {
                    read_key(fptr, checkLoc, key);
                    break;
                }
                if (hashVal >= capacity && reachedEOF == 0) {
                    hashVal = 0;
                    reachedEOF = 1;
                }
                else if (hashVal >= capacity && reachedEOF == 1) {
                    break;
                }
            }
        }
        if (strcmp(val, argv[2]) == 0) {
            printf("%s\n", key); 
        }
        else {
            printf("NOT FOUND\n");
        }


        


        free(vhsFileName);
        fclose(vhsPtr);
        fclose(fptr);
    }



    return 0;
}