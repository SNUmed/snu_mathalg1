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

        poly(mpq_class _coef, int pw_x, int pw_y, int pw_z){

            monomial *begin= new monomial(0, 0, 0, -1, 0);

            if((pw_x == 0) and (pw_y == 0) and (pw_z == 0)){
                begin -> set_ptr(begin);
                ptr_end_mono = begin;
            } else {
                monomial *tmp = new monomial(_coef, pw_x, pw_y, pw_z, 1);

                begin -> set_ptr(tmp);
                tmp -> set_ptr(begin);

                ptr_end_mono = begin;
            }
        }

        void show();
        int is_zero();
        monomial* get_zero_node();
};


void poly::show(){
    ptr_end_mono -> start_show();
}

int poly::is_zero(){
    if(ptr_end_mono -> get_special() == 0){
        return 1;
    } else {
        return 0;
    }
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
            mpq_class coef_q3 = p -> get_coef();
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
            mpq_class coef_p = (p -> get_coef());
            mpq_class coef_q = (q -> get_coef());
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
            mpq_class coef_q3 = p -> get_coef();
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
            mpq_class coef_p = (p -> get_coef());
            mpq_class coef_q = (q -> get_coef());
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

poly poly_minus(poly* poly_1, poly* poly_2){
    poly tmp = copy_poly(poly_2);
    monomial* q = tmp.get_zero_node();
    poly poly_result;

    // initialize to highest order term
    q = q -> get_next_mono();

    while((q -> get_special)() > 0){
        q -> set_coef((-1) * (q -> get_coef()));
        q = q -> get_next_mono();
    }

    poly_result = poly_add(poly_1, &tmp);
    return poly_result;
}

poly poly_mul(poly* poly_1, poly* poly_2){
    monomial *p = poly_1 -> get_zero_node();
    monomial *q = poly_2 -> get_zero_node();
    poly poly_result;

    
    // M1 initialize to highest order term
    p = p -> get_next_mono(); 
    q = q -> get_next_mono();

    // M2
    mpq_class tmp_coef;
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


poly poly_rem(poly* poly_1, poly* poly_2){
    monomial *p = poly_1 -> get_zero_node();
    monomial *q = poly_2 -> get_zero_node();
    poly poly_result;

    // initialize to highest order term
    p = p -> get_next_mono();
    q = q -> get_next_mono();
    
    if(can_div(p, q) == 1){
        // get coef
        mpq_class p_coef, q_coef, tmp_coef;
        p_coef = p -> get_coef();
        q_coef = q -> get_coef();
        tmp_coef = p_coef / q_coef;

        // get pw
        vector<int> tmp_pw = pw_diff(p, q);

        // tmp = p/q
        poly tmp(tmp_coef, tmp_pw[0], tmp_pw[1], tmp_pw[2]);

        // make something to substract
        poly tmp_sub = poly_mul(&tmp, poly_2);

        poly_result = poly_minus(poly_1, &tmp_sub);

    } else {
        // if p has smaller order than q, return p
        poly_result = copy_poly(poly_1);
    }

    return poly_result;
}

mpq_class max_q(mpq_class q_1, mpq_class q_2){
    if(q_1 >= q_2){
        return q_1;
    } else{
        return q_2;
    }
}

/*poly s_poly(poly* poly_1, poly* poly_2){
    // get the leading term of both
    // 
}*/


int main(){
    // a = xy^2
    poly a(1, 1, 2, 0);

    // b = y^2 - y
    poly b(1, 0, 2, 0);
    poly* c = new poly(-1, 0, 1, 0);
    b = poly_add(&b, c);
    delete c;

    /*a.show();
    cout << endl;
    b.show();
    cout << endl; */

    // d = xy
    poly d = poly_rem(&a, &b);
    d.show();
    cout << endl;

    return 0;
}
