#ifndef _MENU_H__
#define _MENU_H__
#pragma once
#include<iostream>
#include <fstream>
#include <cstring>
#include "include/opencv2/opencv.hpp"
#include <easyx.h>
#include <conio.h>
#include <graphics.h>
// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")		//不能少
using namespace std;
using namespace cv;

#define WINDOW_NAME "linkName"
#define FILENAME_HELP "D:\\linkGame\\linkGame\\linkGame\\text\\help.txt"
#define FILENAME_RANK "D:\\linkGame\\linkGame\\linkGame\\text\\rank.txt"
#define FILENAME_SET "D:\\linkGame\\linkGame\\linkGame\\text\\set.txt"
class Menu{
public:
	Menu();
	void menuProcess(void);//菜单流程
	void setInMenu(void);//重新进入菜单
	bool getQuitMenu(void);//退出菜单界面
	bool getStart(void);//开始游戏
	bool getLevel(void);//难度是否设置完成
	int  getLevelChoice(void);//获得难度
	void getMouseInfo(void);//获得鼠标信息结构体
	
	void openMusic(void);//打开音乐
private:

	int mouseChooseMode(void);//通过鼠标位置选择按钮模式


	void cursorResponce(void);//光标响应

	void buttonResponce(void);//按钮响应

	//功能按钮
	void startGameButton(void);
	void helpButton(void);
	void rankListButton(void);
	void selectLevelButton(void);
	void setButton(void);


	LPCWSTR convertWstringType(string text);
	string readFile(string fileName);//读文件
	wstring StoWs(const string& s);//转换字符串类型
	void makeFontStyle(int fontSize, int fontColor, int backgroundColor);//设置字体样式


	IMAGE _img,_start,_quit,_rank,_level,_set,_help;
	MOUSEMSG _mouse;
	RECT _rect ;
	int _levelChoice = 14;
	bool _levelSureFlag = false;
	bool _startGame = false;
};

#endif // !1


