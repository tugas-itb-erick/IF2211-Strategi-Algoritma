#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int max_val = 1000;

void InputData(vector<int> &v, size_t size);
void PrintData(vector<int> &v);

int main(){
  size_t size[] = {1000,5000,10000,50000,100000,500000,1000000};
  vector<int> v;

  for(size_t i=0; i<1/*sizeof(size)*/; i++){
    InputData(v, size[i]);

    PrintData(v);
    cout << "Time Elapsed: " << endl << endl;

    cout << "Press Enter to Continue" << endl;
    cin.ignore();
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
