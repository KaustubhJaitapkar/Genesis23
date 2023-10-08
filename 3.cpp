#include<iostream>
#include<fstream>
using namespace std;

int main(){
    remove("balance.csv");
  
    rename("balancenew.csv", "balance.csv");
    return 0;
}