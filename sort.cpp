/* NIM/Nama : Erick Wijaya */
/* FIle     : sort.cpp     */

#include "sort.h"
using namespace std;

void Swap(int &a, int &b){
  int temp = a;
  a = b;
  b = temp;
}

bool IsSorted(vector<int> &v, size_t size){
  bool sorted = true;
  size_t i = 0;

  while ((i < size-1) && (sorted)){
    if (v[i] > v[i+1])
      sorted = false;
    else
      i++;
  }

  return sorted;
}

void Merge(vector<int> &v, size_t left, size_t mid, size_t right){
  size_t i1 = left;
  size_t i2 = mid+1;
  vector<int> temp;

  while ((i1 <= mid) && (i2 <= right)){
    if (v[i1] <= v[i2])
      temp.push_back(v[i1++]);
    else
      temp.push_back(v[i2++]);
  }

  while (i1 <= mid)
    temp.push_back(v[i1++]);

  while (i2 <= right)
    temp.push_back(v[i2++]);

  for(size_t i=left; i<=right; i++)
    v[i] = temp[i-left];

}

void MergeSort(vector<int> &v, size_t left, size_t right){
  if (left < right){
    size_t mid = (left + right)/2;
    MergeSort(v, left, mid);
    MergeSort(v, mid+1, right);
    Merge(v, left, mid, right);
  }
}

void InsertionSort(vector<int> &v, size_t left, size_t right){
  int temp;

  for(size_t i=left+1; i<=right; i++){
    size_t pos = i;
    while ((pos > left) && (v[pos] < v[pos-1])){
      Swap(v[pos], v[pos-1]);
      --pos;
    }
  }
}

void SelectionSort(vector<int> &v, size_t left, size_t right){
  size_t imin;

  for(size_t i=left; i<right; i++){
    imin = i;
    for(size_t j=i+1; j<=right; j++){
      if (v[j] < v[imin])
        imin = j;
    }
    Swap(v[imin], v[i]);
  }

}

size_t Partition(vector<int> &v, size_t left, size_t right){
  int pivot = v[rand()%(right-left+1) + left]; // random pivot
  size_t il = left;
  size_t ir = right;

  while (il <= ir) {
    while (v[il] < pivot)
      ++il;
    while (v[ir] > pivot)
      --ir;
    if (il <= ir){
      Swap(v[il], v[ir]);
      ++il;
      if (ir > left)
      --ir;
    }
  }

  return ir;
}

void QuickSort(vector<int> &v, size_t left, size_t right){
  if (left < right){
    size_t mid = Partition(v, left, right);
    QuickSort(v, left, mid);
    QuickSort(v, mid+1, right);
  }
}
