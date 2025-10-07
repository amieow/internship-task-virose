#include <bits/stdc++.h>
using namespace std;

int main(){
  string S; cin >> S;
  for(char &s:S){
    s ^= 32;
  }
  cout << S;
}
