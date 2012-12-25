说明：
程序的函数及其功能

file : main.cpp

int main()
	主函数，程序的开始，直接调用printmainmenu()打印菜单，直至游戏退出时返回。

printmainmenu()
	主菜单，打印菜单，并等待输入

	主菜单
	1 新游戏
	2 继续游戏
	3 存盘
	4 读盘
	5 退出

	调用judge()函数

judge()
	让用户输入游戏选项，决定程序的行为。
	1 新游戏
		初始化棋盘后调用entergame()进入游戏
	2 继续游戏
		直接调用entergame()进入游戏
	
entergame()
	游戏的界面，主管程序与人的交互。
	输入有两种类型，见shuruzuobiao()函数

shuruzuobiao()
	游戏界面的输入，主要是坐标：
	1 输入的是坐标
		判断该位置可下后，把坐标信息保存，然后返回。
	2 退出游戏的命令
		直接返回

game_init()
	初始化游戏

