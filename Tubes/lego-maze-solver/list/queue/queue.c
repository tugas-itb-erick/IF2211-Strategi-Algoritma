/* File : queue.c */

#include "queue.h"

int IsQueueEmpty (Queue * Q){
	if (IsListEmpty(Q))
		return 1;
	return 0;
}

void CreateQueue(Queue * Q){
	CreateList(Q);
}

void Push_Back(Queue * Q, infotype X){
	InsertLast(Q, X);
}

void Pop_Head(Queue * Q, infotype * X){
	DeleteFirst(Q, X);
}

void PrintQueue(Queue * Q){
	PrintForward(Q);
}
