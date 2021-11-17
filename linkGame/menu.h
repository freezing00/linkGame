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
// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")		//������
using namespace std;
using namespace cv;

#define WINDOW_NAME "linkName"
#define FILENAME_HELP "D:\\linkGame\\linkGame\\linkGame\\text\\help.txt"
#define FILENAME_RANK "D:\\linkGame\\linkGame\\linkGame\\text\\rank.txt"
#define FILENAME_SET "D:\\linkGame\\linkGame\\linkGame\\text\\set.txt"
class Menu{
public:
	Menu();
	void menuProcess(void);//�˵�����
	void setInMenu(void);//���½���˵�
	bool getQuitMenu(void);//�˳��˵�����
	bool getStart(void);//��ʼ��Ϸ
	bool getLevel(void);//�Ѷ��Ƿ��������
	int  getLevelChoice(void);//����Ѷ�
	void getMouseInfo(void);//��������Ϣ�ṹ��
	
	void openMusic(void);//������
private:

	int mouseChooseMode(void);//ͨ�����λ��ѡ��ťģʽ


	void cursorResponce(void);//�����Ӧ

	void buttonResponce(void);//��ť��Ӧ

	//���ܰ�ť
	void startGameButton(void);
	void helpButton(void);
	void rankListButton(void);
	void selectLevelButton(void);
	void setButton(void);


	LPCWSTR convertWstringType(string text);
	string readFile(string fileName);//���ļ�
	wstring StoWs(const string& s);//ת���ַ�������
	void makeFontStyle(int fontSize, int fontColor, int backgroundColor);//����������ʽ


	IMAGE _img,_start,_quit,_rank,_level,_set,_help;
	MOUSEMSG _mouse;
	RECT _rect ;
	int _levelChoice = 14;
	bool _levelSureFlag = false;
	bool _startGame = false;
};

#endif // !1


