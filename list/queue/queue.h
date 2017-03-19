/* File : queue.h */

#pragma once

#include <stdbool.h>
#include "../list.h"

/* Representasi Queue dengan List */
typedef List Queue;

/* Selektor */
#define Head(Q) (Q).First
#define Tail(Q) (Q).Last
#define InfoHead(Q) (Q).First->Info
#define InfoTail(Q) (Q).Last->Info

/* ********* PROTOTYPE REPRESENTASI LOJIK QUEUE ***************/
bool IsQueueEmpty(Queue Q);
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
void CreateQueue(Queue * Q);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
void Add(Queue * Q, infotype X);
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void Del(Queue * Q, infotype * X);
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
void PrintQueue(Queue S);
/* Mencetak seluruh isi Queue Q dari HEAD hingga TAIL */
