/* NIM/Nama : Erick Wijaya  */
/* FIle     : sort_main.cpp */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "sort.h"
using namespace std;

const int max_val = 10000;
vector<int> vin(1000000);
vector<int> v(1000000);

void InputData(vector<int> &v, size_t size);
void CopyData(vector<int> &vin, vector<int> &vout, size_t size);
void PrintData(vector<int> &v, size_t size);
void PrintInfo(string s, size_t d, bool b, double t);

int main(){
  size_t size[] = {1000,5000,10000,50000,100000,500000,1000000};
  clock_t start, end;
  srand(time(NULL));
  InputData(vin, 1000000);

  for(size_t i=0; i<sizeof(size)/sizeof(size_t); i++){
    CopyData(vin, v, size[i]);
    start = clock();
    MergeSort(v, 0, size[i]-1);
    end = clock();
    PrintData(v, size[i]);
    PrintInfo("-- MERGE SORT --", size[i], IsSorted(v, size[i]), (end-start)/(double)(CLOCKS_PER_SEC));

    CopyData(vin, v, size[i]);
    start = clock();
    InsertionSort(v, 0, size[i]-1);
    end = clock();
    PrintData(v, size[i]);
    PrintInfo("-- INSERTION SORT --", size[i], IsSorted(v, size[i]), (end-start)/(double)(CLOCKS_PER_SEC));

    CopyData(vin, v, size[i]);
    start = clock();
    SelectionSort(v, 0, size[i]-1);
    end = clock();
    PrintData(v, size[i]);
    PrintInfo("-- SELECTION SORT --", size[i], IsSorted(v, size[i]), (end-start)/(double)(CLOCKS_PER_SEC));

    CopyData(vin, v, size[i]);
    start = clock();
    QuickSort(v, 0, size[i]-1);
    end = clock();
    PrintData(v, size[i]);
    PrintInfo("-- QUICK SORT --", size[i], IsSorted(v, size[i]), (end-start)/(double)(CLOCKS_PER_SEC));

  }

  return 0;
}

void InputData(vector<int> &v, size_t size){
  for(size_t i=0; i<size; i++)
    v[i] = rand()%max_val;
}

void CopyData(vector<int> &vin, vector<int> &vout, size_t size){
  for(size_t i=0; i<size; i++)
    vout[i] = vin[i];
}

void PrintData(vector<int> &v, size_t size){
  for(size_t i=0; i<size; i++){
    cout << v[i];
    if (v[i]/10 == 0)
      cout << "    ";
    else if (v[i]/100 == 0)
      cout << "   ";
    else if (v[i]/1000 == 0)
      cout << "  ";
    else
      cout << " ";
    if ((i+1) % 30 == 0)
      cout << endl;
  }
  cout << endl;
}

void PrintInfo(string s, size_t d, bool b, double t){
  cout << s << endl;
  cout << "Data: " << d << endl;
  cout << "Sorted (0/1): " << b << endl;
  cout << "Time Elapsed: " << setprecision(4) << t  << "s" << endl << endl;
  cout << "Press Enter to Continue" << endl;
  cin.ignore();
}
