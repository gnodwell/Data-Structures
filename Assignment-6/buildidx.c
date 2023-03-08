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

    if (argc < 2) {
        fprintf( stderr, "Usage: %s filename.kv capacity\n", argv[0]);
    }
    else {
        FILE *fptr;
        FILE *khsPtr;
        FILE *vhsPtr;
        fptr = fopen(argv[1], "rb");
        char *khsFileName = NULL;
        char *vhsFileName = NULL;
        khsFileName = malloc(sizeof(char) * STRLEN);
        vhsFileName = malloc(sizeof(char) * STRLEN);
        getFileName(argv[1], "khs", khsFileName);
        getFileName(argv[1], "vhs", vhsFileName);

        khsPtr = fopen(khsFileName, "wb+");
        vhsPtr = fopen(vhsFileName, "wb+");

        write_empty(khsPtr, get_capacity(fptr) * 2);
        write_empty(vhsPtr, get_capacity(fptr) * 2);

        int capacity = get_capacity(fptr);
        fseek(fptr, 0, SEEK_SET);
        char key[STRLEN];
        char val[STRLEN];
        int index = 0;
        int hashVal;
        int checkLoc = 0;


        while (index < capacity/128) { //where index is val pointed to by fptr and capcity is total vals in fptr

            read_key(fptr, index, key);
            read_val(fptr, index, val);
            hashVal = hashfn(key, capacity*2);
            read_index(khsPtr, hashVal, &checkLoc);
            while (checkLoc != -1) {
                hashVal += STRLEN;
                if (feof(khsPtr)) {
                    fseek(khsPtr, 0, SEEK_SET);
                    hashVal = 0;
                }
                read_index(khsPtr, hashVal, &checkLoc);
            }
            if (checkLoc == -1) {
                write_index(khsPtr, index, hashVal);
            }

            hashVal = hashfn(val, capacity*2);
            read_index(vhsPtr, hashVal, &checkLoc);
            while (checkLoc != -1) {
                hashVal += 256;
                if (feof(khsPtr)) {
                    fseek(khsPtr, 0, SEEK_SET);
                    hashVal = 0;
                }
                read_index(vhsPtr, hashVal, &checkLoc);
            }
            if (checkLoc == -1) {
                write_index(vhsPtr, index, hashVal);
            }
            index ++;
        }

        free(khsFileName);
        free(vhsFileName);
        fclose(vhsPtr);
        fclose(khsPtr);
        fclose(fptr);

    }



    return 0;


}