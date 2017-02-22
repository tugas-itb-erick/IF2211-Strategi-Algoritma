/* NIM/Nama : Erick Wijaya */
/* FIle     : sort.h       */

#pragma once

#include <iostream>

void MergeSort(vector<int> &v, size_t i, size_t j);
void InsertionSort(vector<int> &v, size_t i, size_t j);
void Merge(vector<int> &v, size_t i, size_t k, size_t j);

void SelectionSort(vector<int> &v, size_t i, size_t j);
void Select(vector<int> &v, size_t i, size_t j);

void QuickSort(vector<int> &v, size_t i, size_t j);
size_t Partition(vector<int> &v, size_t i, size_t j);
