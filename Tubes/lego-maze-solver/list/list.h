/* File : list.h */

#pragma once

#define MAX 50

/* Definisi Type Data */
typedef int infotype;
typedef struct {
	int first;
	int last;
	infotype info[MAX];
} List;

/* Definisi list : */
/* List kosong : Last(L) = 0 */
/* Setiap elemen dapat diacu Info(L,i), Next(L), Prev(L) */
/* Elemen terakhir list: Last(L) */

/* Notasi Akses */
#define Info(L,i) ((L).info[(i)])
#define First(L) ((L).first)
#define Last(L) ((L).last)

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
int IsListEmpty (List *L);
/* Mengirim true jika list kosong. Lihat definisi di atas. */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList (List *L);
/* I.S. L sembarang  */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsertFirst (List *L, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Menambahkan elemen pertama dengan nilai X */
void InsertLast (List *L, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Menambahkan elemen list di akhir: elemen terakhir yang baru bernilai X */

/*** PENGHAPUSAN ELEMEN ***/
void DeleteFirst (List *L, infotype *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
void DeleteLast (List *L, infotype *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintForward (List *L);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen pertama */
/* ke elemen terakhir secara horizontal ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
void PrintBackward (List *L);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen terakhir */
/* ke elemen pertama secara horizontal ke kanan: [en,en-1,...,e2,e1] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [30,20,1] */
