#include <iostream>
#include <vector>

using namespace std;

vector<int> addition(vector<int> v1, vector<int> v2){
    int vlen = v1.size();

    vector<int> v(vlen);
    for(int i=0; i<vlen; i++){
        v[i] = v1[i] + v2[i];
    }

    return v;
}

vector<int> substraction(vector<int> v1, vector<int> v2){
    int vlen = v1.size();

    vector<int> v(vlen);
    for(int i=0; i<vlen; i++){
        v[i] = v1[i] - v2[i];
    }

    return v;
}

vector<int> multiplication(vector<int> v1, vector<int> v2){
    int vlen = 2 * v1.size() - 1;

    vector<int> v(vlen);
    for(int i=0; i<vlen; i++){
        for(int j=0; j<vlen; j++){
            v[i+j] += v1[i] * v2[j]; 
        }
    }

    return v;
}

void to_latex(vector<int> v){
    int vlen = v.size();

    cout<<"$";
    for(int i=0; i<vlen; i++){
        if(v[i] != 0){
            if(v[i] == 1){
                cout<<"x^"<<i;
            }
            else{
                cout<<v[i]<<"x^"<<i;
            }

            if(i < (vlen - 1)){
                cout<<"+";
            }     
        }
    }
    cout<<"$";
}

vector<int> derivative(vector<int> v){
    int vlen = v.size();

    vector<int> v_result(vlen-1);

    for(int i=0; i<vlen; i++){
        v_result[i] = (i+1) * v[i+1]; 
    }

    return v_result;
}

/* vector<vector<int>> integration(vector<int> v){
    int vlen = v.size();
    
    vector<vector<int>> v_result(vlen+1);

    v_result[0][0] = 0;
    v_result[0][1] = 0;
    for(int i=1; i<vlen+1; i++){
        v_result[i][0] = v[i-1];
        v_result[i][1] = i;
    }

    return v_result;
}

void to_latex_int(vector<vector<int>> v){
    int vlen = v.size();

    cout<<"$";
    for(int i=0; i<vlen; i++){
        if(v[i][0] != 0){
            if((v[i][0] == 1) and (v[i][1] == 1)){
                cout<<"x^"<<i;
            }
            else{
                cout<<"\frac{"<<v[i][0]<<"}{"<<v[i][1]<<"}"
                    <<"x^"<<i;
            }

            if(i<vlen-1){
                cout<<"+";
            }
        }
    }
    cout<<"$";
} */

vector<int> KA(vector<int> v1, vector<int> v2){

    int N = max(v1.size(), v2.size());
    vector<int> v_result(2*N-1, 0);

    if(N == 1){
        v_result[0] = v1[0] * v2[0]; 
        return v_result;
    }

    vector<int> v12(N/2,0), v22(N/2,0);
    vector<int> v11(N/2,0), v21(N/2,0);

    for(int i=0; i<(N/2); i++){
        v12[i] = v1[i];
        v22[i] = v2[i];
    }

    for(int i=0; i<(N/2); i++){
        v11[i] = v1[N/2 + i];
        v21[i] = v2[N/2 + i];
    }
    
    vector<int> D0 = KA(v12, v22);
    vector<int> D1 = KA(v11, v21);
    vector<int> D01 = KA(addition(v11, v12), addition(v21, v22));

    int len0 = D0.size(), len1 = D1.size(), len01 = D01.size();

    for(int i=0; i<len0; i++){
        v_result[i] += D0[i];
    }

    for(int i=0; i<len1; i++){
        v_result[i+N] += D1[i];
    }

    for(int i=0; i<len01; i++){
        v_result[i+(N/2)] += D01[i] - D0[i] - D1[i]; 
    }

    return v_result;    
}

int main(){

    vector<int> v1(4), v2(4);

    for(int i=0; i<4; i++){
        v1[i] = i+1;
        v2[i] = i+2;
    }

    vector<int> v = KA(v1, v2);

    to_latex(v);

    return 0;
}
