#include "common.h"

Position btr_ai(Chess[8][8], Chess, int);

Position game_ai(Chess board[8][8],Chess thischess,int level)
{
	return btr_ai(board,thischess,level);
}

