#include <iostream>
#include <cmath>

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

int main(){
    node X = node(VarNode, 1, x, 1);
    node Y = node(VarNode, 1, y, 1);
    node W = node();
    node Z = diff(X-(X/X), x);
    cout << Z.print() << endl;
    return 0;
}
