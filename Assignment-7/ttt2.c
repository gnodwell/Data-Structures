#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ttt.h"




void init_boards() {
    // goes through entire htable and sets init variable to 0
    for (int i = 0; i < HSIZE; i++) {
        (htable[i]).init = 0;
    }
}


int depth(Board board) {
    // returns number of markes on the board
    int numMoves = 0;
    for (int i = 0; i < BSIZE; i++) {
        if (board[i] == 'X' || board[i] == 'O') {
            numMoves++;
        }
    }
    return numMoves;
}


char winner (Board board) {
    int pos1;
    int pos2;
    int pos3;
    int WINS[8][3]  = {
                    {0,1,2}, // top row
                    {3,4,5}, // middle row
                    {6,7,8}, // bottom row
                    {0,3,6}, // left column
                    {1,4,7}, // middle column
                    {2,5,8}, // right column
                    {0,4,8}, // \ diagonal
                    {2,4,6}  // / diagonal
                  };

        for (int i = 0; i < 8; i++) {
            pos1 = WINS[i][0];
            pos2 = WINS[i][1];
            pos3 = WINS[i][2];
            // printf("pos1 -- %d\n", pos1);
            // printf("pos2 -- %d\n", pos2);
            // printf("pos3 -- %d\n", pos3);
            if (board[pos2idx[pos1]] == 'X' && board[pos2idx[pos2]] == 'X' && board[pos2idx[pos3]] == 'X') {
                // printf("test\n");
                int idx = board_hash(board);
                for (int j = 0; j < 9; j++) {
                    htable[idx].move[j] = -1;
                }
                return 'X';
            }
            else if (board[pos2idx[pos1]] == 'O' && board[pos2idx[pos2]] == 'O' && board[pos2idx[pos3]] == 'O') {
                int idx = board_hash(board);
                for (int j = 0; j < 9; j++) {
                    htable[idx].move[j] = -1;
                }
                return 'O';
            }
            else if (depth(board) == 9) {
                return '-';
            }
        }
        return '?';
}


char testWinner (Board board) {
    int pos1;
    int pos2;
    int pos3;
    int WINS[8][3]  = {
                    {0,1,2}, // top row
                    {3,4,5}, // middle row
                    {6,7,8}, // bottom row
                    {0,3,6}, // left column
                    {1,4,7}, // middle column
                    {2,5,8}, // right column
                    {0,4,8}, // \ diagonal
                    {2,4,6}  // / diagonal
                  };
    printf("inside winner -- \n%s\n", board);

        for (int i = 0; i < 8; i++) {
            pos1 = WINS[i][0];
            pos2 = WINS[i][1];
            pos3 = WINS[i][2];
            printf("pos1 -- %d\n", pos1);
            printf("pos2 -- %d\n", pos2);
            printf("pos3 -- %d\n", pos3);
            printf("pos 1 -- %c\n", board[(pos2idx[pos1])]);
            printf("pos 2 -- %c\n", board[(pos2idx[pos2])]);
            printf("pos 3 -- %c\n", board[(pos2idx[pos3])]);
            // printf("pos 1 -- %c\n", board[12]);
            // printf("pos 2 -- %c\n", board[14]);
            // printf("pos 3 -- %c\n", board[16]);
            printf("i -- %d\n", i);


            printf("uiasgbdfuijbasidjhbvfjasbefuj\n");

            if (board[pos2idx[pos1]] == 'X' && board[pos2idx[pos2]] == 'X' && board[pos2idx[pos3]] == 'X') {
                // printf("test\n");
                printf("this should ex\n");
                return 'X';
            }
            else if (board[pos2idx[pos1]] == 'O' && board[pos2idx[pos2]] == 'O' && board[pos2idx[pos3]] == 'O') {
                return 'O';
            }
            else if (depth(board) == 9) {
                return '-';
            }
        }
        return '?';
}



char turn(Board board) {
    if (depth(board) == 9 || winner(board) == 'X' || winner(board) == 'O') {
        return '-';
    }
    else if ((depth(board) % 2 == 1)) {
        return 'O';
    }
    else {
        return 'X';
    } // need to add - if a winner has been delcared
}


void init_board(Board board) {
    int idx = board_hash(board);
    htable[idx].init = 1;
    htable[idx].turn = turn(board);
    htable[idx].depth = depth(board);
    strcpy((htable[idx].board), board);
    htable[idx].winner = winner(board);
}



void join_graph(Board board) {

    // check if check if there is a peice in the spot
    // if spot if used store -1 in corresponding position in move array in the corresponding htable(computed by calling hashfunc)
    //  if the spot is empty make a copy of the board, place appropriate marker (turn(...)) in the appropriate spot in the array (pos2indx) in the string
    // compute hash value of new board and store it in move array
    // check if hash table already contains an entity (init != 0) if it does loop to next move position
    // if not create one by calling init_board and recursivley calling join board


    int idx = board_hash(board);
    int pos2idx[9] = { 0, 2, 4, 12, 14, 16, 24, 26, 28 };
    char cpy[31];

    for (int i = 0; i < 9; i++) {
        if (board[(pos2idx[i])] == 'X' || board[(pos2idx[i])] == 'O') {
            htable[idx].move[i] = -1;
        }
        else if (isdigit(board[pos2idx[i]]) != 0) {
            strcpy(cpy, board);
            cpy[pos2idx[i]] = turn(board);
            int newIdx = board_hash(cpy);
            htable[idx].move[i] = newIdx;

            // if (htable[htable[idx].move[i]].init != -1) {
            if (htable[htable[newIdx].move[i]].init != -1) {
                init_board(cpy);
                join_graph(cpy);
            }
        }
    }

}






















































