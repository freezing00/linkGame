#include "jugeBingo.h"



Bingo::Bingo(){

}
//边界一圈恒为0 
//X轴向右为正 Y轴向下为正 

//包围检测 
void Bingo::judgeAround(coordinateStruct *coordinate) {
	
	//坐标出错 
	if(coordinate->x == 0 || coordinate->y == 0 || coordinate->x == _mapSize+2 || coordinate->y == _mapSize+2) {
		printf("\n coordinate error! \n");
		coordinate->around = NONE_E;
		return;
	}
	
	int result = NONE_E;
	if(image[coordinate->y][coordinate->x - 1] == 0) result += LEFT_E;
	if(image[coordinate->y][coordinate->x + 1] == 0) result += RIGHT_E;
	if(image[coordinate->y - 1][coordinate->x] == 0) result += UP_E;
	if(image[coordinate->y + 1][coordinate->x] == 0) result += DOWN_E;
	
	coordinate->around = result;
}

//检测坐标是否合法 
bool Bingo::coordinateGood(coordinateStruct coordinate) {
	if(coordinate.x > 0 && coordinate.x < _mapSize+2 && coordinate.y > 0 && coordinate.y < _mapSize+2) {
		return true;
	}
	else {
		return false;
	}
}

//判断是否在同一直线上  
bool Bingo::sameLine(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	if(coordinateA->x == coordinateB->x || coordinateA->y == coordinateB->y) {
		return true;
	}
	else {
		return false;
	}
}

//判断该坐标上是否有图 
bool Bingo::coordinateEmpty(coordinateStruct coordinate) {
	if(image[coordinate.y][coordinate.x] != 0) {
		return false;
	}
	else {
		return true;
	}
}

//无路径返回NULL 
//判断直线连接 
stackStruct * Bingo::noCross(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	stackStruct *ptrRoad = NULL;
	
	int distence = 0;
	if(coordinateA->x == coordinateB->x) distence = fabs(coordinateB->y - coordinateA->y);
	else	distence = fabs(coordinateB->x - coordinateA->x);	
	
	//初始化路径栈 
	ptrRoad = (stackStruct*)malloc(sizeof(stackStruct));
	ptrRoad = stack.createStack(distence);
	
	//向右遍历 
	if(coordinateB->x > coordinateA->x) {
		
		int tempCoordinateX = coordinateA->x;
		//向右遍历 
		while (tempCoordinateX != coordinateB->x) {
			
			//路径不通 
			if(image[coordinateA->y][tempCoordinateX] != 0 && tempCoordinateX != coordinateA->x) {
				stack.stackDestory(ptrRoad);
				ptrRoad = NULL;
				break;
			}			
			tempCoordinateX++;	
			stack.stackPush(ptrRoad, RIGHT_E);
		}
		
	}
	//向左遍历 
	else if(coordinateB->x < coordinateA->x) {
		
		int tempCoordinateX = coordinateA->x;
		//向左遍历 
		while (tempCoordinateX != coordinateB->x) {
			
			//路径不通 
			if(image[coordinateA->y][tempCoordinateX] != 0 && tempCoordinateX != coordinateA->x) {
				stack.stackDestory(ptrRoad);
				ptrRoad = NULL;
				break;				
			}			
			stack.stackPush(ptrRoad, LEFT_E);
			tempCoordinateX--;				
		}	

	}
	//向上遍历 
	else if(coordinateB->y < coordinateA->y) {
		
		int tempCoordinateY = coordinateA->y;
		//向上遍历 
		while (tempCoordinateY != coordinateB->y) {
			
			//路径不通 
			if(image[tempCoordinateY][coordinateA->x] != 0 && tempCoordinateY != coordinateA->y) {
				stack.stackDestory(ptrRoad);
				ptrRoad = NULL;
				break;
			}			
			stack.stackPush(ptrRoad, UP_E);
			tempCoordinateY--;				
		}			

	}
	//向下遍历 
	else if(coordinateB->y > coordinateA->y) {
		
		int tempCoordinateY = coordinateA->y;
		//向下遍历 
		while (tempCoordinateY != coordinateB->y) {
			
			//路径不通 
			if(image[tempCoordinateY][coordinateA->x] != 0 && tempCoordinateY != coordinateA->y) {
				stack.stackDestory(ptrRoad);
				ptrRoad = NULL;
				break;					
			}				
			stack.stackPush(ptrRoad, DOWN_E);
			tempCoordinateY++;				
		}	
					
	}		
	
	if(stack.stackIsEmpty(ptrRoad)) {
		//没有找到路径，销栈并返回NULL 
		stack.stackDestory(ptrRoad);
		return NULL;
	}
	else {
		return ptrRoad;	
	}
}

//共线的两个坐标寻找非直连路径 
//无路径返回NULL 
stackStruct * Bingo::twoCrossHor(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	stackStruct *ptrRoad = NULL;
	
	int distenceX = 0;	//无视阻挡的最短路径 
	int distenceY = 0;
	if(coordinateA->x == coordinateB->x) {
		distenceY = fabs(coordinateB->y - coordinateA->y);
	}
	else {
		distenceX = fabs(coordinateB->x - coordinateA->x);
	}
	
	//初始化路径栈 
	ptrRoad = (stackStruct*)malloc(sizeof(stackStruct));
	ptrRoad = stack.createStack(distenceX + distenceY + _mapSize+1);
	
	stackStruct* straightRoad = NULL;

	//Y共线 
	if(distenceX == 0) {
		//左侧开口 
		if(coordinateA->around&LEFT_E && coordinateB->around&LEFT_E) {
			
			//向左移动 
			for(int i = 0; i < coordinateA->x; i++) {
				
				stack.stackPush(ptrRoad, LEFT_E);
				
				coordinateStruct coordinateTempA = *coordinateA;
				coordinateStruct coordinateTempB = *coordinateB;
				
				//寻找坐标之间的直线连接 
				coordinateTempA.x -= i + 1;
				coordinateTempB.x -= i + 1;

				if (!coordinateEmpty(coordinateTempA) || !coordinateEmpty(coordinateTempB)) {
					break;
				}
				
				judgeAround(&coordinateTempA);
				judgeAround(&coordinateTempB);
				straightRoad = noCross(&coordinateTempA, &coordinateTempB);
					
				//寻找到了路径	
				if(straightRoad != NULL) {
					for(int j = 0; j < straightRoad->nowNum; j++) {
						//将直路栈中的数据压入完整路径栈 
						stack.stackPush(ptrRoad, straightRoad->data[j]);
					}
					stack.stackPush(ptrRoad, RIGHT_E);
					break;	//找到了最短路径，直接跳出循环 
				}
				
			}
			
		}
		//左侧开口失败，尝试向右开口 
		if(stack.stackIsEmpty(ptrRoad)) {
			if(coordinateA->around&RIGHT_E && coordinateB->around&RIGHT_E) {
			
				//向右移动 
				for(int i = 0; i < _mapSize + 1 - coordinateA->x; i++) {
					
					stack.stackPush(ptrRoad, RIGHT_E);
					
					coordinateStruct coordinateTempA = *coordinateA;
					coordinateStruct coordinateTempB = *coordinateB;
					
					//寻找坐标之间的直线连接 
					coordinateTempA.x += i + 1;
					coordinateTempB.x += i + 1;

					if (!coordinateEmpty(coordinateTempA) || !coordinateEmpty(coordinateTempB)) {
						break;
					}
					
					judgeAround(&coordinateTempA);
					judgeAround(&coordinateTempB);
					straightRoad = noCross(&coordinateTempA, &coordinateTempB);
						
					//寻找到了路径	
					if(straightRoad != NULL) {
						for(int j = 0; j < straightRoad->nowNum; j++) {
							//将直路栈中的数据压入完整路径栈 
							stack.stackPush(ptrRoad, straightRoad->data[j]);
						}
						stack.stackPush(ptrRoad, LEFT_E);
						break;	//找到了最短路径，直接跳出循环 
					}
					
				}
										
			}
		}
		
	}
	//X共线 
	else {
		//上侧开口 
		if(coordinateA->around&UP_E && coordinateB->around&UP_E) {
			
			//向上移动 
			for(int i = 0; i < coordinateA->y; i++) {
				
				stack.stackPush(ptrRoad, UP_E);
				
				coordinateStruct coordinateTempA = *coordinateA;
				coordinateStruct coordinateTempB = *coordinateB;
				
				//寻找坐标之间的直线连接 
				coordinateTempA.y -= i + 1;
				coordinateTempB.y -= i + 1;

				if (!coordinateEmpty(coordinateTempA) || !coordinateEmpty(coordinateTempB)) {
					break;
				}
				
				judgeAround(&coordinateTempA);
				judgeAround(&coordinateTempB);
				straightRoad = noCross(&coordinateTempA, &coordinateTempB);
					
				//寻找到了路径	
				if(straightRoad != NULL) {
					for(int j = 0; j < straightRoad->nowNum; j++) {
						//将直路栈中的数据压入完整路径栈 
						stack.stackPush(ptrRoad, straightRoad->data[j]);
					}
					stack.stackPush(ptrRoad, DOWN_E);
					break;	//找到了最短路径，直接跳出循环 
				}
				
			}
			
		}
		//上侧开口失败，尝试向下开口 
		if(stack.stackIsEmpty(ptrRoad)) {
			if(coordinateA->around&DOWN_E && coordinateB->around&DOWN_E) {
			
				//向下移动 
				for(int i = 0; i < _mapSize - coordinateA->y; i++) {
					
					stack.stackPush(ptrRoad, DOWN_E);
					
					coordinateStruct coordinateTempA = *coordinateA;
					coordinateStruct coordinateTempB = *coordinateB;
					
					//寻找坐标之间的直线连接 
					coordinateTempA.y += i + 1;
					coordinateTempB.y += i + 1;

					if (!coordinateEmpty(coordinateTempA) || !coordinateEmpty(coordinateTempB)) {
						break;
					}
					
					judgeAround(&coordinateTempA);
					judgeAround(&coordinateTempB);
					straightRoad = noCross(&coordinateTempA, &coordinateTempB);
						
					//寻找到了路径	
					if(straightRoad != NULL) {
						for(int j = 0; j < straightRoad->nowNum; j++) {
							//将直路栈中的数据压入完整路径栈 
							stack.stackPush(ptrRoad, straightRoad->data[j]);
						}
						stack.stackPush(ptrRoad, UP_E);
						break;	//找到了最短路径，直接跳出循环 
					}
					
				}
										
			}
		}		
	}
	
	if(stack.stackIsEmpty(straightRoad)) {
		//没有找到路径，销栈并返回NULL 
		stack.stackDestory(ptrRoad);
		return NULL;
	}
	else {
		return ptrRoad;	
	}
}

//只转一个弯的情况以及在矩形外转两个弯的情况 
//无路径返回NULL 
stackStruct * Bingo::CrossAndBack(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	stackStruct *ptrRoad = NULL;
	
	int distenceX = 0;	//无视阻挡的最短路径 
	int distenceY = 0;
	
	distenceX = fabs(coordinateB->x - coordinateA->x);
	distenceY = fabs(coordinateB->y - coordinateA->y);
	
	//初始化路径栈 
	ptrRoad = (stackStruct*)malloc(sizeof(stackStruct));
	ptrRoad = stack.createStack(3*(_mapSize+1));
	 
	coordinateStruct coordinateTempA = *coordinateA;
	coordinateStruct coordinateTempB = *coordinateB;	
	coordinateStruct coordinateMid[2];
	//第一个中继坐标 
	coordinateMid[0].x = coordinateTempB.x;
	coordinateMid[0].y = coordinateTempA.y;
	//第二个中继坐标 
	coordinateMid[1].x = coordinateTempA.x;
	coordinateMid[1].y = coordinateTempB.y;
	
	/*
	printf("coordinateA x: %d y:%d \n",coordinateA->x, coordinateA->y);	
	printf("coordinateB x: %d y:%d \n",coordinateB->x, coordinateB->y);		
	
	printf("coordinateMid[0] x: %d y:%d \n",coordinateMid[0].x,coordinateMid[0].y);	
	printf("coordinateMid[1] x: %d y:%d \n",coordinateMid[1].x,coordinateMid[1].y);	
	*/
	
	//判断坐标包围 
	judgeAround(&coordinateTempA);
	judgeAround(&coordinateTempB);
	judgeAround(&coordinateMid[0]);
	judgeAround(&coordinateMid[1]);
	
	//前进方向
	int dirX = 0;
	int dirY = 0;
	if(coordinateB->x - coordinateA->x > 0) {
		dirX = 1;
	}
	else {
		dirX = -1;
	}
	if(coordinateB->y - coordinateA->y > 0) {
		dirY = 1;
	}
	else {
		dirY = -1;
	}	
	
	stackStruct *straightRoadFirst[2] = {NULL, NULL};
	stackStruct *straightRoadSecond[2] = {NULL, NULL};
	//第一段路径 
	for(int i = 0; i < 2; i++) {
		straightRoadFirst[i] = noCross(&coordinateTempA, &coordinateMid[i]);
	}
	//第二段路径 
	for(int i = 0; i < 2; i++) {
		straightRoadSecond[i] = noCross(&coordinateMid[i], &coordinateTempB);
	}	
	
	//检验中继点一路径是否通 
	if(straightRoadFirst[0] != NULL && coordinateEmpty(coordinateMid[0])) {
		if(straightRoadSecond[0] != NULL) {
			for(int i = 0; i < straightRoadFirst[0]->nowNum; i++) {
				stack.stackPush(ptrRoad, straightRoadFirst[0]->data[i]);
			}
			for(int i = 0; i < straightRoadSecond[0]->nowNum; i++) {
				stack.stackPush(ptrRoad, straightRoadSecond[0]->data[i]);
			}			
		}
		else {
			
		}
	}
	//检验中继点二路径是否通 
	if(stack.stackIsEmpty(ptrRoad)) {
		if(straightRoadFirst[1] != NULL && coordinateEmpty(coordinateMid[1])) {
			if(straightRoadSecond[1] != NULL) {
				for(int i = 0; i < straightRoadFirst[1]->nowNum; i++) {
					stack.stackPush(ptrRoad, straightRoadFirst[1]->data[i]);
				}
				for(int i = 0; i < straightRoadSecond[1]->nowNum; i++) {
					stack.stackPush(ptrRoad, straightRoadSecond[1]->data[i]);
				}					
			}
			else {
				
			}		
		}
	}	

	//没有找到路径，进行矩形外绕路 
	if(stack.stackIsEmpty(ptrRoad)) {
		
		//全线封锁，无路径  
		if(straightRoadFirst[0] == NULL && straightRoadFirst[1] == NULL \
			&& straightRoadSecond[0] == NULL && straightRoadSecond[1] == NULL) {
				
		}
		else {
			
			coordinateStruct coordinateCross[2];	//转角处坐标 
			stackStruct *crossRoad[3] = {NULL, NULL, NULL};				//记录三条转弯路径 
			
			//检验路径一 
			//若中继坐标被占用，无解 
			if(coordinateEmpty(coordinateMid[0])) {			
								
				//该路径中的两个路段只可能有一个连通 
				if(straightRoadFirst[0] != NULL) {
					
					//拐点 
					coordinateCross[0] = coordinateMid[0];	
					coordinateCross[0].x += dirX;
					coordinateCross[1] = coordinateCross[0];
					coordinateCross[1].y += dirY*distenceY;						
					
					//拐点坐标合法且空 
					while(coordinateGood(coordinateCross[0]) && coordinateGood(coordinateCross[1]) && \
						  coordinateEmpty(coordinateCross[0]) && coordinateEmpty(coordinateCross[1])) {
						
						//获得三条岔路 
						crossRoad[0] = noCross(&coordinateMid[0], &coordinateCross[0]);
						crossRoad[1] = noCross(&coordinateCross[0], &coordinateCross[1]);
						crossRoad[2] = noCross(&coordinateCross[1], coordinateB);
						
						//存在通路 
						if(crossRoad[0] != NULL && crossRoad[1] != NULL && crossRoad[2] != NULL) {
							
							//将连通路段入栈，测试绕过非连通路段 
							for(int i = 0; i < straightRoadFirst[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, straightRoadFirst[0]->data[i]);
							}							
							
							//三条岔路入栈 
							for(int i = 0; i < crossRoad[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[0]->data[i]);
							}
							for(int i = 0; i < crossRoad[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[1]->data[i]);
							}							
							for(int i = 0; i < crossRoad[2]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[2]->data[i]);
							}
							break;	//跳出循环							
						}
						//不存在 
						else {
							//指针置空，供下次使用 
							crossRoad[0] = NULL;
							crossRoad[1] = NULL;
							crossRoad[2] = NULL;
						}
						
						//遍历下一组拐点坐标 
						coordinateCross[0].x += dirX;
						coordinateCross[1].x += dirX;
					}
					
				}
				 
				if(straightRoadSecond[0] != NULL) {
					
					//拐点 
					coordinateCross[0] = *coordinateA;	
					coordinateCross[0].y -= dirY;
					coordinateCross[1] = coordinateCross[0];
					coordinateCross[1].x += dirX*distenceX;						
					
					//拐点坐标合法且空 
					while(coordinateGood(coordinateCross[0]) && coordinateGood(coordinateCross[1]) && \
						  coordinateEmpty(coordinateCross[0]) && coordinateEmpty(coordinateCross[1])) {
						
						//获得三条岔路 
						crossRoad[0] = noCross(coordinateA, &coordinateCross[0]);
						crossRoad[1] = noCross(&coordinateCross[0], &coordinateCross[1]);
						crossRoad[2] = noCross(&coordinateCross[1], &coordinateMid[0]);
						
						//存在通路 
						if(crossRoad[0] != NULL && crossRoad[1] != NULL && crossRoad[2] != NULL) {						
							
							//三条岔路入栈 
							for(int i = 0; i < crossRoad[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[0]->data[i]);
							}
							for(int i = 0; i < crossRoad[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[1]->data[i]);
							}							
							for(int i = 0; i < crossRoad[2]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[2]->data[i]);
							}
							
							//将连通路段入栈
							for(int i = 0; i < straightRoadSecond[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, straightRoadSecond[0]->data[i]);
							}								
							
							break;	//跳出循环							
						}
						//不存在 
						else {
							//指针置空，供下次使用 
							crossRoad[0] = NULL;
							crossRoad[1] = NULL;
							crossRoad[2] = NULL;
						}
						
						//遍历下一组拐点坐标 
						coordinateCross[0].y += dirY;
						coordinateCross[1].y += dirY;
					}
										
				}				
			}
			
			//检验路径二
			//若中继坐标被占用，无解 
			if(coordinateEmpty(coordinateMid[1]) && stack.stackIsEmpty(ptrRoad)) {
								
				//该路径中的两个路段只可能有一个连通 
				if(straightRoadFirst[1] != NULL) {
					
					//拐点 
					coordinateCross[0] = coordinateMid[1];	
					coordinateCross[0].y += dirY;
					coordinateCross[1] = coordinateCross[0];
					coordinateCross[1].x += dirX*distenceX;						
					
					//拐点坐标合法且空 
					while(coordinateGood(coordinateCross[0]) && coordinateGood(coordinateCross[1]) && \
						  coordinateEmpty(coordinateCross[0]) && coordinateEmpty(coordinateCross[1])) {
						
						//获得三条岔路 
						crossRoad[0] = noCross(&coordinateMid[1], &coordinateCross[0]);
						crossRoad[1] = noCross(&coordinateCross[0], &coordinateCross[1]);
						crossRoad[2] = noCross(&coordinateCross[1], coordinateB);
						
						//存在通路 
						if(crossRoad[0] != NULL && crossRoad[1] != NULL && crossRoad[2] != NULL) {
							
							//将连通路段入栈，测试绕过非连通路段 
							for(int i = 0; i < straightRoadFirst[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, straightRoadFirst[1]->data[i]);
							}							
							
							//三条岔路入栈 
							for(int i = 0; i < crossRoad[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[0]->data[i]);
							}
							for(int i = 0; i < crossRoad[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[1]->data[i]);
							}							
							for(int i = 0; i < crossRoad[2]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[2]->data[i]);
							}
							break;	//跳出循环							
						}
						//不存在 
						else {
							//指针置空，供下次使用 
							crossRoad[0] = NULL;
							crossRoad[1] = NULL;
							crossRoad[2] = NULL;
						}
						
						//遍历下一组拐点坐标 
						coordinateCross[0].y += dirY;
						coordinateCross[1].y += dirY;
					}
					
				}
				 
				if(straightRoadSecond[1] != NULL) {
					
					//拐点 
					coordinateCross[0] = *coordinateA;	
					coordinateCross[0].x -= dirX;
					coordinateCross[1] = coordinateCross[0];
					coordinateCross[1].y += dirY*distenceY;						
					
					//拐点坐标合法且空 
					while(coordinateGood(coordinateCross[0]) && coordinateGood(coordinateCross[1]) && \
						  coordinateEmpty(coordinateCross[0]) && coordinateEmpty(coordinateCross[1])) {
						
						//获得三条岔路 
						crossRoad[0] = noCross(coordinateA, &coordinateCross[0]);
						crossRoad[1] = noCross(&coordinateCross[0], &coordinateCross[1]);
						crossRoad[2] = noCross(&coordinateCross[1], &coordinateMid[1]);
						
						//存在通路 
						if(crossRoad[0] != NULL && crossRoad[1] != NULL && crossRoad[2] != NULL) {						
							
							//三条岔路入栈 
							for(int i = 0; i < crossRoad[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[0]->data[i]);
							}
							for(int i = 0; i < crossRoad[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[1]->data[i]);
							}							
							for(int i = 0; i < crossRoad[2]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[2]->data[i]);
							}
							
							//将连通路段入栈
							for(int i = 0; i < straightRoadSecond[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, straightRoadSecond[1]->data[i]);
							}								
							
							break;	//跳出循环							
						}
						//不存在 
						else {
							//指针置空，供下次使用 
							crossRoad[0] = NULL;
							crossRoad[1] = NULL;
							crossRoad[2] = NULL;
						}
						
						//遍历下一组拐点坐标 
						coordinateCross[0].x -= dirX;
						coordinateCross[1].x -= dirX;
					}
										
				}					
			}			
			
		}
		
	}

	stack.stackDestory(straightRoadFirst[0]);
	stack.stackDestory(straightRoadFirst[1]);
	stack.stackDestory(straightRoadSecond[0]);
	stack.stackDestory(straightRoadSecond[1]);

	if(stack.stackIsEmpty(ptrRoad)) {
		//没有找到路径，销栈并返回NULL 
		stack.stackDestory(ptrRoad);
		return NULL;
	}
	else {
		return ptrRoad;	
	}
}

//在矩形内部拐两次弯 
//无路径返回NULL 
stackStruct * Bingo::twoCrossInside(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	stackStruct *ptrRoad = NULL;
	
	int distenceX = 0;	//无视阻挡的最短路径 
	int distenceY = 0;
	
	distenceX = fabs(coordinateB->x - coordinateA->x);
	distenceY = fabs(coordinateB->y - coordinateA->y);
	
	//初始化路径栈 
	ptrRoad = (stackStruct*)malloc(sizeof(stackStruct));
	ptrRoad = stack.createStack(distenceX + distenceY);
	 
	coordinateStruct coordinateTempA = *coordinateA;
	coordinateStruct coordinateTempB = *coordinateB;	
	coordinateStruct coordinateTemp = *coordinateA;
	
	/*
	printf("coordinateA x: %d y:%d \n",coordinateA->x, coordinateA->y);	
	printf("coordinateB x: %d y:%d \n",coordinateB->x, coordinateB->y);		
	*/
	
	//判断坐标包围 
	judgeAround(&coordinateTempA);
	judgeAround(&coordinateTempB);
	
	//前进方向记录 
	int dirX = 0;
	int dirY = 0;
	direction_e dirXE = NONE_E;
	direction_e dirYE = NONE_E;
	if(coordinateB->x - coordinateA->x > 0) {
		dirX = 1;
		dirXE = RIGHT_E;
	}
	else {
		dirX = -1;
		dirXE = LEFT_E;
	}
	if(coordinateB->y - coordinateA->y > 0) {
		dirY = 1;
		dirYE = DOWN_E;
	}
	else {
		dirY = -1;
		dirYE = UP_E;
	}
	
	stackStruct *straightRoad = NULL;
	
	//路径一 
	//先移动X
	if(coordinateTempA.around&dirXE) {
		
		//首先移动X	 
		for(int i = 1; i < distenceX; i++) {
			
			//初始化临时坐标 
			coordinateTemp = *coordinateA;
			ptrRoad->nowNum = 0;			
			
			//重新入栈 
			for(int j = 0; j < i; j++) {
				coordinateTemp.x += dirX;
				stack.stackPush(ptrRoad, dirXE);
			}
			
			//Y移动 
			for(int j = 0; j < distenceY; j++) {
				coordinateTemp.y += dirY;
				stack.stackPush(ptrRoad, dirYE);
				//发现阻碍 
				if(!coordinateEmpty(coordinateTemp)) {	
					coordinateTemp.y -= dirY;	
					stack.stackPop(ptrRoad);
					break;
				}				
			}
			
			//Y移动时遇到障碍，无路径 
			if(coordinateTemp.y != coordinateB->y) {
				ptrRoad->nowNum = 0;
			}
			else {
				//最后一段直路 
				straightRoad = noCross(&coordinateTemp, coordinateB);
				//找到了路径 
				if(!stack.stackIsEmpty(straightRoad)) {
					for(int i = 0; i < straightRoad->nowNum; i++) {
						coordinateTemp.y += dirY;
						stack.stackPush(ptrRoad, straightRoad->data[i]);
					}
					break;
				}
				//遇到障碍，无路径 
				else {
					ptrRoad->nowNum = 0;
				}
			}
			
		}
	}
	//无路径 
	else {
		ptrRoad->nowNum = 0;
	}

	//路径二
	//先移动Y 
	if(stack.stackIsEmpty(ptrRoad) && coordinateTempA.around&dirYE) {
		
		//首先移动Y	 
		for(int i = 1; i < distenceY; i++) {
			
			//初始化临时坐标 
			coordinateTemp = *coordinateA;
			ptrRoad->nowNum = 0;			
			
			//重新入栈 
			for(int j = 0; j < i; j++) {
				coordinateTemp.y += dirY;
				stack.stackPush(ptrRoad, dirYE);
			}
			
			//X移动 
			for(int j = 0; j < distenceX; j++) {
				coordinateTemp.x += dirX;
				stack.stackPush(ptrRoad, dirXE);
				//发现阻碍 
				if(!coordinateEmpty(coordinateTemp)) {	
					coordinateTemp.x -= dirX;	
					stack.stackPop(ptrRoad);
					break;
				}				
			}
			
			//X移动时遇到障碍，无路径 
			if(coordinateTemp.x != coordinateB->x) {
				ptrRoad->nowNum = 0;
			}
			else {
				//最后一段直路 
				straightRoad = noCross(&coordinateTemp, coordinateB);
				//找到了路径 
				if(!stack.stackIsEmpty(straightRoad)) {
					for(int i = 0; i < straightRoad->nowNum; i++) {
						coordinateTemp.x += dirX;
						stack.stackPush(ptrRoad, straightRoad->data[i]);
					}
					break;
				}
				//遇到障碍，无路径 
				else {
					ptrRoad->nowNum = 0;
				}
			}
			
		}
	}
	
	stack.stackDestory(straightRoad);

	if(stack.stackIsEmpty(ptrRoad)) {
		//没有找到路径，销栈并返回NULL 
		stack.stackDestory(ptrRoad);
		return NULL;
	}
	else {
		return ptrRoad;	
	}	
}

//寻找路径 
stackStruct * Bingo::findTrail(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	stackStruct *ptrResult = NULL;
	
	//坐标相同，无路径 
	if(coordinateA->x == coordinateB->x && coordinateA->y == coordinateB->y) {
		printf("\n same Coordinate! No trail! \n");
		return NULL;
	}
	
	//包围检测 
	judgeAround(coordinateA);
	judgeAround(coordinateB);
	
	int distence = fabs(coordinateA->x - coordinateB->x) + fabs(coordinateA->y - coordinateB->y);
	//处理相邻情况
	if (distence == 1) {

	}
	else {
		//包围检测
		if (coordinateA->around == NONE_E || coordinateB->around == NONE_E) {
			printf("\n Coordinate surrounded! No trail! \n");
			return NULL;
		}
	}

	//坐标共线 
	if(sameLine(coordinateA, coordinateB) == true) {
		ptrResult = noCross(coordinateA, coordinateB);
		if(stack.stackIsEmpty(ptrResult)) ptrResult = twoCrossHor(coordinateA, coordinateB);
	}
	//坐标不共线 
	else {
		ptrResult = CrossAndBack(coordinateA, coordinateB);
		if(stack.stackIsEmpty(ptrResult)) ptrResult = twoCrossInside(coordinateA, coordinateB);
	}
	
	return ptrResult;
}

int Bingo::judgeProcess(int x1, int y1, int x2, int y2) {
	
	coordinateStruct coordinateA, coordinateB;
	
	coordinateA.x = x1;
	coordinateA.y = y1;
	
	coordinateB.x = x2;
	coordinateB.y = y2;
	
	stackStruct *ptrRoad = findTrail(&coordinateA, &coordinateB);
	
	if(!stack.stackIsEmpty(ptrRoad)) {
		stack.stackPrint(ptrRoad);
		return 1;
	}
	else {
		printf("\n stack is empty! No trail! \n");
	}
	
	stack.stackDestory(ptrRoad);	//一定记得销栈 	
	
	return 0;
}

