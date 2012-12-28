#include "common.h"

/* list of AI */
Position naive_ai(Chess[][8],Chess);
int greedy_ai(Chess[][8],Chess);
int simple_ai(Chess[][8],Chess,int);
/* end of AI list */

#ifdef NAIVE_AI 
Position naive_ai(Chess board[8][8],Chess thischess)
	//just for test
{
	Position first_move;
	get_move(board,&first_move,thischess,1);
}
#endif

Position game_ai(Chess board[8][8],Chess thischess,int level)
{
	return simple_ai(board,thischess,level);
}

