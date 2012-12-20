#ifndef _COMMON_H
#define _COMMON_H

/* define types and constants */

typedef int Chess;
typedef unsigned char Position;
#define BLACK 1
#define WHITE -1
#define NUL 0
#define BSIZE 8

/*end of types and constants defination*/

/*global game variables*/


/*end of global game variables*/

/*functions*/
int get_move(Chess[][BSIZE],Position*,Chess,int);
bool judgeload(int,int,Chess[][BSIZE],Chess);//判断能否落子
int reverse(Chess src[][BSIZE],Chess dest[][BSIZE],int x, int y,Chess thischess);
Position game_ai(Chess board[8][8],Chess);
extern "C" void clrscr();
#endif

