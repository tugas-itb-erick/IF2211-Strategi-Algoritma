#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "sort.h"
using namespace std;

const int max_val = 1000;

void InputData(vector<int> &v, size_t size);
void PrintData(vector<int> &v);
void PrintInfo(string s, size_t d, double t);

int main(){
  size_t size[] = {1000,5000,10000,50000,100000,500000,1000000};
  vector<int> v;
  clock_t start, end;

  for(size_t i=0; i<1/*sizeof(size)*/; i++){
    InputData(v, size[i]);
    start = clock();
    MergeSort(v, 0, size[i]-1);
    end = clock();
    PrintData(v);
    PrintInfo("-- MERGE SORT --", size[i], (end-start)/(CLOCKS_PER_SEC/1000));

    InputData(v, size[i]);
    start = clock();
    InsertionSort(v, 0, size[i]-1);
    end = clock();
    PrintData(v);
    PrintInfo("-- INSERTION SORT --", size[i], (end-start)/(CLOCKS_PER_SEC/1000));

    InputData(v, size[i]);
    start = clock();
    SelectionSort(v, 0, size[i]-1);
    end = clock();
    PrintData(v);
    PrintInfo("-- SELECTION SORT --", size[i], (end-start)/(CLOCKS_PER_SEC/1000));
  }

}

void InputData(vector<int> &v, size_t size){
  v.clear();
  for(size_t i=0; i<size; i++)
    v.push_back(rand()%max_val);
}

void PrintData(vector<int> &v){
  for(size_t i=0; i<v.size(); i++){
    cout << v[i];
    if (v[i]/10 == 0)
      cout << "   ";
    else if (v[i]/100 == 0)
      cout << "  ";
    else
      cout << " ";
    if ((i+1) % 40 == 0)
      cout << endl;
  }
  cout << endl;
}

void PrintInfo(string s, size_t d, double t){
  cout << s << endl;
  cout << "Data: " << d << endl;
  cout << "Time Elapsed: " << t  << "ms" << endl << endl;
  cout << "Press Enter to Continue" << endl;
  cin.ignore();
}
