/* File : queue.c */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

bool IsQueueEmpty (Queue Q){
	return (IsListEmpty(Q));
}

void CreateQueue(Queue * Q){
	CreateList(Q);
}

void Add(Queue * Q, infotype X){
	InsertLast(Q, X);
}

void Del(Queue * Q, infotype * X){
	DeleteFirst(Q, X);
}

void PrintQueue(Queue Q){
	PrintForward(Q);
}
