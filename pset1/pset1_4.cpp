#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int compare(vector<unsigned long> v1, vector<unsigned long> v2){

    int order = v1.size();

    for(int i=0; i<order; i++){
        if(v1[order-(i+1)] < v2[order-(i+1)]){
            return 0;
        }
    }
    return 1;
}

vector<unsigned long> substract(vector<unsigned long> v1, vector<unsigned long>v2){

    int order = v1.size();
    int big = compare(v1, v2);
    if(big == 0){
        vector<unsigned long> v;
        v = v1;
        v1 = v2;
        v2 = v;
    }

    vector<unsigned long> v_result(order);
    vector<int> v_sign(order, 0);
    for(int i=0; i<order; i++){
        //v_sign[i] 을 빼야한다
        if ((v1[i] + v_sign[i]) < v2[i]){
            //그 앞자리에서 1을 당겨온다
            v_sign[i+1] = 1;
            bitset<64> up(1);
            up = up << 63;
            v_result[i] = up.to_ulong() + v1[i] - v2[i] + 1;
        }
        else{
            v_result[i] = v1[i] - v2[i];
        }

    }
    return v_result;
}

int main(){

    const int order = 10;
    vector<unsigned long> v1(order), v2(order), v_result(order);


    
    return 0;
}
