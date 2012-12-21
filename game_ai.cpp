#include "common.h"

/* list of AI */
Position naive_ai(Chess[][8],Chess);
int greedy_ai(Chess[][8],Chess);
/* end of AI list */

Position naive_ai(Chess board[8][8],Chess thischess)
	//just for test
{
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			if (judgeload(i,j,board,thischess))
				return (i<<4)|j;
		}
	}
}

Position game_ai(Chess board[8][8],Chess thischess)
{
	return greedy_ai(board,thischess);
}

