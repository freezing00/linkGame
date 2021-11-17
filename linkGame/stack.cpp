#include "stack.h"


Stack::Stack(){
}


//����ջ 
stackStruct*  Stack::createStack(int maxNum) {

	if (maxNum == 0) return NULL;
	stackStruct* ptr = (stackStruct*)malloc(sizeof(stackStruct));
	ptr->maxNum = maxNum;
	ptr->data = (dataType*)malloc(maxNum * sizeof(dataType));
	ptr->nowNum = 0;

	return ptr;
}

//�ж�ջ�� 
bool Stack::stackIsEmpty(stackStruct* ptr) {

	if (ptr == NULL) return true;
	if (ptr->nowNum == 0) return true;
	else return false;
}

//�ж�ջ��  
bool Stack::stackIsFull(stackStruct* ptr) {

	if (ptr->nowNum >= ptr->maxNum) return true;
	else return false;
}

//��ջ 
bool Stack::stackPush(stackStruct* ptr, dataType data) {

	if (ptr == NULL || stackIsFull(ptr)) {

		if (ptr = NULL) printf("stack is NULL!");
		if (stackIsFull(ptr)) printf("stack is full!");

		return false;
	}

	ptr->data[ptr->nowNum] = data;
	ptr->nowNum++;
	return true;
}

//��ջ 
dataType Stack::stackPop(stackStruct* ptr) {

	if (ptr->nowNum == 0) return false;

	dataType data = ptr->data[ptr->nowNum - 1];
	ptr->nowNum--;
	return data;
}

//��ȡջ��Ԫ�� 
dataType Stack::stackTop(stackStruct* ptr) {

	if (ptr->nowNum == 0) {
		printf("stack is empty! No top!\n");
		return 0;
	}

	return ptr->data[ptr->nowNum - 1];
}

void Stack::stackPrint(stackStruct* ptr) {

	if (ptr == NULL && ptr->nowNum == 0) {
		printf("\n stack is NULL or empty! Cannot print! \n");
	}

	printf("trail is ");
	for (int i = 0; i < ptr->nowNum; i++) {
		switch (ptr->data[i]) {
		case LEFT_E:
			printf(" L ");
			break;
		case RIGHT_E:
			printf(" D ");
			break;
		case UP_E:
			printf(" U ");
			break;
		case DOWN_E:
			printf(" D ");
			break;
		}
	}

}

//����˳��ջ���ͷ�ջ��ռ�洢�ռ�
bool Stack::stackDestory(stackStruct* ptr) {

	if (ptr == NULL) {
		printf("stack is NULL! Cannot destory!\n");
	}
	else {
		free(ptr->data);
		free(ptr);
	}

	return true;
}
