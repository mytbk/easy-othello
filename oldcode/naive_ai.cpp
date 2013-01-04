#include "common.h"

Position naive_ai(Chess board[8][8],Chess thischess)
	//just for test
{
	Position first_move;
	get_move(board,&first_move,thischess,1);
	return first_move;
}
