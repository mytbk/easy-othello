#include <iostream>
#include "chars.h"
#define BLK 1
#define WHT -1

using namespace std;

const char* drawchrs[3][3]={
	{ULEFT,UCROSS,URIGHT},
	{LCROSS,CROSS,RCROSS},
	{DLEFT,DCROSS,DRIGHT}
};

void drawboard(int h,int w,int board[20][20])
{
	int i,j;
	int drwx,drwy; //which char to draw

	for (i=0;i<h;i++){
		for (j=0;j<w;j++){
			switch (board[i][j]){
				case BLK:
				cout << BLACK;
				break;

				case WHT:
				cout << WHITE;
				break;

				default:
				if (i==0)
					drwy=0;
				else if (i==h-1)
					drwy=2;
				else
					drwy=1;

				if (j==0)
					drwx=0;
				else if (j==w-1)
					drwx=2;
				else
					drwx=1;
				cout << drawchrs[drwy][drwx];
			}
		}
		cout << endl;
	}
}
