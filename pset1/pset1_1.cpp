#include <iostream>

using namespace std;

int Euclid(int a, int b){

    int r;
    if (a < b){
        return Euclid(b,a);
    }

    r = a%b;
    if (r == 0){
        return b;
    } else {
        return Euclid(b,r);
    }
    
}

int main(){
    int a, b;
    cout << "input numbers:" <<endl;
    cin >> a >> b;
    cout<<"The greatest common divisor is :"<<Euclid(a,b);

    return 0;
}
