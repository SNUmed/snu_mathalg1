#include <iostream>
#include <vector>

using namespace std;

class monomial{
    private:
        vector<int> pw;
        int special;
        int coef;
        monomial *next_mono;

    public:
        monomial(int _coef, int pw_x, int pw_y, int pw_z, int _special){
            pw.resize(3);
            coef = _coef;
            pw[0] = pw_x;
            pw[1] = pw_y;
            pw[2] = pw_z;
            special = _special;
        }

        void set_pw(int pw_x, int pw_y, int pw_z);
        void set_special(int _spec);
        void set_ptr(monomial* _next_mono);
        void set_coef(int _coef);
        int get_special();
        monomial* get_next_mono();
        void start_show();
        void cont_show();
        vector<int> get_pw();
        int get_coef();
};

int monomial::get_coef(){
    return coef;
}

vector<int> monomial::get_pw(){
    return pw; 
}

void monomial::set_pw(int pw_x, int pw_y, int pw_z){
    pw.resize(3);
    pw[0] = pw_x;
    pw[1] = pw_y;
    pw[2] = pw_z;
}

void monomial::set_special(int _spec){
    special = _spec;
}

void monomial::set_ptr(monomial* _next_mono){
    next_mono = _next_mono;
}

void monomial::set_coef(int _coef){
    coef = _coef; 
}

int monomial::get_special(){
    return special; 
}

monomial* monomial::get_next_mono(){
    return next_mono;   
}

void monomial::start_show(){
    next_mono -> cont_show();
}

void monomial::cont_show(){
    if(special == 1){
        cout << coef 
        << "x^" << pw[0]
        << "y^" << pw[1]
        << "z^" << pw[2];
        if((next_mono -> get_special()) == 1){
            cout << "+";
        }
        next_mono -> cont_show();
    } else {
        cout << endl << "finished";
    }
}

int big_pw(monomial* mono_1, monomial* mono_2){
    vector<int> pw_1 = mono_1 -> get_pw();
    vector<int> pw_2 = mono_2 -> get_pw();


    // if pw of two monomial are same
    if(pw_1 == pw_2){
        return 1;
    }
    
    // check whether mono_1 has larger pw
    if(pw_1[0] > pw_2[0]){
        return 0;
    } else {
        if(pw_1[1] > pw_2[1]){
            return 0;
        } else {
            if (pw_1[2] > pw_2[2]){
                return 0;
            }
        }
    }
    
    // not above two, mono_2 has larger pw
    return 2;
}
