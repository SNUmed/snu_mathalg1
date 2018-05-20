#include "poly.hpp"
#include <set>

set<poly> buchberger(set<poly>* _pre_basis){
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

int main(){
    set<poly> pre_basis;
    set<poly>::iterator b_it;
    pre_basis.insert(poly(1,2,0,0) + poly(1,0,2,0) + poly(1,0,0,2) + poly(-1,0,0,0));
    pre_basis.insert(poly(1,3,0,0) + poly(1,2,0,0) + poly(-1,0,2,0) + poly(-1,0,0,2));
//    pre_basis.insert(poly(1,2,1,0) + poly(-2,0,0,0));
 //   pre_basis.insert(poly(1,1,2,0) + poly(-1,0,1,0));

//    for(b_it = pre_basis.begin(); b_it != pre_basis.end(); ++b_it){
//        (*b_it).show();
//        cout << endl;
//    }

    set<poly> basis = buchberger(&pre_basis);
    for(b_it = basis.begin(); b_it != basis.end(); ++b_it){
        (*b_it).show();
        cout << endl;
    }
    
    

    /*poly a = poly(1,2,0,0) + poly(1,0,2,0) + poly(1,0,0,2) + poly(-1,0,0,0);
    poly b = poly(1,3,0,0) + poly(1,2,0,0) + poly(-1,0,2,0) + poly(-1,0,0,2); */
    
    /*poly a = poly(1,2,1,0) + poly(-2,0,0,0);
    poly b = poly(1,1,2,0) + poly(-1,0,1,0);
    
    cout << "---------------------" << endl;

    cout << (b<a) << endl; */

    return 0;
}
