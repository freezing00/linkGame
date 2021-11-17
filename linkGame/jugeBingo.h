#pragma once
#ifndef _JUDGEBINGO_H_
#define _JUDGEBINGO_H_
#include "stack.h"


#define COORDINATE_A_X 1
#define COORDINATE_A_Y 1
#define COORDINATE_B_X 1
#define COORDINATE_B_Y 2

//二维坐标结构体 
typedef struct {
	dataType x;
	dataType y;
	int around;	//包围情况 
} coordinateStruct;




class Bingo {
public:

	dataType image[18][18] = {0};
	int _mapSize = 14;

	Bingo();

	int judgeProcess(int x1,int y1,int x2,int y2);
private:
	stackStruct* findTrail(coordinateStruct* coordinateA, coordinateStruct* coordinateB);//寻找路径 

	//包围检测 
	void judgeAround(coordinateStruct* coordinate);

	//检测坐标是否合法 
	bool coordinateGood(coordinateStruct coordinate);

	//判断是否在同一直线上  
	bool sameLine(coordinateStruct* coordinateA, coordinateStruct* coordinateB);

	//判断该坐标上是否有图 
	bool coordinateEmpty(coordinateStruct coordinate);
	
	//无路径返回NULL 
	//判断直线连接 
	stackStruct* noCross(coordinateStruct* coordinateA, coordinateStruct* coordinateB);
	//共线的两个坐标寻找非直连路径 
	//无路径返回NULL 
	stackStruct* twoCrossHor(coordinateStruct* coordinateA, coordinateStruct* coordinateB);
	//只转一个弯的情况以及在矩形外转两个弯的情况 
	//无路径返回NULL 
	stackStruct* CrossAndBack(coordinateStruct* coordinateA, coordinateStruct* coordinateB);
	//在矩形内部拐两次弯 
	//无路径返回NULL 
	stackStruct* twoCrossInside(coordinateStruct* coordinateA, coordinateStruct* coordinateB);



	coordinateStruct coordinateA;
	coordinateStruct coordinateB;
	Stack stack;


};
#endif // !_JUDGEBINGO_H_
