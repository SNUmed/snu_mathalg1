#include "poly.hpp"
#include <set>

set<poly> buchberger_fat(set<poly>* _pre_basis){
    set<poly> basis = *_pre_basis;
    vector<poly> pair;
    pair.resize(2);
    set< vector<poly> > pairs;

    set<poly>::iterator row_it, col_it;
    for(row_it = _pre_basis -> begin(); row_it != _pre_basis -> end(); ++row_it){
        for(col_it = _pre_basis -> begin(); col_it != _pre_basis -> end(); ++col_it){
            if(row_it != col_it){
                pair[0] = (*row_it);
                pair[1] = (*col_it);            
                pairs.insert(pair);
            }
        }
    }

    set< vector<poly> >::iterator pair_it;
    set<poly>::iterator pre_it;
    poly fat_s, poly_1, poly_2, poly_pre;
    for(pair_it = pairs.begin(); pair_it != pairs.end(); ++pair_it){
        poly_1 = (*pair_it)[0];
        poly_2 = (*pair_it)[1];
        fat_s = s_poly(&poly_1, &poly_2); 

        for(pre_it = _pre_basis -> begin(); pre_it != _pre_basis -> end(); ++pre_it){
            poly_pre = *pre_it;
            fat_s = poly_rem(&fat_s, &poly_pre);
        }

        if(poly_empty(&fat_s) == false){
            basis.insert(fat_s);    
        }
    }

    return basis;    
}

set<poly> buchberger_red(set<poly>* _fat_basis){
    set<poly> basis;
    set<poly>::iterator it_row, it_col;
    poly fat_element, div_element;
    
    for(it_row = _fat_basis -> begin(); it_row!= _fat_basis -> end(); ++it_row){
        fat_element = *it_row; 
        for(it_col = _fat_basis -> begin(); it_col != it_row; ++it_col){
            div_element = *it_col;
            fat_element = poly_rem(&fat_element, &div_element);

        }
        basis.insert(fat_element);
    }
    
    return basis;
}


int main(){
    
    // due to some unknown reason, comparison between set<poly> is not working.
    // although I defined operator == in the polynomial properly(it seems to work well when testing for quite a lot of examples)
    // so performing "while" until the basis and the reduced basis are equal is not working.
    // therefore, as an incomplete solution, increase n untill the program end up to a reduced basis 
    int n = 10;

    set<poly> pre_basis;
    set<poly>::iterator b_it;
//    pre_basis.insert(poly(1,2,0,0) + poly(1,0,2,0) + poly(1,0,0,2) + poly(-1,0,0,0));
//    pre_basis.insert(poly(1,3,0,0) + poly(1,2,0,0) + poly(-1,0,2,0) + poly(-1,0,0,2));
//    pre_basis.insert(poly(1,2,1,0) + poly(-2,0,0,0));
//    pre_basis.insert(poly(1,1,2,0) + poly(-1,0,1,0));

    pre_basis.insert(poly(1,2,0,0) + poly(-1, 0,1,0));
    pre_basis.insert(poly(1,3,0,0) + poly(-1, 1,0,0));

    set<poly> basis = buchberger_fat(&pre_basis);
    for(b_it = basis.begin(); b_it != basis.end(); ++b_it){
        (*b_it).show();
        cout << endl;
    }
    
    cout << "---------------" << endl;
    set<poly> basis_red = buchberger_red(&basis);
    for(b_it = basis_red.begin(); b_it != basis_red.end(); ++b_it){
        (*b_it).show();
        cout << endl;
    }
    
    basis = basis_red;
    for(int i=0; i<n; i++){
        cout << "---------------" << endl;
        basis = basis_red;
        basis_red = buchberger_red(&basis);

        //print reduced basis
        for(b_it = basis_red.begin(); b_it != basis_red.end(); ++b_it){
            (*b_it).show();
            cout << endl;
        }
    }

    return 0;
}
