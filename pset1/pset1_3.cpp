#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int main(){
    const int order = 10;
    vector<unsigned long> v1, v2, v_result(order + 1, 0);
    v1.resize(order);
    v2.resize(order);

    for(int i=0; i<order; i++){
        cout << "input i'th value of v1: ";
        cin >> v1[i];
        cout << "input i'th value of v2: ";
        cin >> v2[i];
    }

    for(int i=0; i<order; i++){
        v_result[i] += v1[i] + v2[i];
        bitset<64> int_max(1);
        int_max = int_max << 63;

        if (v1[i] > (int_max.to_ulong() - v2[i])){
            v_result[i+1] += 1;
        }
    }

    for(int i=0; i<order+1; i++){
        cout << v_result[i] << endl;
    }
    
    return 0;
}
