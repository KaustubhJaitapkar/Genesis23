#include<iostream>
#include <fstream>
using namespace std;

int main(){
     fstream fin;
    fstream fout;
  
    remove("Acc.csv");
  
    rename("Accnew.csv", "Acc.csv");
    return 0;
}