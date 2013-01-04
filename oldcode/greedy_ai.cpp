#include "common.h"

#ifdef GREEDY_AI

#include <iostream>
#include <cstdlib>
#define INF 0xffff

using namespace std;

int 
search(Chess board[8][8], int thischess, int depth, int &x, int &y)
{
	if (depth==-1)
		return 0;

	Position list[60];
	int nMoves;
	int tx,ty;
	int bestx,besty;
	int best_value=(thischess==BLACK)?-INF:INF;
	int vmove;

	nMoves = get_move(board, list, thischess, 60);
	if (!nMoves){
		return (board,-thischess,depth-1,x,y);
	}
	//cerr << thischess << '\t' << nMoves << " moves" << endl;
	for (int i=0; i <nMoves ; i++){
		tx = list[i]>>4;
		ty = list[i]&0xf;
		//cerr << thischess << " trying move" << tx << ty << endl;
		Chess testboard[8][8];
		int nReversed=reverse(board,testboard,tx,ty,thischess);
		vmove = nReversed-search(testboard,-thischess,depth-1,x,y);
		if (thischess==WHITE){
			vmove=-vmove;
			if (vmove<best_value){
				bestx=tx;besty=ty;
				best_value=vmove;
			}
		}else{
			if (vmove>best_value){
				bestx=tx;besty=ty;
				best_value=vmove;
			}
		}
	}
	x=bestx;y=besty;
	return best_value;
}


Position 
greedy_ai(Chess board[8][8], Chess thischess)
{
	int x,y;
	search(board,thischess,3,x,y);
	if (!judgeload(x,y,board,thischess)){
		cerr << "Trying a wrong place!" << endl;
		system 
#ifdef linux
		("read");
#else
		("pause");
#endif
	}
	return (x<<4)|y;
}

#endif
