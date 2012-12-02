#include "drawboard.cpp"
#include <stdlib.h>
#include <time.h>

int main()
{
	int gameboard[20][20];
	int i,j;
	int h,w;

	srand(time(0));
	h=rand()%20+1;
	w=rand()%20+1;
	cout << h << ' ' << w << endl;

	for (i=0;i<h;i++){
		for (j=0;j<w;j++){
			gameboard[i][j]=rand()%3-1;
			cout << gameboard[i][j] << ' ';
		}
		cout << endl;
	}

	drawboard(h,w,gameboard);
	return 0;
}

