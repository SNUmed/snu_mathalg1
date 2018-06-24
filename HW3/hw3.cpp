#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

const int MaxOrder=260;

const int ZeroNode=0;
const int ConstNode=1000;
const int VarNode=1001;
const int AddNode=1002;
const int MultNode=1003;
const int DivNode=1004;
const int SubNode=1005;

const int PowerNode=1010;
const int MonomialNode=1020;

const int x=1;
const int y=2;

int fact(int n){
    if(n<=1){
        return 1;
    }
    else{
        return n*fact(n-1);
    }
}

class Timer // Just for performance test
{
    // make things readable
    using clk = std::chrono::steady_clock;

    clk::time_point b; // begin
    clk::time_point e; // end

public:
    void clear() { b = e = clk::now(); }
    void start() { b = clk::now(); }
    void stop() { e = clk::now(); }

    friend std::ostream& operator<<(std::ostream& o, const Timer& timer)
    {
        return o << timer.secs();
    }

    // return time difference in seconds
    double secs() const
    {
        if(e <= b)
            return 0.0;
        auto d = std::chrono::duration_cast<std::chrono::microseconds>(e - b);
        return d.count() / 1000000.0;
    }
};

class node{
    public:
        int type = ZeroNode;
        int char_type = 0; // char_type stores x or y 
        int info = 0; // info stores power
        int coef = 0; // store coef
        node *left = NULL;
        node *right = NULL;    


        // root/empty node init
        node(){}
            
        // const node init
        node(int _type, int _coef){
            if(_coef == 0){
                node();
            }
            else{
                type = _type;
                coef = _coef;
            }
        }

        // var node init
        node(int _type, int _coef, int _char_type, int _info){
            if(_coef == 0){
                node();
            }
            else{
                type = _type;
                coef = _coef;
                char_type = _char_type;
                info = _info;
            }
        }

        // operation node init
        node(int _type, node* lhs, node* rhs){
            type = _type;
            left = lhs;
            right = rhs;
            coef = -1;
        }
        
        // delete node
        /*~node(){
            // cout << "node destructed" << endl;
            if(left != NULL){
                delete left;
            }
            if(right != NULL){
                delete right;
            }
        }*/
       
        // copy function 
        static node* copy(const node& _node){
            node *result = new node();
            *result = _node;
            if(_node.left != NULL){
                result -> left = copy(*(_node.left));
            }
            if(_node.right != NULL){
                result -> right = copy(*(_node.right));
            }
            return result;
        }

        // add, mult, sub, div operators
        node operator+(const node& _node){
            node result = node(AddNode, copy(*this), copy(_node));
            if((this -> coef) * (_node.coef) == 0){
                if((this->coef) + (_node.coef) == 0){
                    result = node();
                }
                else if((this->coef) != 0){
                    result = *this;
                }
                else{
                    result = _node;
                }
            }
            if((this -> type) == (_node.type)){
                if((this -> type) <= 1001){
                    if((this -> char_type) == (_node.char_type)){
                        if((this -> coef) + (_node.coef) == 0){
                        result = node();
                        }
                    }
                }
            }
            return result;
        }

        node operator*(const node& _node){
            node result = node(MultNode, copy(*this), copy(_node));
            if((this -> coef) * (_node.coef) == 0){
                result = node();
            }
            return result;
        }
        
        node operator-(const node& _node){
            node result = node(SubNode, copy(*this), copy(_node));
            if((this -> coef) * (_node.coef) == 0){
                if((this->coef) + (_node.coef) == 0){
                    result = node();
                }
                else if((this->coef) != 0){
                    result = *this;
                }
                else{
                    result = _node;
                }
            }
            if((this -> type) == (_node.type)){
                if((this -> type) <= 1001){
                    if((this -> char_type) == (_node.char_type)){
                        if((this -> coef) - (_node.coef) == 0){
                        result = node();
                        }
                    }
                }
            }
            return result;
        }

        node operator/(const node& _node){
            node result = node(DivNode, copy(*this), copy(_node));
            if((this -> coef) ==0){
                result = node();
            }
            return result;
        }
        
        // print node
        string print(){
            string result = "";
            switch(type){
                case ConstNode:
                    result = to_string(coef);

                case VarNode:
                    if(char_type == x){
                        result = to_string(coef) + "x^" + to_string(info);
                    }
                    if(char_type == y){
                        result = to_string(coef) + "y^" + to_string(info);
                    }
                    break;

                case AddNode:
                    result = "(" + left -> print() + ") + ";
                    result += "(" + right -> print() + ")";
                    break;

                case SubNode:
                    result = "(" + left -> print() + ") - ";
                    result += "(" + right -> print() + ")";
                    break;

                case MultNode:
                    result = "(" + left -> print() + ") * ";
                    result += "(" + right -> print() + ")";
                    break;

                case DivNode:
                    result = "(" + left -> print() + ") / ";
                    result += "(" + right -> print() + ")";
                                
                default:
                    break;
            }
            return result;
        }
};

double eval(const node& _node, double x_val, double y_val){
    double result; 
    // const val if const node
    if(_node.type == ConstNode){
        result = _node.coef;
    } // eval x or y if var node
    else if(_node.type == VarNode){
        if(_node.char_type == x){
            result = (_node.coef) * pow(x_val,_node.info);
        }
        else{ // not x than it must be y (may cause error?)
            result = (_node.coef) * pow(y_val,_node.info);
        } 
    } // operation nodes compute recursively 
    else{
        if(_node.type == AddNode){
            result = eval(*(_node.left), x_val, y_val) + eval(*(_node.right), x_val, y_val);
        }
        else if(_node.type == MultNode){
            result = eval(*(_node.left), x_val, y_val) * eval(*(_node.right), x_val, y_val);
        }
        else if(_node.type == DivNode){
            result = eval(*(_node.left), x_val, y_val) / eval(*(_node.right), x_val, y_val);
        }
        else if(_node.type == SubNode){
            result = eval(*(_node.left), x_val, y_val) - eval(*(_node.right), x_val, y_val);
        }
        else{ // not const, var, oper then just return 0
            result = 0;
        }
    }

    return result;
}

node diff(const node& _node, int var){
    node result = node();
    // constant to zero
    if((_node.type == ConstNode) or (_node.type == ZeroNode)){
        // do nothing return will be at the end
    }
    else{
        if(_node.type == VarNode){
            // D on same variable
            if(_node.char_type == var){
                if(_node.info == 1){
                    result = node(ConstNode, _node.coef);
                }
                else{
                    result = node(VarNode, _node.info * _node.coef, _node.char_type, _node.info - 1);
                }
            }
            return result;
        }
        else{
            if(_node.type == AddNode){
                result = diff(*(_node.left), var) + diff(*(_node.right), var);  
            }
            else if(_node.type == MultNode){
                result = diff(*(_node.left), var) * (*(_node.right))
                    + (*(_node.left)) * diff(*(_node.right), var);
            }
            else if(_node.type == SubNode){
                result = diff(*(_node.left), var) - diff(*(_node.right), var);
            }
            else{
                result = (diff(*(_node.left), var) * (*(_node.right))
                    - (*(_node.left)) * diff(*(_node.right), var))
                    / ((*(_node.right)) * (*(_node.right)));
            }
        }
    }
    return result;
}

double rev(const node& _node, int var, double x_val, double y_val){
    double result = 0;
    // constant to zero
    if((_node.type == ConstNode) or (_node.type == ZeroNode)){
        // do nothing return will be at the end
    }
    else{
        if(_node.type == VarNode){
            result = eval(diff(_node, var), x_val, y_val); 
            return result;
        }
        else{
            if(_node.type == AddNode){
                result = rev(*(_node.left), var, x_val, y_val) + rev(*(_node.right), var, x_val, y_val);  
            }
            else if(_node.type == MultNode){
                result = rev(*(_node.left), var, x_val, y_val) * eval(*(_node.right), x_val, y_val)
                    + eval(*(_node.left), x_val, y_val) * rev(*(_node.right), var, x_val, y_val);
            }
            else if(_node.type == SubNode){
                result = rev(*(_node.left), var, x_val, y_val) - rev(*(_node.right), var, x_val, y_val);            
            }
            else{
                result = (rev(*(_node.left), var, x_val, y_val) * eval(*(_node.right), x_val, y_val)
                    - eval(*(_node.left), x_val, y_val) * rev(*(_node.right), var, x_val, y_val))
                    / pow(eval(*(_node.right), x_val, y_val), 2);
            }
        }
    }
    return result;
}

vector<double> grad_rev(const node& _node, double x_val, double y_val){
    vector<double> result;
    result.resize(2);
    result[0] = rev(_node, x, x_val, y_val);
    result[1] = rev(_node, y, x_val, y_val);
    return result;
}

class dual{
    public:
        vector<long double> vec;

        dual(){}

        dual(vector<long double> _vec){
            vec = _vec;
        }

        // operator overload
        dual operator+(const dual& _dual){
            dual result;
            result.vec = vec;
            int len = vec.size();
            for(int i=0; i<len; i++){
                result.vec[i] += _dual.vec[i];
            }

            return result;
        }

        dual operator*(const dual& _dual){
            dual result;
            int len = vec.size();
            result.vec.resize(len, 0);
            for(int i=0; i<len; i++){
                for(int j=0; j<=i; j++){
                    result.vec[i] += vec[i-j] * _dual.vec[j];
                }
            }
            return result;
        }

        dual operator-(const dual& _dual){
            dual result;
            result.vec = vec;
            int len = vec.size();
            for(int i=0; i<len; i++){
                result.vec[i] -= _dual.vec[i]; 
            }

            return result;
        }        

        dual operator/(const dual& _dual){
            dual result;
            result.vec = vec;
            int len = vec.size();
            result.vec[0] = result.vec[0] / _dual.vec[0];
            for(int i=1; i<len; i++){
                for(int j=1; j<=i; j++){
                    result.vec[i] -= _dual.vec[j]*result.vec[i-j];
                }
                result.vec[i] = result.vec[i] / _dual.vec[0];
            }
            return result;
        }

        // print method
        string print(){
            //using iterator do printing
            string result = "(";
            vector<long double>::iterator it;
            for(it = vec.begin(); it != vec.end(); ++it){
                result += to_string(*it);
                result += ",";
            }
            
            result.pop_back();
            result += ")";

            return result;
        }
};

// real mult
dual rmult(long double c, const dual& _dual){
    dual result;
    int len = _dual.vec.size();
    for(int i=0; i<len; i++){
        result.vec[i] = _dual.vec[i] * c;
    }
    return result;
}

// pow
dual pow(const dual& _dual, int n){
    if(n == 1){
        return _dual;
    }
    else{
        return pow(_dual, n-1) * _dual;
    }
}

dual fwd(const node& _node, dual _dual){
    dual result;
    // constant to zero
    if((_node.type == ConstNode) or (_node.type == ZeroNode)){
        result.vec = vector<long double>(_dual.vec.size(), 0); 
        result.vec[0] = _node.coef;
    }
    else{
        if(_node.type == VarNode){
            result = pow(_dual, _node.info);
        }
        else{
            if(_node.type == AddNode){
                result = fwd(*(_node.left), _dual) + fwd(*(_node.right), _dual);
            }
            else if(_node.type == MultNode){
                result = fwd(*(_node.left), _dual) * fwd(*(_node.right), _dual);
            }
            else if(_node.type == SubNode){
                result = fwd(*(_node.left), _dual) - fwd(*(_node.right), _dual);
            }
            else{
                result = fwd(*(_node.left), _dual) / fwd(*(_node.right), _dual);
            }
        }
    }

    // node type polynomial -> vec[i] = fact(order)/fact(order-i) * 적당히
    
    return result;
}



int main(){
    /*
    // X for x^1, Y for y^1
    node X = node(VarNode, 1, x, 1);
    node Y = node(VarNode, 1, y, 1);
    // symbolic derivative test
    cout << diff(X*X+Y*Y, x).print() << endl;
    // reverse AD
    vector<double> vec = grad_rev((X*X+Y*Y), 1, 2);
    cout << vec[0] << "," << vec[1] << endl;
    // H = x^2+y^3-y^2, problem (4)
    node H = (X*X) + (Y*Y*Y) - (Y*Y);
    // roundH/roundx
    cout << diff(H, x).print() << endl;
    // roundH/roundy
    cout << diff(H, y).print() << endl;
    // reverse AD of H on (0,1)
    vector<double> gradH = grad_rev(H, 0, 1);
    cout << gradH[0] << ',' << gradH[1] << endl;
    */
    vector<long double> a(4), b(4);
    a[0]=1; a[1]=0; a[2]=0; a[3]=0;
    b[0]=1; b[1]=1; b[2]=0; a[3]=0;
    dual da(a), db(b);
    dual c = da / db;
    cout << c.print() << endl;

}
