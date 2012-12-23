#include "common.h"
#include "debug.h"
#include <iostream>
#include <cstdlib>

using namespace std;

#ifdef SIMPLE_AI

#define SQUARE(x) ((x)*(x))
#define INF 0x10000
const int sline[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
const int mline[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
const Chess corners[4][2]={{0,0},{0,BSIZE-1},{BSIZE-1,0},{BSIZE-1,BSIZE-1}};

int
evaluate(Chess board[8][8])
{
	int nChesses[3]={};
	int value=0;
	int values[8][8]={};

	for (int i=0;i<8;i++) //calculate chesses
		for (int j=0;j<8;j++)
			nChesses[1+board[i][j]]++;

	Position tmp;
	if (!get_move(board,&tmp,1,1)&&!get_move(board,&tmp,-1,1)) //game over
		return (nChesses[2]-nChesses[0])*INF; 

	//calculate the corner value
	int corner_value=SQUARE(nChesses[1]/5+1)+1;
	values[0][0]=values[0][BSIZE-1]
		=values[BSIZE-1][0]=values[BSIZE-1][BSIZE-1]
		=corner_value;

	for (int i=0;i<4;i++){ //set corner and points surrounding
		int cx=corners[i][0],cy=corners[i][1]; //corner(x,y)
		if (board[cx][cy]){
			for (int j=0;j<4;j++){ //search boarders
				int x=cx+sline[j][0],
					y=cy+sline[j][1];
				while (x>=0&&x<BSIZE&&y>=0&&y<BSIZE){
					if (board[x][y]==board[cx][cy])
						values[x][y]=max(corner_value/2,2);
					else{
						if (board[x][y]!=NUL&&!values[x][y])
							values[x][y]=-1;
						break;
					}
					x+=sline[j][0];
					y+=sline[j][1];
				}
			}
		}
		else{ //mark neighbers as danger
			for (int i=0;i<4;i++){
				int x=cx+mline[i][0],
					y=cy+mline[i][1];
				if (x>=0&&x<BSIZE&&y>=0&&y<BSIZE)
					values[x][y]=-corner_value*3/4;
				x=cx+sline[i][0];y=cy+sline[i][1];
				if (x>=0&&x<BSIZE&&y>=0&&y<BSIZE)
					values[x][y]=-corner_value/2;
			}
		}
	}
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			if (board[i][j]==BLACK)
				value+=values[i][j]?values[i][j]:1;
			else if (board[i][j]==WHITE)
				value-=values[i][j]?values[i][j]:1;
		}
	}

#ifdef debug
	printboard(board);
	cerr << value << endl;
#endif
	return value;
}

int 
search(Chess board[8][8], int thischess, int depth, int &x, int &y)
{
	int moveflag=0;
	__start:
	if (!depth||moveflag==2)
		return evaluate(board);

	Position list[60];
	int nMoves;
	int tx,ty;
	int bestx,besty;
	int best_value=(thischess==BLACK)?-INF:INF;
	int vmove;

	nMoves = get_move(board, list, thischess, 60);
	if (!nMoves){
		moveflag++;
		thischess=-thischess;
		goto __start;
	}else
		moveflag=0;
	if (nMoves<4)
		depth++;
#ifdef debug
	cerr << thischess << '\t' << nMoves << " moves" << endl;
#endif
	bestx=list[0]>>4;besty=list[0]&0xf;
	for (int i=0; i <nMoves ; i++){
		tx = list[i]>>4;
		ty = list[i]&0xf;
#ifdef debug
		cerr << thischess << " trying move" << tx << ty << endl;
#endif
		Chess testboard[8][8];
		reverse(board,testboard,tx,ty,thischess);
		vmove = search(testboard,-thischess,depth-1,x,y);
		if (thischess==WHITE){
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
#ifdef debug
	cerr << best_value << endl;
#endif
	return best_value;
}


Position 
simple_ai(Chess board[8][8], Chess thischess)
{
	int x,y;
	search(board,thischess,4,x,y);
	if (!judgeload(x,y,board,thischess)){
		cerr << "Trying a wrong place (" << x <<',' << y << ")!" << endl;
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
