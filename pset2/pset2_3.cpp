#include <iostream>
#include <vector>

using namespace std;

class monomial{
    private:
        vector<int> pw;
        int special;
        int coef;
        monomial *ptr;

    public:
        void set_pw(int pw_x, int pw_y, int pw_z);
        void set_special(int special);
        void set_ptr(monomial next_mono);
        void get_pw();
        void get_coef();

};

void monomial::set_pw(int pw_x, int pw_y, int pw_z){
    pw.resize(3);
    pw[0] = pw_x;
    pw[1] = pw_y;
    pw[2] = pw_z;
}

void monomial::set_special(int spec){
    special = spec;
}

void monomial::set_ptr(monomial next_mono){
    ptr = &next_mono;
}

void monomial::get_pw(){
    cout << "power of x is: " << pw[0] << endl;
    cout << "power of y is: " << pw[1] << endl;
    cout << "power of z is: " << pw[2] << endl;
}

void monomial::get_coef(){
    cout << "coefficient of mono is: " << coef << endl;
}

int main(){
    monomial zero;
    monomial xyz;

    zero.set_special(0);
    zero.set_pw(0, 0, 1);
    zero.set_ptr(xyz);

    xyz.set_special(1);
    xyz.set_pw(1,1,1);
    xyz.set_ptr(zero);

    zero.get_pw();
    zero.get_coef();
    xyz.get_pw();
    xyz.get_coef();

    return 0;
}
