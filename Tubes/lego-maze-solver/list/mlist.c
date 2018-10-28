/* File : mlist.c */

#include <stdio.h>
#include "list.h"
#include "stack/stack.h"
#include "queue/queue.h"

int main(){
  int i;
  int dum;

  printf("LIST DRIVER\n");
  List L1;
  CreateList(&L1);

  printf("Test Insert\n");
  for(i=0; i<10; i++){
    InsertFirst(&L1, i);
  }
  PrintForward(&L1); printf("\n");
  PrintBackward(&L1); printf("\n");

  printf("Test Delete\n");
  for(i=0; i<2; i++){
    DeleteFirst(&L1, &dum);
    DeleteLast(&L1, &dum);
  }
  PrintForward(&L1); printf("\n");
  PrintBackward(&L1); printf("\n\n");

  printf("STACK DRIVER\n");
  Stack S;
  CreateStack(&S);

  printf("Test Push\n");
  for(i=0; i<10; i++){
    Push(&S, i);
  }
  PrintStack(&S); printf("\n");

  printf("Test Pop\n");
  for(i=0; i<2; i++){
    Pop(&S, &dum);
  }
  PrintStack(&S); printf("\n\n");

  printf("QUEUE DRIVER\n");
  Queue Q;
  CreateQueue(&Q);

  printf("Test Add\n");
  for(i=0; i<10; i++){
    Add(&Q, i);
  }
  PrintQueue(&Q); printf("\n");

  printf("Test Del\n");
  for(i=0; i<2; i++){
    Del(&Q, &dum);
  }
  PrintQueue(&Q); printf("\n");

  printf("Test Add\n");
  Add(&Q, 12);
  PrintQueue(&Q); printf("\n\n");

  return 0;
}
