#include <iostream>
#include <cstdlib>
#include <cstring>
#include "common.h"

using namespace std;

void judge();//判断菜单的函数
void entergame();//游戏执行的函数
void printmainmenu();

/* global variables */

Chess human=BLACK;
Chess thischess; //当前落子的一方
Chess qipan[8][8];
int nSteps; //记录步数
int nChesses[3]; //双方棋子个数
const char player[3]={'W',' ','B'};//加这一行的作用是为了显示轮到谁落子，否则容易忘记
char hang,lie;

/* end of global variables */

void game_init() //棋局初始化
{
	memset(qipan,0,sizeof(qipan));
	qipan[3][3]=BLACK;
	qipan[3][4]=WHITE;
	qipan[4][3]=WHITE;
	qipan[4][4]=BLACK;
	nSteps=0;
	nChesses[0]=nChesses[2]=2;
	thischess=BLACK;
}

void printqizi() //打印棋盘
{
	cout<<"黑棋 ●  "<<nChesses[2]<<endl;
	cout<<"白棋 ○  "<<nChesses[0]<<endl;
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

void shuruzuobiao() //在游戏界面处理输入
{
	while (1){
		cout<<"请输入您需要落子的位置坐标：（例如 A 1），player"<<player[thischess+1]<<" "<<endl;;
		cout<<"返回主菜单请输入：R M"<<endl;
		cin>>hang>>lie;
		if(((hang>='A'&&hang<='H')||(hang>='a'&&hang<='h'))&&lie>='1'&&lie<='8')
		{
			hang&=0xdf;
			if (judgeload(hang-'A',lie-'1',qipan,thischess))
				return;
			else {
				cout<<"当前位置不能落子，请重新输入"<<endl;
			}
		}else if(hang=='R'&&lie=='M'){
			return;
		}
		else{
			cout<<"输入坐标无效，请重新输入："<<endl;
		}
	}
}

void choosecolour() //选择颜色
{
	int colour;
	cout<<"请输入您需要选择的棋子颜色：(黑 1 or 白 -1)";
	cin>>colour;
	if(colour==1||colour==-1) { 
		human=colour;
		game_init();
		entergame();
	}
	else {
		cout<<"您选择的颜色有误，请重新输入：";
		choosecolour();
	}
}


void savechess()
{

}

void readchess()
{

}

void printmainmenu() //主界面
{
	for (;;){
		clrscr();
		cout<<"主菜单："<<endl;
		cout<<"直接进入游戏：输入 E G"<<endl;
		cout<<"继续游戏：输入 C O"<<endl;
		cout<<"选择棋子颜色：输入 C C"<<endl;
		cout<<"当前游戏存盘：输入 S C"<<endl;
		cout<<"读取存盘游戏：输入 R C"<<endl;
		judge();
	}
}

void entergame() //游戏
{
	printqizi();
	int moveflag=0; //记录不可移动的步数，2则游戏结束
	while(1)
	{
		if (moveflag==2||nSteps==60){
			cout << "游戏结束。按Enter返回主菜单。" << endl;
			char buf[8];
			cin.getline(buf,8);
			cin.getline(buf,8);
			return;
		}
		bool canMove=false;
		Position test; //一个可下子的点
		if (get_move(qipan,&test,thischess,1))
			canMove=true;

		if (canMove){
			moveflag=0;
			int nReversed;
			if (thischess!=human){
				Position pos = game_ai(qipan,thischess);
				nReversed = reverse(qipan,qipan,pos>>4,pos&0xf,thischess);
			}else{
				shuruzuobiao();
				if (hang=='R' && lie=='M') //遇到返回菜单的命令
					return;
				nReversed=reverse(qipan,qipan,hang-'A',lie-'1',thischess);
			}
			clrscr();
			nChesses[1+thischess]+=nReversed+1;
			nChesses[1-thischess]-=nReversed;
			++nSteps;
		}
		else{
			++moveflag; //the player has no place to move
			cout << "Player" << player[1+thischess] 
				<< " has no valid moves." << endl;
		}
		thischess=-thischess;
		printqizi();
	}
}

void judge() //处理主菜单的命令
{
	char input1,input2;
	cout<<"请输入指令：（大写字母）";
	cin>>input1>>input2;
	if(input1=='E'&&input2=='G'){
		game_init();
		entergame();
	}
	else if(input1=='C'&&input2=='O')
		entergame();//chooseorder();
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
	printmainmenu();
	return 0;
}

