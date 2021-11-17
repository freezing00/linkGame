#pragma once
#ifndef _STACK_H_
#define _STACK_H_
#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include<iostream>
using namespace  std;

typedef int dataType;
//栈结构体 
typedef struct {
	int maxNum;
	int nowNum;
	dataType* data;
} stackStruct;

//方向枚举类型 
typedef enum {
	NONE_E = 0x00,
	LEFT_E = 0x01,
	RIGHT_E = 0x02,
	UP_E = 0x04,
	DOWN_E = 0x08,
} direction_e;

class Stack {
public:
	Stack();
	stackStruct* createStack(int maxNum);
	bool stackIsEmpty(stackStruct* ptr);
	bool stackIsFull(stackStruct* ptr);
	bool stackPush(stackStruct* ptr, dataType data);
	dataType stackPop(stackStruct* ptr);
	dataType stackTop(stackStruct* ptr);
	void stackPrint(stackStruct* ptr);
	bool stackDestory(stackStruct* ptr);

};

#endif // !_STACK_H_
