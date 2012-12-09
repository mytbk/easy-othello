#ifndef _COMMON_H
#define _COMMON_H

typedef int Chess;
#define BLACK 1
#define WHITE -1
#define NUL 0

#define BSIZE 8
bool judgeload(int x,int y,Chess board[][BSIZE],Chess thischess);//判断能否落子
int reverse(Chess src[][BSIZE],Chess dest[][BSIZE],int x, int y,Chess thischess);
void clrscr();
#endif
