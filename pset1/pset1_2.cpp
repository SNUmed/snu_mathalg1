#include <iostream>
#include <vector>

using namespace std;

int main(){
    const int order = 2;

    vector<int> v1, v2, v_result(2 * order -1, 0);
    v1.resize(order);
    v2.resize(order);

    // assign values to polynomials
    v1[0]=2;
    v1[1]=2;

    v2[0]=1;
    v2[1]=1;

    // multiply vectors
    vector<int> v_add(order, 0);
    for(int i=0; i<order; i++){

        for(int j=0; j<order; j++){
            v_add[j] = v1[j] * v2[i];
        } 

        for(int j=0; j<order; j++){
            v_result[i+j] += v_add[j];
        }
        
    }
    
    // print as latex in the form $v_result[0] + v_result[1]*x + v_result[2]*x^2 + ... 
    cout<<"$";
    for(int i=0; i<2*order-1; i++){
        if (v_result[i] != 0){

            if (i<2*order-2){
                cout<<v_result[i]<<"x^"<<i<<"+";
            } else {
                cout<<v_result[i]<<"x^"<<i;
            }
        }
    }
    cout<<"$";

    /* for addition, simply add by element using for loop */

    return 0;
}
