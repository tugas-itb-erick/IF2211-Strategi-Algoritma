/* File : stack.c */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

bool IsStackEmpty (Stack S){
	return (IsListEmpty(S));
}

void CreateStack (Stack * S){
	CreateList(S);
}

void Push (Stack * S, infotype X){
	InsertFirst(S, X);
}

void Pop (Stack * S, infotype * X){
	DeleteFirst(S, X);
}

void PrintStack(Stack S){
	PrintForward(S);
}
