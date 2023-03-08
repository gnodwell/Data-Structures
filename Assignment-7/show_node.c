#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ttt.h"


int main(int argc, char *argv[]) {
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);
    for (int i = 0; i < argc-1; i++) {
        int arg;
        arg = atoi(argv[i+1]);
        print_node(htable[arg]);        
    }

    return 0;
}