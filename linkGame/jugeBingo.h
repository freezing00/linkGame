#pragma once
#ifndef _JUDGEBINGO_H_
#define _JUDGEBINGO_H_
#include "stack.h"


#define COORDINATE_A_X 1
#define COORDINATE_A_Y 1
#define COORDINATE_B_X 1
#define COORDINATE_B_Y 2

//��ά����ṹ�� 
typedef struct {
	dataType x;
	dataType y;
	int around;	//��Χ��� 
} coordinateStruct;




class Bingo {
public:

	dataType image[18][18] = {0};
	int _mapSize = 14;

	Bingo();

	int judgeProcess(int x1,int y1,int x2,int y2);
private:
	stackStruct* findTrail(coordinateStruct* coordinateA, coordinateStruct* coordinateB);//Ѱ��·�� 

	//��Χ��� 
	void judgeAround(coordinateStruct* coordinate);

	//��������Ƿ�Ϸ� 
	bool coordinateGood(coordinateStruct coordinate);

	//�ж��Ƿ���ͬһֱ����  
	bool sameLine(coordinateStruct* coordinateA, coordinateStruct* coordinateB);

	//�жϸ��������Ƿ���ͼ 
	bool coordinateEmpty(coordinateStruct coordinate);
	
	//��·������NULL 
	//�ж�ֱ������ 
	stackStruct* noCross(coordinateStruct* coordinateA, coordinateStruct* coordinateB);
	//���ߵ���������Ѱ�ҷ�ֱ��·�� 
	//��·������NULL 
	stackStruct* twoCrossHor(coordinateStruct* coordinateA, coordinateStruct* coordinateB);
	//ֻתһ���������Լ��ھ�����ת���������� 
	//��·������NULL 
	stackStruct* CrossAndBack(coordinateStruct* coordinateA, coordinateStruct* coordinateB);
	//�ھ����ڲ��������� 
	//��·������NULL 
	stackStruct* twoCrossInside(coordinateStruct* coordinateA, coordinateStruct* coordinateB);



	coordinateStruct coordinateA;
	coordinateStruct coordinateB;
	Stack stack;


};
#endif // !_JUDGEBINGO_H_
