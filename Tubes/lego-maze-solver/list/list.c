/* File : list.c */

#include "list.h"

int IsListEmpty (List *L)
{ // Kamus Lokal
	// Algoritma
	if (Last(*L) == -1)
		return 1;
	return 0;
}

void CreateList (List *L)
{ // Kamus Lokal
	int i;
	// Algoritma
	First(*L) = 0;
	Last(*L) = -1;
}

void InsertFirst (List *L, infotype X)
{ // Kamus Lokal
	int i;
	// Algoritma
	++Last(*L);
	for(i=Last(*L); i>0; i--)
		Info(*L,i) = Info(*L,i-1);
	Info(*L, First(*L)) = X;
}

void InsertLast (List *L, infotype X)
{ // Kamus Lokal
	int i;
	// Algoritma
	++Last(*L);
	Info(*L, Last(*L)) = X;
}

void DeleteFirst (List *L, infotype *X)
{ // Kamus Lokal
	int i;
	// Algoritma
	*X = Info(*L, First(*L));
	for(i=0; i<Last(*L); i++)
		Info(*L,i) = Info(*L,i+1);
	--Last(*L);
}

void DeleteLast (List *L, infotype *X)
{ // Kamus Lokal
	int i;
	// Algoritma
	*X = Info(*L, Last(*L));
	--Last(*L);
}

void PrintForward (List *L)
{ // Kamus Lokal
	int i;
	// Algoritma
	/*printf("[");
	for(i=0; i<=Last(*L); i++){
		printf("%d", Info(*L, i));
		if (i < Last(*L))
			printf(",");
	}
	printf("]");*/
}

void PrintBackward (List *L)
{ // Kamus Lokal
	int i;
	// Algoritma
	/*printf("[");
	for(i=Last(*L); i>=0; i--){
		printf("%d", Info(*L, i));
		if (i > 0)
			printf(",");
	}
	printf("]");*/
}
