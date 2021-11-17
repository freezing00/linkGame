#pragma once
#ifndef _INITGRAPH_H_
#define _INITGRAPH_H_
#include "jugeBingo.h"
#include <easyx.h>
#include <conio.h>
#include <graphics.h>
#include <cstring>
#include <opencv2/opencv.hpp>


#define IMG_SIZE 43 //隔一个动物图片的宽度
#define MAX_ANIMAL_NUM 31 //总共的动物数量

using namespace std;

class Graph {
public:
	Graph();
	void initProcess();
	int returnMenu();
	void gameInit();
	void setMapSize(int mapSize);//设置地图大小
private:

	//图标的坐标左上右下
	typedef struct
	{
		int x;
		int y;
	}coordinate;

	coordinate loc_tl[17][17];//每个图标的左上坐标
	coordinate loc_br[17][17];//每个图标的右下坐标
	coordinate _match[2] = {0};

	void timeConsume();
	void gameDraw();
	int classifyHitStatus();
	void showScore(int score);
	void resetMap();
	void reunionData();
	void timeDown();
	void addTime();

	LPCWSTR convertWstringType(string text);
	wstring StoWs(const string& s);//转换字符串类型
	void makeFontStyle(int fontSize, int fontColor, int backgroundColor);//设置字体样式

	//定义变量 int  a;	
	int _mapSize = 14;	
	int _winSize;
	MOUSEMSG _mouse;
	IMAGE img_total[3];
	IMAGE _img;
	IMAGE _imgFruit[MAX_ANIMAL_NUM][2];//
	//地图
	int _map[18][18] = {0};
	bool findFlag1 = false;
	bool findFlag2 = false;
	Bingo _bingo;
	int _score = 0;
	int nowTime = 0;
	time_t start, stop;
	int _resetMap = 0;
	int durationTime;
};
#endif // !_INITGRAPH_H_
