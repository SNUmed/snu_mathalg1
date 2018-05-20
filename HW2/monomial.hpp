#include <iostream>
#include <vector>
#include <gmpxx.h>

using namespace std;

class monomial{
    private:
        vector<int> pw;
        int special;
        mpq_class coef;
        monomial *next_mono;

    public:
        monomial(mpq_class _coef, int pw_x, int pw_y, int pw_z, int _special){
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
        void set_coef(mpq_class _coef);
        int get_special();
        monomial* get_next_mono();
        void start_show();
        void cont_show();
        vector<int> get_pw();
        mpq_class get_coef();
};

mpq_class monomial::get_coef(){
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

void monomial::set_coef(mpq_class _coef){
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
        if(coef > 0){
            cout << "+";
        }
        cout << coef; 
        if(pw[0] != 0){
            cout << "x^" << pw[0];
        }
        if(pw[1] != 0){
            cout << "y^" << pw[1];
        }
        if(pw[2] != 0){
            cout << "z^" << pw[2];
        }
        next_mono -> cont_show();
    } 
}

int big_pw(monomial* mono_1, monomial* mono_2){
    vector<int> pw_1 = mono_1 -> get_pw();
    vector<int> pw_2 = mono_2 -> get_pw();

    /*for(int i=0; i<3; i++){
        cout<<pw_1[i] << "," << pw_2[i]<<endl;
    }

    
    // if pw of two monomial are the same
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
    } */

    for(int i=0; i<3; i++){
        if(pw_1[i] > pw_2[i]){
            return 0;
        } else if(pw_1[i] < pw_2[i]){
            return 2;
        }
    }

    return 1;

    // not above two, mono_2 has larger pw
    //return 2;
}

int can_div(monomial* mono_1, monomial* mono_2){
    vector<int> pw_1 = mono_1 -> get_pw();
    vector<int> pw_2 = mono_2 -> get_pw();

    if(pw_1[0] >= pw_2[0]){
        if(pw_1[1] >= pw_2[1]){
            if(pw_1[2] >= pw_2[2]){
                return 1;
            }
        }
    }

    return 0;
}

vector<int> pw_diff(monomial* mono_1, monomial* mono_2){
    vector<int> pw_1 = mono_1 -> get_pw();
    vector<int> pw_2 = mono_2 -> get_pw();
    vector<int> contrast;
    contrast.resize(3);

    for(int i=0; i<3; i++){
        contrast[i] = pw_1[i] - pw_2[i];
    }

    return contrast;
}




