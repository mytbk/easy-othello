#include "debug.h"
#include <stdio.h>

const char player[]={'W','N','B'};

void printboard(int board[8][8])
{
	int i,j;
	for (i=0;i<8;i++){
		for (j=0;j<8;j++){
			putchar(player[1+board[i][j]]);
			putchar('\t');
		}
		putchar('\n');
	}
}

