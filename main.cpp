#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "common.h"

using namespace std;

void judge();//判断菜单的函数
void entergame();//游戏执行的函数
void printmainmenu();//主菜单
void judgewin();//判断胜负
void exitgame();//中途停止游戏的函数

/* global variables */

Chess human=BLACK;
Chess thischess; //当前落子的一方
Chess qipan[8][8]={0};
int nSteps; //记录步数
int nChesses[3]; //双方棋子个数
const char player[3]={'W',' ','B'};//加这一行的作用是为了显示轮到谁落子，否则容易忘记
char hang,lie;
bool normalexit=true;//标记是否是中途退出游戏
/* end of global variables */

void game_init() //棋局初始化
{/*{{{*/
	memset(qipan,0,sizeof(qipan));
	qipan[3][3]=WHITE;
	qipan[3][4]=BLACK;
	qipan[4][3]=BLACK;
	qipan[4][4]=WHITE;
	nSteps=0;
	nChesses[0]=nChesses[2]=2;
	thischess=BLACK;
}/*}}}*/

void printqizi() //打印棋盘
{/*{{{*/
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
}/*}}}*/

void shuruzuobiao() //在游戏界面处理输入
{/*{{{*/
	while (1){
		cout<<"请输入您需要落子的位置坐标：（例如 A 1），player"<<player[thischess+1]<<" "<<endl;;
		cout<<"返回主菜单请输入：R M"<<endl;//(return mainmenu)
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
}/*}}}*/

void choosecolour() //选择颜色
{/*{{{*/
	int colour;
	cout<<"请输入您需要选择的棋子颜色：(黑 1 or 白 -1)"<<endl;
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
}/*}}}*/

void savechess()
{/*{{{*/
	ofstream of("data.txt",ios::out);
		if(!of) return ;
		of << human << endl;
		for(int i=0;i<BSIZE;i++){
			for(int j=0;j<BSIZE;j++)
				of<<' '<<qipan[i][j];
			of << endl;
		}
		of.close();
}/*}}}*/

void readchess()
{/*{{{*/
	ifstream infile("data.txt",ios::in);
		if(!infile) return ;
		nChesses[0]=nChesses[2]=0;
		infile >> human;
		for(int i=0;i<BSIZE;i++)
			for(int j=0;j<BSIZE;j++){
			 infile>>qipan[i][j];
			 nChesses[qipan[i][j]+1]++;
			}
		infile.close();
		thischess=human;
		entergame();
}/*}}}*/

void exitgame()
{/*{{{*/
	char input;
	cout<<"您的确要离开游戏么？（Y or N）"<<endl;
	cin>>input;
	if(input=='Y'||input=='y')
		exit(0);
}/*}}}*/

void printmainmenu() //主界面
{/*{{{*/
	for (;;){
		clrscr();
		cout<<"主菜单："<<endl;
		cout<<"1.直接进入游戏"<<endl;
		cout<<"2.继续游戏"<<endl;
		cout<<"3.选择棋子颜色"<<endl;
		cout<<"4.当前游戏存盘"<<endl;
		cout<<"5.读取存盘游戏"<<endl;
		cout<<"6.退出游戏"<<endl;
		judge();
	}
}/*}}}*/

void judgewin()
{/*{{{*/
	if(nChesses[2]>nChesses[0])
		cout<<"黑棋胜！"<<endl;
	else if(nChesses[2]<nChesses[0])
		cout<<"白棋胜！"<<endl;
	else cout<<"平手！"<<endl;
}/*}}}*/

void entergame() //游戏
{/*{{{*/
	if(normalexit)
		printqizi();
	int moveflag=0; //记录不可移动的步数，2则游戏结束
	while(1)
	{
		if (moveflag==2||nSteps==60){
			if (normalexit) judgewin();
			cout << "游戏结束,按Enter返回主菜单。" << endl;
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
}/*}}}*/

void judge() //处理主菜单的命令
{/*{{{*/
    int  input1;
	cout<<"请输入指令:";
	cin>>input1;
	if(input1==1)
    {
		game_init();
		entergame();
	}
	else if(input1==2)
		entergame();
	else if(input1==3)
		choosecolour();
	else if(input1==4)
		savechess();
	else if(input1==5)
		readchess();
	else if(input1==6)
		exitgame();
	else {cout<<"您输入的指令有误，请重新输入：";
		judge();
	}
}/*}}}*/

int main ()
{
	printmainmenu();
	return 0;
}

