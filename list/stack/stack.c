/* File : stack.c */

#include "stack.h"

int IsStackEmpty (Stack * S){
	if (IsListEmpty(S))
		return 1;
	return 0;
}

void CreateStack (Stack * S){
	CreateList(S);
}

void Push (Stack * S, infotype X){
	InsertLast(S, X);
}

void Pop (Stack * S, infotype * X){
	DeleteLast(S, X);
}

void PrintStack(Stack * S){
	PrintBackward(S);
}
