#include <iostream>
#include <bitset>

using namespace std;

int main(){
    bitset<64> bitset1(7);
    bitset<64> bitset2(8);
    if(bitset2 > bitset1){
        cout << bitset1;
    } 


    return 0;
}
