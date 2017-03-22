/* File : stack.h */

#pragma once

#include "../list.h"

/* Representasi Stack dengan List */
typedef List Stack;

/* Selektor */
#define Top(S) (S).last
#define InfoTop(S) (S).info[last]

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
int IsStackEmpty (Stack * S);
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
void CreateStack (Stack * S);
/* I.S. sembarang */
/* F.S. Membuat sebuah stack S yang kosong */
void Push (Stack * S, infotype X);
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void Pop (Stack * S, infotype * X);
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
void PrintStack(Stack * S);
/* Mencetak seluruh isi Stack S dari Top */
