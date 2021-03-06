#ifndef _COMMON_H
#define _COMMON_H

/* define types and constants */

typedef int Chess;
typedef unsigned int Position;
#define BLACK 1
#define WHITE -1
#define NUL 0
#define BSIZE 8

/*end of types and constants defination*/


/*functions*/
int get_move(Chess[][BSIZE],Position*,Chess,int);
bool judgeload(int,int,Chess[][BSIZE],Chess);//判断能否落子
int reverse(Chess src[][BSIZE],Chess dest[][BSIZE],int x, int y,Chess thischess);
Position game_ai(Chess board[8][8],Chess,int);
extern "C" void clrscr();
#ifdef __WIN32
#include <windows.h>
#define sleep(x) Sleep(x*1000)
#else
#include <unistd.h>
#endif
/* end of functions */

/* choose AI */
#define SIMPLE_AI

#endif

