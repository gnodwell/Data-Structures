#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ttt.h"

int main() {
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);

    int count = 0;

    for (int i = 0; i < HSIZE; i++) {
        if (htable[i].init == 1) {
            count++;
        }
    }

    printf("Nodes -- %d\n", count);

    return 0;
}          