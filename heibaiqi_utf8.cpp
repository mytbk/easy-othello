#include<iostream>
#include "common.h"

using namespace std;

Chess qipan[8][8]={};
char hang,lie;

void printqizi()
{
	cout<<"    1   2   3   4   5   6   7   8  "<<endl;
	cout<<"  ╔ ═ ╦ ═ ╦ ═ ╦ ═ ╦ ═ ╦ ═ ╦ ═ ╦ ═ ╗"<<endl;

	for(int i=0;i<8;i++){
		cout << " " << char('A'+i) << "║";
		for(int j=0;j<8;j++){
			switch(qipan[i][j])
			{
				case NUL:
					cout<<"   ";
					break;
				case BLACK:
					cout<<" ● ";
					break;
				case WHITE:
					cout<<" ○ ";
					break;
			}
			cout << "║";
		}
		cout << endl;
		if (i<7)
			cout<<"  ╠ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╣"<<endl;
		else
			cout<<"  ╚ ═ ╩ ═ ╩ ═ ╩ ═ ╩ ═ ╩ ═ ╩ ═ ╩ ═ ╝"<<endl;
	}
}

/*
void printqipan()
{
	//	for(int i=0;i<8;i++)
	cout<<" A║   ║   ║   ║   ║   ║   ║   ║   ║"<<endl;
	cout<<" B║   ║   ║   ║   ║   ║   ║   ║   ║"<<endl;
	cout<<"  ╠ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╣"<<endl;
	cout<<" C║   ║   ║   ║   ║   ║   ║   ║   ║"<<endl;
	cout<<"  ╠ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╣"<<endl;
	cout<<" D║   ║   ║   ║ ● ║ ○ ║   ║   ║   ║"<<endl;
	cout<<"  ╠ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╣"<<endl;
	cout<<" E║   ║   ║   ║ ○ ║ ● ║   ║   ║   ║"<<endl;
	cout<<"  ╠ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╣"<<endl;
	cout<<" F║   ║   ║   ║   ║   ║   ║   ║   ║"<<endl;
	cout<<"  ╠ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╣"<<endl;
	cout<<" G║   ║   ║   ║   ║   ║   ║   ║   ║"<<endl;
	cout<<"  ╠ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╬ ═ ╣"<<endl;
	cout<<" H║   ║   ║   ║   ║   ║   ║   ║   ║"<<endl;
}*/

void shuruzuobiao()
{
	while (1){
		cin>>hang>>lie;
		if(hang>='A'&&hang<='H'&&lie>='1'&&lie<='8')
		{
			cout<<"zhengque"<<endl;
			return;
		}
		else{ 
			cout<<"输入坐标无效，请重新输入：";
		}
	}
}

int main ()
{
	qipan[3][3]=WHITE;
	qipan[3][4]=BLACK;
	qipan[4][3]=BLACK;
	qipan[4][4]=WHITE;
	printqizi();
	Chess thischess=BLACK;
	while (1){
		shuruzuobiao();
		clrscr();
		reverse(qipan,qipan,hang-'A',lie-'1',thischess);
		thischess=-thischess;
		printqizi();
	}
	return 0;
}

