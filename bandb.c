#include <stdio.h>
#include "bandb.h"

int main (int argc, char **argv) {

    unsigned char dest[20];
    char str1[20];
    int bytes;
    int reverse;

    printf("Welcome to getbytes\n");
    printf("Please enter str1: ");
    scanf("%s", str1);
    printf("Please enter bytes: ");
    scanf("%d", &bytes);
    printf("Please enter dest: ");
    scanf("%s", dest);
    printf("Please enter reverse: ");
    scanf("%d", &reverse);

    getbytes(dest, bytes, str1, reverse);
    printf( "\"%s\"\n", dest );





    return 0;

}