#include "common.h"

int 
get_move(Chess board[BSIZE][BSIZE],Position list[],int chess,int max)
{
	int nMoves=0;
	for (int i=0;i<BSIZE;i++){
		for (int j=0;j<BSIZE;j++){
			if (judgeload(i,j,board,chess)){
					list[nMoves++]=(i<<4)|j;
					if (nMoves==max)
						return nMoves;
			}
		}
	}
	return nMoves;
}

int 
reverse(Chess src[][BSIZE],Chess dest[][BSIZE],int x, int y,Chess thischess)
{
	if (thischess==0)
		return 0;

	int nReversed=0;
	int directions[8][2]={
		{-1,0},{-1,1},{0,1},{1,1},
		{1,0},{1,-1},{0,-1},{-1,-1}
	}; //8 directions

	for (int i=0;i<BSIZE;i++){
		for (int j=0;j<BSIZE;j++)
			dest[i][j]=src[i][j];
	} //copy the board
	dest[x][y]=thischess; //place the chess

	for (int i=0;i<8;i++){ //loop for all directions
		int xx=x,yy=y; //searching x,y
		int u,v;
		do {
			xx+=directions[i][0];
			yy+=directions[i][1];
		}while (xx>=0&&xx<8&&yy>=0&&yy<8&&src[xx][yy]==-thischess);

		if (xx<0||xx>=8||yy<0||yy>=8||src[xx][yy]==NUL)
			//out of bound
			continue;

		u=x+directions[i][0];
		v=y+directions[i][1];
		while (u!=xx||v!=yy){ //(u,v)!=(xx,yy) then continue reversing
			dest[u][v]=-dest[u][v]; //reverse
			u+=directions[i][0];
			v+=directions[i][1];
			++nReversed;
		}
	}
	return nReversed;
}

bool judgeload(int x,int y ,Chess board[][BSIZE],Chess thischess)
{
	if(board[x][y]!=NUL)
		return false;
	int directions[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
	for(int i=0;i<8;i++)
	{
		int xx=x,yy=y;
		int u,v;
		do {
			xx+=directions[i][0];
			yy+=directions[i][1];
		}while (xx>=0&&xx<8&&yy>=0&&yy<8&&board[xx][yy]==-thischess);
		if (xx<0||xx>=8||yy<0||yy>=8||board[xx][yy]==NUL)
			continue;
		u=x+directions[i][0];
		v=y+directions[i][1];
		if (u!=xx||v!=yy)
			return true;
	}
	return false;
}//在你的程序基础上修改了一下，其实还是你的思路
