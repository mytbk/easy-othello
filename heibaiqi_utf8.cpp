#include <iostream>
#include "common.h"

using namespace std;

Chess thischess=BLACK;
Chess qipan[8][8]={};
int nSteps=0; //记录步数
int nChesses[3]={2,0,2}; //双方棋子个数
char player[3]={'W',' ','B'};//加这一行的作用是为了显示轮到谁落子，否则容易忘记
char hang,lie;

void judge();//判断菜单的函数
void entergame();//游戏执行的函数

void printqizi()
{
	cout<<"黑棋 "<<nChesses[2]<<endl;
	cout<<"白棋 "<<nChesses[0]<<endl;
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

void shuruzuobiao()
{
	while (1){
		cout<<"请输入您需要落子的位置坐标：（例如 A 1），player"<<player[thischess+1]<<" ";
		cin>>hang>>lie;
		if(hang>='A'&&hang<='H'&&lie>='1'&&lie<='8')
		{
			if (judgeload(hang-'A',lie-'1',qipan,thischess))
				return;
			else {
				cout<<"当前位置不能落子，请重新输入"<<endl;
			}
		}
		else{
			cout<<"输入坐标无效，请重新输入："<<endl;
		}
	}
}

void choosecolour()
{
	int colour;
	cout<<"请输入您需要选择的棋子颜色：(黑 1 or 白 -1)";
	cin>>colour;
	if(colour==1) { thischess=BLACK;
		entergame();
	}
	else if(colour==-1)
	{thischess=WHITE;
		entergame();
	}
	else {
		cout<<"您选择的颜色有误，请重新输入：";
		choosecolour();
	}
}

void chooseorder()
{

}

void savechess()
{

}

void readchess()
{

}

void printmainmenu()
{
	cout<<"主菜单："<<endl;
	cout<<"直接进入游戏：输入 E G"<<endl;
	cout<<"选择先手后手：输入 C O"<<endl;
	cout<<"选择棋子颜色：输入 C C"<<endl;
	cout<<"当前游戏存盘：输入 S C"<<endl;
	cout<<"读取存盘游戏：输入 R C"<<endl;
	judge();
}

void entergame()
{
	printqizi();
	while(1)
	{
		if (nSteps==60){
			cout << "游戏结束" << endl;
			return;
		}
		bool canMove=false;
		for (int i=0;i<8&&!canMove;i++){ //找能下子的地方
			for (int j=0;j<8;j++){
				if (judgeload(i,j,qipan,thischess)){
					canMove=true;
					break;
				}
			}
		}
		if (canMove){
			shuruzuobiao();
			clrscr();
			int nReversed=reverse(qipan,qipan,hang-'A',lie-'1',thischess);
			nChesses[1+thischess]+=nReversed+1;
			nChesses[1-thischess]-=nReversed;
			++nSteps;
		}
		else{
			cout << "Player" << player[1+thischess] 
				<< "has no valid moves." << endl;
		}
		thischess=-thischess;
		printqizi();
	}
}

void judge()
{
	char input1,input2;
	cout<<"请输入指令：（大写字母）";
	cin>>input1>>input2;
	if(input1=='E'&&input2=='G')
		entergame();
	else if(input1=='C'&&input2=='O')
		chooseorder();
	else if(input1=='C'&&input2=='C')
		choosecolour();
	else if(input1=='S'&&input2=='C')
		savechess();
	else if(input1=='R'&&input2=='C')
		readchess();
	else {cout<<"您输入的指令有误，请重新输入：";
		judge();
	}
}

int main ()
{
	qipan[3][3]=WHITE;
	qipan[3][4]=BLACK;
	qipan[4][3]=BLACK;
	qipan[4][4]=WHITE;
	printmainmenu();
	return 0;
}

