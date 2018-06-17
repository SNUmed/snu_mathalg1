#include <iostream>
#include <cmath>

using namespace std;

const int MaxOrder=260;

const int VarNode=1000;
const int ConstNode=1001;
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
        int type;
        int char_type; // char_type stores x or y 
        int info; // info stores power
        int coef; // store coef
        node *left;
        node *right;    


        // root node init
        node(){
            left=NULL;
            right=NULL;
            info=0;
            type=0;
            char_type=0;
            coef=0;
        }
            
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
            type = _type;
            coef = _coef;
            char_type = _char_type;
            info = _info;
        }

        // operation node init
        node(int _type, node* lhs, node* rhs){
            type = _type;
            left = lhs;
            right = rhs;
        }
        
        // delete node
        ~node(){
            if(left != NULL){
                delete left;
            }
            if(right != NULL){
                delete right;
            }
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

                case MultNode:
                    result = "(" + left -> print() + ") * ";
                    result += "(" + right -> print() + ")";
                    break;

                case DivNode:
                    result = "(" + left -> print() + ") / ";
                    result += "(" + right -> print() + ")";

                case SubNode:
                    result = "(" + left -> print() + ") - ";
                    result += "(" + right -> print() + ")";
                
                default:
                    break;
            }
            return result;
        }
};

// 지금 copy가 모든 정보를 카피하지 않음
node* copy(node* ptrNode){
    node *result = new node;
    *result = *ptrNode; 
    result -> info = ptrNode -> info;
    if(ptrNode -> left != NULL){
        result -> left = copy(ptrNode -> left);
    }
    if(ptrNode -> right != NULL){
        result -> right = copy(ptrNode -> right);
    }
    return result;
}

node* add(node* lhs, node* rhs){
    node* result = new node(AddNode, copy(lhs), copy(rhs));
    return result;
}

node* mult(node* lhs, node* rhs){
    node* result = new node(MultNode, copy(lhs), copy(rhs));
    return result;
}

node* div(node* lhs, node* rhs){
    node* result = new node(DivNode, copy(lhs), copy(rhs));
    return result;
}

node* sub(node* lhs, node* rhs){
    node* result = new node(SubNode, copy(lhs), copy(rhs));
    return result;
}

double eval(node* _node, double x_val, double y_val){
    double result; 
    // const val if const node
    if(_node -> type == ConstNode){
        result = _node -> coef;
    } // eval x or y if var node
    else if(_node -> type == VarNode){
        if(_node -> char_type == x){
            result = (_node -> coef) * pow(x_val, _node -> info);
        }
        else{ // not x than it must be y (may cause error?)
            result = (_node -> coef) * pow(y_val, _node -> info);
        } 
    } // operation nodes compute recursively 
    else{
        if(_node -> type == AddNode){
                result = eval(_node -> left, x_val, y_val) + eval(_node -> right, x_val, y_val);
        }
        else if(_node -> type == MultNode){
            result = eval(_node -> left, x_val, y_val) * eval(_node -> right, x_val, y_val);
        }
        else if(_node -> type == DivNode){
            result = eval(_node -> left, x_val, y_val) / eval(_node -> right, x_val, y_val);
        }
        else if(_node -> type == SubNode){
            result = eval(_node -> left, x_val, y_val) - eval(_node -> right, x_val, y_val);
        }
        else{ // not const, var, oper then just return 0
            result = 0;
        }
    }

    return result;
}

node* diff(node* ptrNode, int diff_var){
    node *result = new node;
    if(ptrNode -> type == ConstNode){
        *result = node();
    }








    /*if(ptrNode -> type == AddNode){
        result = add(diff((ptrNode -> left), diff_var), diff((ptrNode -> right), diff_var));
    }
    else if(ptrNode -> type == SubNode){
        result  = sub(diff((ptrNode -> left), diff_var), diff((ptrNode -> right), diff_var));   
    }
    else if(ptrNode -> type == MultNode){
        result = add(mult(diff(ptrNode -> left, diff_var), ptrNode -> right), mult(ptrNode -> left, diff(ptrNode -> right, diff_var)));
    }
    else if(ptrNode -> type == DivNode){
        result = mul(diff(ptrNode -> left))
    }*/
    
    
    return result;
}

#define X {new node(VarNode, 1, x, 1)}
#define Y {new node(VarNode, 1, y, 1)}

int main(){
    node *root;
    root = mult(add(Y, mult(X,Y)), X);
    cout << root -> print();
    cout << endl;
    cout << eval(root, 1, 2);
    return 0;
}
