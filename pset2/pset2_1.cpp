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

vector<vector<int>> integration(vector<int> v){
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
}
