/* File : list.c */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

void InsFirst (List *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void InsLast (List *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void DelFirst (List *L, address *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelLast (List *L, address *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, jika ada */

bool IsListEmpty (List L)
{ // Kamus Lokal
	// Algoritma
	return ((First(L) == Nil) && (Last(L) == Nil));
}

void CreateList (List *L)
{ // Kamus Lokal
	// Algoritma
	First(*L) = Nil;
	Last(*L) = Nil;
}

address Alokasi (infotype X)
{ // Kamus Lokal
	address P;
	// Algoritma
	P = (address) malloc (sizeof(ElmtList));
	if (P != Nil){
		Info(P) = X;
		Next(P) = Nil;
		Prev(P) = Nil;
	}
	return P;
}

void Dealokasi (address P)
{ // Kamus Lokal
	// Algoritma
	free(P);
}

address Search (List L, infotype X)
{ // Kamus Lokal
	address P;
	bool found;
	// Algoritma
	P = First(L);
	found = false;
	while ((P != Nil) && !(found)){
		if (Info(P) == X)
			found = true;
		else
			P = Next(P);
	}
	return P;
}

void InsertFirst (List *L, infotype X)
{ // Kamus Lokal
	address P;
	// Algoritma
	P = Alokasi(X);
	if (P != Nil)
		InsFirst(L, P);
}

void InsertLast (List *L, infotype X)
{ // Kamus Lokal
	address P;
	// Algoritma
	P = Alokasi(X);
	if (P != Nil)
		InsLast(L, P);
}

void DeleteFirst (List *L, infotype *X)
{ // Kamus Lokal
	address P;
	// Algoritma
	DelFirst(L, &P);
	*X = Info(P);
	Dealokasi(P);
}

void DeleteLast (List *L, infotype *X)
{ // Kamus Lokal
	address P;
	// Algoritma
	DelLast(L, &P);
	*X = Info(P);
	Dealokasi(P);
}

void PrintForward (List L)
{ // Kamus Lokal
	address P;
	// Algoritma
	printf("[");
	P = First(L);
	while (P != Nil){
		printf("%d", Info(P));
		if (Next(P) != Nil)
			printf(",");
		P = Next(P);
	}
	printf("]");
}

void PrintBackward (List L)
{ // Kamus Lokal
	address P;
	// Algoritma
	printf("[");
	P = Last(L);
	while (P != Nil){
		printf("%d", Info(P));
		if (Prev(P) != Nil)
			printf(",");
		P = Prev(P);
	}
	printf("]");
}

void InsFirst (List *L, address P)
{ // Kamus Lokal
  // Algoritma
  Next(P) = First(*L);
  if (IsListEmpty(*L)){
    Last(*L) = P;
  }else{
    Prev(First(*L)) = P;
  }
  First(*L) = P;
}

void InsLast (List *L, address P)
{ // Kamus Lokal
  // Algoritma
  Prev(P) = Last(*L);
  if (IsListEmpty(*L)){
    First(*L) = P;
  }else{
    Next(Last(*L)) = P;
  }
  Last(*L) = P;
}

void DelFirst (List *L, address *P)
{ // Kamus Lokal
  // Algoritma
  *P = First(*L);
  if (First(*L) == Last(*L)){ // IsOneElmt, tidak mungkin First dan Last bernilai Nil
    Last(*L) = Nil;
  }else{
    Prev(Next(*P)) = Nil;
  }
  First(*L) = Next(*P);
  Next(*P) = Nil;
  Prev(*P) = Nil;
}

void DelLast (List *L, address *P)
{ // Kamus Lokal
  // Algoritma
  *P = Last(*L);
  if (First(*L) == Last(*L)){ // IsOneElmt, tidak mungkin First dan Last bernilai Nil
    First(*L) = Nil;
  }else{
    Next(Prev(*P)) = Nil;
  }
  Last(*L) = Prev(*P);
  Prev(*P) = Nil;
  Next(*P) = Nil;
}
