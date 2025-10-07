#include <bits/stdc++.h>
using namespace std;

int main(){
  int p,q; cin >> p >> q;
  if((p*p + q*q + 1) % 4 == 0){
    cout << (p*p + q*q + 1) / 4;
  }else{
    cout << -1;
  }
}
