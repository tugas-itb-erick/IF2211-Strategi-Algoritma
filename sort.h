/* NIM/Nama : Erick Wijaya */
/* FIle     : sort.h       */

#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

void Merge(vector<int> &v, size_t left, size_t mid, size_t right);
void MergeSort(vector<int> &v, size_t left, size_t right);
void InsertionSort(vector<int> &v, size_t left, size_t right);

void SelectionSort(vector<int> &v, size_t left, size_t right);

size_t Partition(vector<int> &v, size_t left, size_t right);
void QuickSort(vector<int> &v, size_t left, size_t right);

bool IsSorted(vector<int> &v, size_t size);
