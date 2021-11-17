#include "jugeBingo.h"



Bingo::Bingo(){

}
//�߽�һȦ��Ϊ0 
//X������Ϊ�� Y������Ϊ�� 

//��Χ��� 
void Bingo::judgeAround(coordinateStruct *coordinate) {
	
	//������� 
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

//��������Ƿ�Ϸ� 
bool Bingo::coordinateGood(coordinateStruct coordinate) {
	if(coordinate.x > 0 && coordinate.x < _mapSize+2 && coordinate.y > 0 && coordinate.y < _mapSize+2) {
		return true;
	}
	else {
		return false;
	}
}

//�ж��Ƿ���ͬһֱ����  
bool Bingo::sameLine(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	if(coordinateA->x == coordinateB->x || coordinateA->y == coordinateB->y) {
		return true;
	}
	else {
		return false;
	}
}

//�жϸ��������Ƿ���ͼ 
bool Bingo::coordinateEmpty(coordinateStruct coordinate) {
	if(image[coordinate.y][coordinate.x] != 0) {
		return false;
	}
	else {
		return true;
	}
}

//��·������NULL 
//�ж�ֱ������ 
stackStruct * Bingo::noCross(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	stackStruct *ptrRoad = NULL;
	
	int distence = 0;
	if(coordinateA->x == coordinateB->x) distence = fabs(coordinateB->y - coordinateA->y);
	else	distence = fabs(coordinateB->x - coordinateA->x);	
	
	//��ʼ��·��ջ 
	ptrRoad = (stackStruct*)malloc(sizeof(stackStruct));
	ptrRoad = stack.createStack(distence);
	
	//���ұ��� 
	if(coordinateB->x > coordinateA->x) {
		
		int tempCoordinateX = coordinateA->x;
		//���ұ��� 
		while (tempCoordinateX != coordinateB->x) {
			
			//·����ͨ 
			if(image[coordinateA->y][tempCoordinateX] != 0 && tempCoordinateX != coordinateA->x) {
				stack.stackDestory(ptrRoad);
				ptrRoad = NULL;
				break;
			}			
			tempCoordinateX++;	
			stack.stackPush(ptrRoad, RIGHT_E);
		}
		
	}
	//������� 
	else if(coordinateB->x < coordinateA->x) {
		
		int tempCoordinateX = coordinateA->x;
		//������� 
		while (tempCoordinateX != coordinateB->x) {
			
			//·����ͨ 
			if(image[coordinateA->y][tempCoordinateX] != 0 && tempCoordinateX != coordinateA->x) {
				stack.stackDestory(ptrRoad);
				ptrRoad = NULL;
				break;				
			}			
			stack.stackPush(ptrRoad, LEFT_E);
			tempCoordinateX--;				
		}	

	}
	//���ϱ��� 
	else if(coordinateB->y < coordinateA->y) {
		
		int tempCoordinateY = coordinateA->y;
		//���ϱ��� 
		while (tempCoordinateY != coordinateB->y) {
			
			//·����ͨ 
			if(image[tempCoordinateY][coordinateA->x] != 0 && tempCoordinateY != coordinateA->y) {
				stack.stackDestory(ptrRoad);
				ptrRoad = NULL;
				break;
			}			
			stack.stackPush(ptrRoad, UP_E);
			tempCoordinateY--;				
		}			

	}
	//���±��� 
	else if(coordinateB->y > coordinateA->y) {
		
		int tempCoordinateY = coordinateA->y;
		//���±��� 
		while (tempCoordinateY != coordinateB->y) {
			
			//·����ͨ 
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
		//û���ҵ�·������ջ������NULL 
		stack.stackDestory(ptrRoad);
		return NULL;
	}
	else {
		return ptrRoad;	
	}
}

//���ߵ���������Ѱ�ҷ�ֱ��·�� 
//��·������NULL 
stackStruct * Bingo::twoCrossHor(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	stackStruct *ptrRoad = NULL;
	
	int distenceX = 0;	//�����赲�����·�� 
	int distenceY = 0;
	if(coordinateA->x == coordinateB->x) {
		distenceY = fabs(coordinateB->y - coordinateA->y);
	}
	else {
		distenceX = fabs(coordinateB->x - coordinateA->x);
	}
	
	//��ʼ��·��ջ 
	ptrRoad = (stackStruct*)malloc(sizeof(stackStruct));
	ptrRoad = stack.createStack(distenceX + distenceY + _mapSize+1);
	
	stackStruct* straightRoad = NULL;

	//Y���� 
	if(distenceX == 0) {
		//��࿪�� 
		if(coordinateA->around&LEFT_E && coordinateB->around&LEFT_E) {
			
			//�����ƶ� 
			for(int i = 0; i < coordinateA->x; i++) {
				
				stack.stackPush(ptrRoad, LEFT_E);
				
				coordinateStruct coordinateTempA = *coordinateA;
				coordinateStruct coordinateTempB = *coordinateB;
				
				//Ѱ������֮���ֱ������ 
				coordinateTempA.x -= i + 1;
				coordinateTempB.x -= i + 1;

				if (!coordinateEmpty(coordinateTempA) || !coordinateEmpty(coordinateTempB)) {
					break;
				}
				
				judgeAround(&coordinateTempA);
				judgeAround(&coordinateTempB);
				straightRoad = noCross(&coordinateTempA, &coordinateTempB);
					
				//Ѱ�ҵ���·��	
				if(straightRoad != NULL) {
					for(int j = 0; j < straightRoad->nowNum; j++) {
						//��ֱ·ջ�е�����ѹ������·��ջ 
						stack.stackPush(ptrRoad, straightRoad->data[j]);
					}
					stack.stackPush(ptrRoad, RIGHT_E);
					break;	//�ҵ������·����ֱ������ѭ�� 
				}
				
			}
			
		}
		//��࿪��ʧ�ܣ��������ҿ��� 
		if(stack.stackIsEmpty(ptrRoad)) {
			if(coordinateA->around&RIGHT_E && coordinateB->around&RIGHT_E) {
			
				//�����ƶ� 
				for(int i = 0; i < _mapSize + 1 - coordinateA->x; i++) {
					
					stack.stackPush(ptrRoad, RIGHT_E);
					
					coordinateStruct coordinateTempA = *coordinateA;
					coordinateStruct coordinateTempB = *coordinateB;
					
					//Ѱ������֮���ֱ������ 
					coordinateTempA.x += i + 1;
					coordinateTempB.x += i + 1;

					if (!coordinateEmpty(coordinateTempA) || !coordinateEmpty(coordinateTempB)) {
						break;
					}
					
					judgeAround(&coordinateTempA);
					judgeAround(&coordinateTempB);
					straightRoad = noCross(&coordinateTempA, &coordinateTempB);
						
					//Ѱ�ҵ���·��	
					if(straightRoad != NULL) {
						for(int j = 0; j < straightRoad->nowNum; j++) {
							//��ֱ·ջ�е�����ѹ������·��ջ 
							stack.stackPush(ptrRoad, straightRoad->data[j]);
						}
						stack.stackPush(ptrRoad, LEFT_E);
						break;	//�ҵ������·����ֱ������ѭ�� 
					}
					
				}
										
			}
		}
		
	}
	//X���� 
	else {
		//�ϲ࿪�� 
		if(coordinateA->around&UP_E && coordinateB->around&UP_E) {
			
			//�����ƶ� 
			for(int i = 0; i < coordinateA->y; i++) {
				
				stack.stackPush(ptrRoad, UP_E);
				
				coordinateStruct coordinateTempA = *coordinateA;
				coordinateStruct coordinateTempB = *coordinateB;
				
				//Ѱ������֮���ֱ������ 
				coordinateTempA.y -= i + 1;
				coordinateTempB.y -= i + 1;

				if (!coordinateEmpty(coordinateTempA) || !coordinateEmpty(coordinateTempB)) {
					break;
				}
				
				judgeAround(&coordinateTempA);
				judgeAround(&coordinateTempB);
				straightRoad = noCross(&coordinateTempA, &coordinateTempB);
					
				//Ѱ�ҵ���·��	
				if(straightRoad != NULL) {
					for(int j = 0; j < straightRoad->nowNum; j++) {
						//��ֱ·ջ�е�����ѹ������·��ջ 
						stack.stackPush(ptrRoad, straightRoad->data[j]);
					}
					stack.stackPush(ptrRoad, DOWN_E);
					break;	//�ҵ������·����ֱ������ѭ�� 
				}
				
			}
			
		}
		//�ϲ࿪��ʧ�ܣ��������¿��� 
		if(stack.stackIsEmpty(ptrRoad)) {
			if(coordinateA->around&DOWN_E && coordinateB->around&DOWN_E) {
			
				//�����ƶ� 
				for(int i = 0; i < _mapSize - coordinateA->y; i++) {
					
					stack.stackPush(ptrRoad, DOWN_E);
					
					coordinateStruct coordinateTempA = *coordinateA;
					coordinateStruct coordinateTempB = *coordinateB;
					
					//Ѱ������֮���ֱ������ 
					coordinateTempA.y += i + 1;
					coordinateTempB.y += i + 1;

					if (!coordinateEmpty(coordinateTempA) || !coordinateEmpty(coordinateTempB)) {
						break;
					}
					
					judgeAround(&coordinateTempA);
					judgeAround(&coordinateTempB);
					straightRoad = noCross(&coordinateTempA, &coordinateTempB);
						
					//Ѱ�ҵ���·��	
					if(straightRoad != NULL) {
						for(int j = 0; j < straightRoad->nowNum; j++) {
							//��ֱ·ջ�е�����ѹ������·��ջ 
							stack.stackPush(ptrRoad, straightRoad->data[j]);
						}
						stack.stackPush(ptrRoad, UP_E);
						break;	//�ҵ������·����ֱ������ѭ�� 
					}
					
				}
										
			}
		}		
	}
	
	if(stack.stackIsEmpty(straightRoad)) {
		//û���ҵ�·������ջ������NULL 
		stack.stackDestory(ptrRoad);
		return NULL;
	}
	else {
		return ptrRoad;	
	}
}

//ֻתһ���������Լ��ھ�����ת���������� 
//��·������NULL 
stackStruct * Bingo::CrossAndBack(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	stackStruct *ptrRoad = NULL;
	
	int distenceX = 0;	//�����赲�����·�� 
	int distenceY = 0;
	
	distenceX = fabs(coordinateB->x - coordinateA->x);
	distenceY = fabs(coordinateB->y - coordinateA->y);
	
	//��ʼ��·��ջ 
	ptrRoad = (stackStruct*)malloc(sizeof(stackStruct));
	ptrRoad = stack.createStack(3*(_mapSize+1));
	 
	coordinateStruct coordinateTempA = *coordinateA;
	coordinateStruct coordinateTempB = *coordinateB;	
	coordinateStruct coordinateMid[2];
	//��һ���м����� 
	coordinateMid[0].x = coordinateTempB.x;
	coordinateMid[0].y = coordinateTempA.y;
	//�ڶ����м����� 
	coordinateMid[1].x = coordinateTempA.x;
	coordinateMid[1].y = coordinateTempB.y;
	
	/*
	printf("coordinateA x: %d y:%d \n",coordinateA->x, coordinateA->y);	
	printf("coordinateB x: %d y:%d \n",coordinateB->x, coordinateB->y);		
	
	printf("coordinateMid[0] x: %d y:%d \n",coordinateMid[0].x,coordinateMid[0].y);	
	printf("coordinateMid[1] x: %d y:%d \n",coordinateMid[1].x,coordinateMid[1].y);	
	*/
	
	//�ж������Χ 
	judgeAround(&coordinateTempA);
	judgeAround(&coordinateTempB);
	judgeAround(&coordinateMid[0]);
	judgeAround(&coordinateMid[1]);
	
	//ǰ������
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
	//��һ��·�� 
	for(int i = 0; i < 2; i++) {
		straightRoadFirst[i] = noCross(&coordinateTempA, &coordinateMid[i]);
	}
	//�ڶ���·�� 
	for(int i = 0; i < 2; i++) {
		straightRoadSecond[i] = noCross(&coordinateMid[i], &coordinateTempB);
	}	
	
	//�����м̵�һ·���Ƿ�ͨ 
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
	//�����м̵��·���Ƿ�ͨ 
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

	//û���ҵ�·�������о�������· 
	if(stack.stackIsEmpty(ptrRoad)) {
		
		//ȫ�߷�������·��  
		if(straightRoadFirst[0] == NULL && straightRoadFirst[1] == NULL \
			&& straightRoadSecond[0] == NULL && straightRoadSecond[1] == NULL) {
				
		}
		else {
			
			coordinateStruct coordinateCross[2];	//ת�Ǵ����� 
			stackStruct *crossRoad[3] = {NULL, NULL, NULL};				//��¼����ת��·�� 
			
			//����·��һ 
			//���м����걻ռ�ã��޽� 
			if(coordinateEmpty(coordinateMid[0])) {			
								
				//��·���е�����·��ֻ������һ����ͨ 
				if(straightRoadFirst[0] != NULL) {
					
					//�յ� 
					coordinateCross[0] = coordinateMid[0];	
					coordinateCross[0].x += dirX;
					coordinateCross[1] = coordinateCross[0];
					coordinateCross[1].y += dirY*distenceY;						
					
					//�յ�����Ϸ��ҿ� 
					while(coordinateGood(coordinateCross[0]) && coordinateGood(coordinateCross[1]) && \
						  coordinateEmpty(coordinateCross[0]) && coordinateEmpty(coordinateCross[1])) {
						
						//���������· 
						crossRoad[0] = noCross(&coordinateMid[0], &coordinateCross[0]);
						crossRoad[1] = noCross(&coordinateCross[0], &coordinateCross[1]);
						crossRoad[2] = noCross(&coordinateCross[1], coordinateB);
						
						//����ͨ· 
						if(crossRoad[0] != NULL && crossRoad[1] != NULL && crossRoad[2] != NULL) {
							
							//����ͨ·����ջ�������ƹ�����ͨ·�� 
							for(int i = 0; i < straightRoadFirst[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, straightRoadFirst[0]->data[i]);
							}							
							
							//������·��ջ 
							for(int i = 0; i < crossRoad[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[0]->data[i]);
							}
							for(int i = 0; i < crossRoad[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[1]->data[i]);
							}							
							for(int i = 0; i < crossRoad[2]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[2]->data[i]);
							}
							break;	//����ѭ��							
						}
						//������ 
						else {
							//ָ���ÿգ����´�ʹ�� 
							crossRoad[0] = NULL;
							crossRoad[1] = NULL;
							crossRoad[2] = NULL;
						}
						
						//������һ��յ����� 
						coordinateCross[0].x += dirX;
						coordinateCross[1].x += dirX;
					}
					
				}
				 
				if(straightRoadSecond[0] != NULL) {
					
					//�յ� 
					coordinateCross[0] = *coordinateA;	
					coordinateCross[0].y -= dirY;
					coordinateCross[1] = coordinateCross[0];
					coordinateCross[1].x += dirX*distenceX;						
					
					//�յ�����Ϸ��ҿ� 
					while(coordinateGood(coordinateCross[0]) && coordinateGood(coordinateCross[1]) && \
						  coordinateEmpty(coordinateCross[0]) && coordinateEmpty(coordinateCross[1])) {
						
						//���������· 
						crossRoad[0] = noCross(coordinateA, &coordinateCross[0]);
						crossRoad[1] = noCross(&coordinateCross[0], &coordinateCross[1]);
						crossRoad[2] = noCross(&coordinateCross[1], &coordinateMid[0]);
						
						//����ͨ· 
						if(crossRoad[0] != NULL && crossRoad[1] != NULL && crossRoad[2] != NULL) {						
							
							//������·��ջ 
							for(int i = 0; i < crossRoad[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[0]->data[i]);
							}
							for(int i = 0; i < crossRoad[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[1]->data[i]);
							}							
							for(int i = 0; i < crossRoad[2]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[2]->data[i]);
							}
							
							//����ͨ·����ջ
							for(int i = 0; i < straightRoadSecond[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, straightRoadSecond[0]->data[i]);
							}								
							
							break;	//����ѭ��							
						}
						//������ 
						else {
							//ָ���ÿգ����´�ʹ�� 
							crossRoad[0] = NULL;
							crossRoad[1] = NULL;
							crossRoad[2] = NULL;
						}
						
						//������һ��յ����� 
						coordinateCross[0].y += dirY;
						coordinateCross[1].y += dirY;
					}
										
				}				
			}
			
			//����·����
			//���м����걻ռ�ã��޽� 
			if(coordinateEmpty(coordinateMid[1]) && stack.stackIsEmpty(ptrRoad)) {
								
				//��·���е�����·��ֻ������һ����ͨ 
				if(straightRoadFirst[1] != NULL) {
					
					//�յ� 
					coordinateCross[0] = coordinateMid[1];	
					coordinateCross[0].y += dirY;
					coordinateCross[1] = coordinateCross[0];
					coordinateCross[1].x += dirX*distenceX;						
					
					//�յ�����Ϸ��ҿ� 
					while(coordinateGood(coordinateCross[0]) && coordinateGood(coordinateCross[1]) && \
						  coordinateEmpty(coordinateCross[0]) && coordinateEmpty(coordinateCross[1])) {
						
						//���������· 
						crossRoad[0] = noCross(&coordinateMid[1], &coordinateCross[0]);
						crossRoad[1] = noCross(&coordinateCross[0], &coordinateCross[1]);
						crossRoad[2] = noCross(&coordinateCross[1], coordinateB);
						
						//����ͨ· 
						if(crossRoad[0] != NULL && crossRoad[1] != NULL && crossRoad[2] != NULL) {
							
							//����ͨ·����ջ�������ƹ�����ͨ·�� 
							for(int i = 0; i < straightRoadFirst[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, straightRoadFirst[1]->data[i]);
							}							
							
							//������·��ջ 
							for(int i = 0; i < crossRoad[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[0]->data[i]);
							}
							for(int i = 0; i < crossRoad[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[1]->data[i]);
							}							
							for(int i = 0; i < crossRoad[2]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[2]->data[i]);
							}
							break;	//����ѭ��							
						}
						//������ 
						else {
							//ָ���ÿգ����´�ʹ�� 
							crossRoad[0] = NULL;
							crossRoad[1] = NULL;
							crossRoad[2] = NULL;
						}
						
						//������һ��յ����� 
						coordinateCross[0].y += dirY;
						coordinateCross[1].y += dirY;
					}
					
				}
				 
				if(straightRoadSecond[1] != NULL) {
					
					//�յ� 
					coordinateCross[0] = *coordinateA;	
					coordinateCross[0].x -= dirX;
					coordinateCross[1] = coordinateCross[0];
					coordinateCross[1].y += dirY*distenceY;						
					
					//�յ�����Ϸ��ҿ� 
					while(coordinateGood(coordinateCross[0]) && coordinateGood(coordinateCross[1]) && \
						  coordinateEmpty(coordinateCross[0]) && coordinateEmpty(coordinateCross[1])) {
						
						//���������· 
						crossRoad[0] = noCross(coordinateA, &coordinateCross[0]);
						crossRoad[1] = noCross(&coordinateCross[0], &coordinateCross[1]);
						crossRoad[2] = noCross(&coordinateCross[1], &coordinateMid[1]);
						
						//����ͨ· 
						if(crossRoad[0] != NULL && crossRoad[1] != NULL && crossRoad[2] != NULL) {						
							
							//������·��ջ 
							for(int i = 0; i < crossRoad[0]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[0]->data[i]);
							}
							for(int i = 0; i < crossRoad[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[1]->data[i]);
							}							
							for(int i = 0; i < crossRoad[2]->nowNum; i++) {
								stack.stackPush(ptrRoad, crossRoad[2]->data[i]);
							}
							
							//����ͨ·����ջ
							for(int i = 0; i < straightRoadSecond[1]->nowNum; i++) {
								stack.stackPush(ptrRoad, straightRoadSecond[1]->data[i]);
							}								
							
							break;	//����ѭ��							
						}
						//������ 
						else {
							//ָ���ÿգ����´�ʹ�� 
							crossRoad[0] = NULL;
							crossRoad[1] = NULL;
							crossRoad[2] = NULL;
						}
						
						//������һ��յ����� 
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
		//û���ҵ�·������ջ������NULL 
		stack.stackDestory(ptrRoad);
		return NULL;
	}
	else {
		return ptrRoad;	
	}
}

//�ھ����ڲ��������� 
//��·������NULL 
stackStruct * Bingo::twoCrossInside(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	stackStruct *ptrRoad = NULL;
	
	int distenceX = 0;	//�����赲�����·�� 
	int distenceY = 0;
	
	distenceX = fabs(coordinateB->x - coordinateA->x);
	distenceY = fabs(coordinateB->y - coordinateA->y);
	
	//��ʼ��·��ջ 
	ptrRoad = (stackStruct*)malloc(sizeof(stackStruct));
	ptrRoad = stack.createStack(distenceX + distenceY);
	 
	coordinateStruct coordinateTempA = *coordinateA;
	coordinateStruct coordinateTempB = *coordinateB;	
	coordinateStruct coordinateTemp = *coordinateA;
	
	/*
	printf("coordinateA x: %d y:%d \n",coordinateA->x, coordinateA->y);	
	printf("coordinateB x: %d y:%d \n",coordinateB->x, coordinateB->y);		
	*/
	
	//�ж������Χ 
	judgeAround(&coordinateTempA);
	judgeAround(&coordinateTempB);
	
	//ǰ�������¼ 
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
	
	//·��һ 
	//���ƶ�X
	if(coordinateTempA.around&dirXE) {
		
		//�����ƶ�X	 
		for(int i = 1; i < distenceX; i++) {
			
			//��ʼ����ʱ���� 
			coordinateTemp = *coordinateA;
			ptrRoad->nowNum = 0;			
			
			//������ջ 
			for(int j = 0; j < i; j++) {
				coordinateTemp.x += dirX;
				stack.stackPush(ptrRoad, dirXE);
			}
			
			//Y�ƶ� 
			for(int j = 0; j < distenceY; j++) {
				coordinateTemp.y += dirY;
				stack.stackPush(ptrRoad, dirYE);
				//�����谭 
				if(!coordinateEmpty(coordinateTemp)) {	
					coordinateTemp.y -= dirY;	
					stack.stackPop(ptrRoad);
					break;
				}				
			}
			
			//Y�ƶ�ʱ�����ϰ�����·�� 
			if(coordinateTemp.y != coordinateB->y) {
				ptrRoad->nowNum = 0;
			}
			else {
				//���һ��ֱ· 
				straightRoad = noCross(&coordinateTemp, coordinateB);
				//�ҵ���·�� 
				if(!stack.stackIsEmpty(straightRoad)) {
					for(int i = 0; i < straightRoad->nowNum; i++) {
						coordinateTemp.y += dirY;
						stack.stackPush(ptrRoad, straightRoad->data[i]);
					}
					break;
				}
				//�����ϰ�����·�� 
				else {
					ptrRoad->nowNum = 0;
				}
			}
			
		}
	}
	//��·�� 
	else {
		ptrRoad->nowNum = 0;
	}

	//·����
	//���ƶ�Y 
	if(stack.stackIsEmpty(ptrRoad) && coordinateTempA.around&dirYE) {
		
		//�����ƶ�Y	 
		for(int i = 1; i < distenceY; i++) {
			
			//��ʼ����ʱ���� 
			coordinateTemp = *coordinateA;
			ptrRoad->nowNum = 0;			
			
			//������ջ 
			for(int j = 0; j < i; j++) {
				coordinateTemp.y += dirY;
				stack.stackPush(ptrRoad, dirYE);
			}
			
			//X�ƶ� 
			for(int j = 0; j < distenceX; j++) {
				coordinateTemp.x += dirX;
				stack.stackPush(ptrRoad, dirXE);
				//�����谭 
				if(!coordinateEmpty(coordinateTemp)) {	
					coordinateTemp.x -= dirX;	
					stack.stackPop(ptrRoad);
					break;
				}				
			}
			
			//X�ƶ�ʱ�����ϰ�����·�� 
			if(coordinateTemp.x != coordinateB->x) {
				ptrRoad->nowNum = 0;
			}
			else {
				//���һ��ֱ· 
				straightRoad = noCross(&coordinateTemp, coordinateB);
				//�ҵ���·�� 
				if(!stack.stackIsEmpty(straightRoad)) {
					for(int i = 0; i < straightRoad->nowNum; i++) {
						coordinateTemp.x += dirX;
						stack.stackPush(ptrRoad, straightRoad->data[i]);
					}
					break;
				}
				//�����ϰ�����·�� 
				else {
					ptrRoad->nowNum = 0;
				}
			}
			
		}
	}
	
	stack.stackDestory(straightRoad);

	if(stack.stackIsEmpty(ptrRoad)) {
		//û���ҵ�·������ջ������NULL 
		stack.stackDestory(ptrRoad);
		return NULL;
	}
	else {
		return ptrRoad;	
	}	
}

//Ѱ��·�� 
stackStruct * Bingo::findTrail(coordinateStruct *coordinateA, coordinateStruct *coordinateB) {
	
	stackStruct *ptrResult = NULL;
	
	//������ͬ����·�� 
	if(coordinateA->x == coordinateB->x && coordinateA->y == coordinateB->y) {
		printf("\n same Coordinate! No trail! \n");
		return NULL;
	}
	
	//��Χ��� 
	judgeAround(coordinateA);
	judgeAround(coordinateB);
	
	int distence = fabs(coordinateA->x - coordinateB->x) + fabs(coordinateA->y - coordinateB->y);
	//�����������
	if (distence == 1) {

	}
	else {
		//��Χ���
		if (coordinateA->around == NONE_E || coordinateB->around == NONE_E) {
			printf("\n Coordinate surrounded! No trail! \n");
			return NULL;
		}
	}

	//���깲�� 
	if(sameLine(coordinateA, coordinateB) == true) {
		ptrResult = noCross(coordinateA, coordinateB);
		if(stack.stackIsEmpty(ptrResult)) ptrResult = twoCrossHor(coordinateA, coordinateB);
	}
	//���겻���� 
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
	
	stack.stackDestory(ptrRoad);	//һ���ǵ���ջ 	
	
	return 0;
}

