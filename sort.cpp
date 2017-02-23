/* NIM/Nama : Erick Wijaya */
/* FIle     : sort.cpp     */

#include "sort.h"
using namespace std;

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
  /*if (left < right){
    size_t mid = left;
    InsertionSort(v, left, mid);
    InsertionSort(v, mid+1, right);
    Merge(v, left, mid, right);
  }*/
  int temp;

  for(size_t i=left+1; i<=right; i++){
    size_t pos = i;
    while ((pos > left) && (v[pos] < v[pos-1])){
      temp = v[pos];
      v[pos] = v[pos-1];
      v[pos-1] = temp;
      --pos;
    }
  }
}

void Select(vector<int> &v, size_t left, size_t right){
  int temp;
  size_t imin = left;

  for(size_t i=left+1; i<=right; i++){
    if (v[i] < v[imin])
      imin = i;
  }

  temp = v[imin];
  v[imin] = v[left];
  v[left] = temp;
}

void SelectionSort(vector<int> &v, size_t left, size_t right){
  /*if (left < right){
    Select(v, left, right);
    SelectionSort(v, left+1, right);
  }*/
  int temp;
  size_t imin;

  for(size_t i=left; i<right; i++){
    imin = i;
    for(size_t j=i+1; j<=right; j++){
      if (v[j] < v[imin])
        imin = j;
    }

    temp = v[imin];
    v[imin] = v[i];
    v[i] = temp;
  }

}

size_t Partition(vector<int> &v, size_t left, size_t right){
  size_t pivot;
  return 0;
}

void QuickSort(vector<int> &v, size_t left, size_t right){
  if (left < right){
    size_t mid = Partition(v, left, right);
    QuickSort(v, left, mid);
    QuickSort(v, mid+1, right);
  }
}
