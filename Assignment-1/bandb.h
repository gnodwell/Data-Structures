#include <string.h>

void getbytes (unsigned char dest[], int bytes, void *src, int reverse) {

    int i = 0; // initializes counter
    char *str = src; 

    if (reverse == 0) { //sets dest in proper order
        while (i < bytes) {
            dest[i] = str[i];
            i++;
        }
    }
    else if (reverse != 0) { // sets dest in reverse order
        int j = bytes;
        while (i < bytes) {
            dest[j-1] = str[i];
            j--;
            i++;

        }
    }
}



