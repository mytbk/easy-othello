#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "common.h"
#define VERSION "0.1Alpha 20121225"

using namespace std;

void judge();//判断菜单的函数
void entergame();//游戏执行的函数
void printmainmenu();//主菜单
void judgewin();//判断胜负
void exitgame();//中途停止游戏的函数

/* global variables */

Chess qipan[8][8]={};
Chess human=BLACK;
Chess thischess; //当前落子的一方
int nChesses[3]; //双方棋子个数
const char player[3]={'W',' ','B'};//加这一行的作用是为了显示轮到谁落子，否则容易忘记
int nSteps; //记录总步数
int cur_move; //当前步数
struct
{
	Chess who;
	int x,y;
	int nBlack,nWhite;
	Chess board[8][8];
}record[61]; //记录每步的信息
char hang,lie;
int pLine,pColumn; //保存行列坐标
bool normalexit=true;//标记是否是中途退出游戏

/* end of global variables */

void saveRecord() //保存棋局状态
{/*{{{*/
	record[nSteps].who = thischess; //记录当前下子的一方
	record[nSteps].x=pLine; //记录行数
	record[nSteps].y=pColumn; //记录列数
	record[nSteps].nBlack=nChesses[2];
	record[nSteps].nWhite=nChesses[0];
	memcpy(record[nSteps].board,qipan,sizeof(qipan)); //拷贝棋盘
}/*}}}*/

void game_init() //棋局初始化
{/*{{{*/
	memset(qipan,0,sizeof(qipan));
	qipan[3][3]=WHITE;
	qipan[3][4]=BLACK;
	qipan[4][3]=BLACK;
	qipan[4][4]=WHITE;
	cur_move=nSteps=0;
	nChesses[0]=nChesses[2]=2;
	thischess=BLACK;
	saveRecord();
}/*}}}*/

void put_chess(Chess put, int x, int y)
{/*{{{*/
	int nReversed=reverse(qipan,qipan,x,y,put); //翻转棋子并记录翻转棋子个数
	nChesses[1+put]+=nReversed+1; //下子一方棋子增加(包括刚下的子)
	nChesses[1-put]-=nReversed; //对方棋子减少
	++cur_move; //当前步数加1
	nSteps=cur_move; //最大步数等于当前步数
	saveRecord(); //保存状态
}/*}}}*/

void game_undo() //悔棋
{
	int p;
	for (p=cur_move;p&&record[p].who!=human;p--)
		;
	if (p==0){
		cerr << "已经是第一步！" << endl;
		return;
	}
	cur_move = p-1;
	thischess = human;
	return;
}

void game_redo() //撤销悔棋
{
	int p;
	for (p=cur_move+1;p<=nSteps&&record[p].who!=human;p++)
		;
	if (p>nSteps){
		cerr << "已经是最后一步！" << endl;
		return;
	}
	cur_move = p;
	thischess = -human;
	return;
}

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
{
	while (1){
		cout<<"请输入您需要落子的位置坐标：（例如 A 1），player"<<player[thischess+1]<<" "<<endl;;
		cout<<"返回主菜单请输入：R M"<<endl;//(return mainmenu)
		cout<<"悔棋请按UD,撤销悔棋请按RD"<<endl;
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
		}else if (hang=='U'&&lie=='D'){
			game_undo();
		}else if (hang=='R'&&lie=='D'){
			game_redo();
		}
		else{
			cout<<"输入坐标无效，请重新输入："<<endl;
		}
	}
}

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

/* 存档文件格式
 * 第一行: 人所在的一方
 * 以下各行为3个整数，依次为
 * 下棋的一方 所下的行 所下的列
 */

void savechess()
{
	char filename[1024];
	cout << "请输入存盘文件（默认为data.txt）：" ;
	cin.getline(filename,sizeof(filename)); //清空字符缓冲区
	cin.getline(filename,sizeof(filename));
	if (strlen(filename)==0)
		strcpy(filename,"data.txt");

	ofstream of(filename,ios::out);
	if(!of) return ;
	of << human << endl; //保存人类所在的一方
	for(int i=1;i<=cur_move;i++){ //将开始至当前步数都存下来
		of << record[i].who << ' ' 
			<< record[i].x << ' ' << record[i].y << endl;
	}
	of.close();
}

void readchess()
{
	char filename[1024];
	cout << "请输入存盘文件（默认为data.txt）：" ;
	cin.getline(filename,sizeof(filename));
	cin.getline(filename,sizeof(filename));
	if (strlen(filename)==0)
		strcpy(filename,"data.txt");

	ifstream infile(filename,ios::in);
	if(!infile) return ;

	//开始加载棋局
	game_init();
	infile >> human;
	while (infile>>thischess>>pLine>>pColumn)
		put_chess(thischess,pLine,pColumn);
	
	infile.close();
	thischess=human;
	entergame();
}

void exitgame()
{/*{{{*/
	char input;
	cout<<"您的确要离开游戏么？（Y or N）"<<endl;
	cin>>input;
	if(input=='Y'||input=='y')
		exit(0);
}/*}}}*/

void printmainmenu() //主界面
{
	for (;;){
		clrscr();
		cout<<"黑白棋 "<<VERSION<<endl<<endl; 
		cout<<"主菜单："<<endl;
		cout<<"1.直接进入游戏"<<endl;
		cout<<"2.继续游戏"<<endl;
		cout<<"3.选择棋子颜色"<<endl;
		cout<<"4.当前游戏存盘"<<endl;
		cout<<"5.读取存盘游戏"<<endl;
		cout<<"6.退出游戏"<<endl;
		judge();
	}
}

void judgewin()
{/*{{{*/
	if(nChesses[2]>nChesses[0])
		cout<<"黑棋胜！"<<endl;
	else if(nChesses[2]<nChesses[0])
		cout<<"白棋胜！"<<endl;
	else cout<<"平手！"<<endl;
}/*}}}*/

void entergame() //游戏
{
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
		if (get_move(qipan,&test,thischess,1)) //如果可下子
			canMove=true;

		if (canMove){
			moveflag=0;
			if (thischess!=human){
				Position pos = game_ai(qipan,thischess);
				pLine = pos>>4;
				pColumn = pos&0xf;
			}else{
				shuruzuobiao();
				if (hang=='R' && lie=='M') //遇到返回菜单的命令
					return;
				//if (
				pLine = hang-'A';
				pColumn = lie-'1';
			}
			put_chess(thischess,pLine,pColumn);
			clrscr();
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

