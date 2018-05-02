#include "monomial.hpp"

vector<int> add(vector<int> v1, vector<int> v2){
    int vlen = v1.size();

    vector<int> v(vlen);
    for(int i=0; i<vlen; i++){
        v[i] = v1[i] + v2[i];
    }

    return v;
}

class poly{
    private:
        monomial *ptr_end_mono;

    public:
        poly(){
            monomial *begin= new monomial(0, 0, 0, -1, 0);
            begin -> set_ptr(begin);
            ptr_end_mono = begin;
        }

        poly(int _coef, int pw_x, int pw_y, int pw_z){
            monomial *begin = new monomial(0, 0, 0, -1, 0);
            monomial *tmp = new monomial(_coef, pw_x, pw_y, pw_z, 1);

            begin -> set_ptr(tmp);
            tmp -> set_ptr(begin);

            ptr_end_mono = begin;
        }

        void show();
        monomial* get_zero_node();
};


void poly::show(){
    ptr_end_mono -> start_show();
}

monomial* poly::get_zero_node(){
    return ptr_end_mono; 
}

poly copy_poly(poly* _poly){
    monomial* p = _poly -> get_zero_node();
    poly poly_result;
    monomial* q = poly_result.get_zero_node();
    
    // A1 Initialize to highest order term
    p = p -> get_next_mono();
    monomial* q_1 = q;
    q = q -> get_next_mono();
    goto A2;
    // A2 Compare higest order terms
    A2:
        int comp = big_pw(p, q);
        if(comp == 2){
            q_1 = q; 
            q = q -> get_next_mono();
            goto A2;
        } else if(comp == 1){
            goto A3;
        } else if(comp == 0){
            // A5 
            int coef_q3 = p -> get_coef();
            vector<int> pw_q3 = p -> get_pw();
            monomial *q_3 = new monomial(coef_q3, pw_q3[0], pw_q3[1], pw_q3[2], 1);
            q_3 -> set_ptr(q);
            q_1 -> set_ptr(q_3);
            q_1 = q_3;
            p = p -> get_next_mono();
            goto A2;
        }
    // A3
    A3:
        if((p -> get_special()) == 0){
            return poly_result;
        } else {
            int coef_p = (p -> get_coef());
            int coef_q = (q -> get_coef());
            q -> set_coef(coef_p + coef_q);
        }

        if((q -> get_coef()) == 0){
            goto A4;
        } else {
            p = p -> get_next_mono();       
            q_1 = q; 
            q = q -> get_next_mono();
            goto A2;
        }
    // A4
    A4: 
        monomial* q_2 = q;
        q = q -> get_next_mono();
        q_1 -> set_ptr(q);
        delete q_2;
        p = p -> get_next_mono();
        goto A2;
}

poly poly_add(poly* poly_1, poly* poly_2){
    monomial* p = poly_1 -> get_zero_node();
    poly poly_result = copy_poly(poly_2);
    monomial* q = poly_result.get_zero_node();
    
    // A1
    p = p -> get_next_mono();
    monomial* q_1 = q;
    q = q -> get_next_mono();
    goto A2;
    // A2
    A2:
        int comp = big_pw(p, q);
        if(comp == 2){
            q_1 = q; 
            q = q -> get_next_mono();
            goto A2;
        } else if(comp == 1){
            goto A3;
        } else if(comp == 0){
            // A5
            int coef_q3 = p -> get_coef();
            vector<int> pw_q3 = p -> get_pw();
            monomial *q_3 = new monomial(coef_q3, pw_q3[0], pw_q3[1], pw_q3[2], 1);
            q_3 -> set_ptr(q);
            q_1 -> set_ptr(q_3);
            q_1 = q_3;
            p = p -> get_next_mono();
            goto A2;
        }
    // A3
    A3:
        if((p -> get_special()) == 0){
            return poly_result;
        } else {
            int coef_p = (p -> get_coef());
            int coef_q = (q -> get_coef());
            q -> set_coef(coef_p + coef_q);
        }

        if((q -> get_coef()) == 0){
            goto A4;
        } else {
            p = p -> get_next_mono();       
            q_1 = q; 
            q = q -> get_next_mono();
            goto A2;
        }
    // A4
    A4: 
        monomial* q_2 = q;
        q = q -> get_next_mono();
        q_1 -> set_ptr(q);
        delete q_2;
        p = p -> get_next_mono();
        goto A2;
} 

poly poly_mul(poly* poly_1, poly* poly_2){
    monomial *p = poly_1 -> get_zero_node();
    monomial *q = poly_2 -> get_zero_node();
    poly poly_result;

    
    // M1 initialize to highest order term
    p = p -> get_next_mono(); 
    q = q -> get_next_mono();

    // M2
    int tmp_coef;
    vector<int> tmp_pw;
    while((p -> get_special()) > 0){
        while((q -> get_special()) > 0){
            tmp_coef = (p -> get_coef()) * (q -> get_coef());
            tmp_pw = add((p -> get_pw()), (q -> get_pw()));
            poly tmp(tmp_coef, tmp_pw[0], tmp_pw[1], tmp_pw[2]);
            poly_result = poly_add(&poly_result, &tmp);

            q = q -> get_next_mono(); 
        }
        p = p -> get_next_mono();     
    }
    return poly_result;
}

int main(){
    poly a(1, 1, 0, 0);
    poly b(2, 0, 1, 0);

    poly c = poly_add(&a, &b);
    a.show();
    cout << endl;
    b.show();
    cout << endl;
    c.show();
    
    poly d = poly_mul(&a, &b);
    cout << endl;
    d.show();

    return 0;
}
