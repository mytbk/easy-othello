#include "common.h"

Position naive_ai(Chess board[8][8],Chess thischess)
{
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			if (judgeload(i,j,board,thischess))
				return (i<<4)|j;
		}
	}
}

