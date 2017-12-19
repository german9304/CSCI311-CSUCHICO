
#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;


void RBTree::rbPrintTree(){
    Node * x = root;
    reverseInOrderPrint(x, 0);
}
void RBTree::reverseInOrderPrint(Node *x, int depth) {
    if ( x != nil ) {
        reverseInOrderPrint(x->right, depth+1);
        cout << setw(depth*4+4) << x->color << " ";
        cout << *(x->key) << " " << *(x->value) << endl;
        reverseInOrderPrint(x->left, depth+1);
    }
}


RBTree::Node::Node(){
    parent=nullptr;
    left=nullptr;
    right=nullptr;
    color='B';
    key=nullptr;
    value =nullptr;
}
RBTree::Node::~Node(){
    delete value;
    delete key;
}
RBTree::~RBTree(){
  Node * x = root;
   //clean(x);
   delete nil;
}

void RBTree::clean(Node *x){
    if(x==nil){
        return;
    }
    clean(x->left);
    clean(x->right);
    delete x;
}

RBTree::RBTree(){
    nil=new Node();
    root=nil;
}

/*******
 Insert , Insert  Fix up
 *******/
void RBTree::rbInsert(const string& key, const string& value){
    Node * z = new Node();
    z->key=new string(key);
    z->value=new string(value);
    rbInsert(z);
}

void RBTree::rbInsert(Node* z){
    Node * y = nil;
    Node * x = root;
    while(x!=nil){
        y=x;
        if(*(z->key)<*(x->key)){
            x=x->left;
        }else{
            x=x->right;
        }
    }
    z->parent=y;
    if(y==nil){
        root = z;
    }else if(*(z->key)<*(y->key)){
        y->left =z;
    }else{
        y->right=z;
    }
    z->left=nil;;
    z->right=nil;
    z->color='R';
    rbInsertFixup(z);

}

void RBTree::rbInsertFixup(Node* x){

    Node * y=nullptr;
    while(x->parent->color=='R'){
        if(x->parent==x->parent->parent->left){
            y=x->parent->parent->right;
            if(y->color=='R'){
                x->parent->color='B';
                y->color='B';
                x->parent->parent->color='R';
                x=x->parent->parent;
            }else{
                if(x==x->parent->right){
                    x=x->parent;
                    leftRotate(x);
                }
                x->parent->color='B';
                x->parent->parent->color='R';
                rightRotate(x->parent->parent);
            }
        }else{
            y=x->parent->parent->left;
            if(y->color=='R'){
                x->parent->color='B';
                y->color='B';
                x->parent->parent->color='R';
                x=x->parent->parent;
            }else{
                if(x==x->parent->left){
                x=x->parent;
                rightRotate(x);
               }
                x->parent->color='B';
                x->parent->parent->color='R';
                leftRotate(x->parent->parent);//h
           }
        }
    }
     root->color='B';
}


/*******
 Search, Find
 *******/
vector<const string*> RBTree::rbFind(const string& key){

Node * xroot = root;
vector<const string *> av;

Node * search = rbTreeSearch(xroot, key);
    if(search!=nil){
    av.push_back(search->value);

    Node* pred=nullptr;
    Node * succ=nullptr;
    Node * succ_Pr=search;
    Node * succ_Su=search;
    while(pred!=nil || succ!=nil){
        succ= rbTreeSuccessor(succ_Su);
        if(succ!=nil){
        if(*(succ->key)==key){
            av.push_back(succ->value);
            succ_Su=succ;

        }else{
            succ=nil;
         }
        }
        pred =rbTreePredecessor(succ_Pr);
        if(pred!=nil){
        if(*(pred->key)==key){
            av.push_back(pred->value);
            succ_Pr=pred;
        }else{
            pred=nil;
        }
      }

     }
    }

    return av;
}

RBTree::Node* RBTree::rbTreeSearch(Node* x, const string& Key){

    while(x!=nil && Key!=*(x->key)){
        if(Key<*(x->key)){
            x= x->left;
        }else{
            x= x->right;
        }
    }

    return x;
}

/*******
 Delete , Delete Fix up
 *******/
void RBTree::rbDelete(const string& key, const string& value){
    Node * xr = root;
    Node * z = rbTreeSearch(xr, key);

    while(z!=nil && *(z->value)==value){
    rbDelete(z);
    z = rbTreeSearch(root, key);
    }

    Node* pred=nullptr;
    Node * succ=nullptr;

    if(z!=nil){
    Node * succ_Pr=z;
    Node * succ_Su=z;
    while(pred!=nil || succ!=nil){

        succ= rbTreeSuccessor(succ_Su);
        if(succ!=nil){
            if(*(succ->key)==key){
               if( *(succ->value)==value){
                rbDelete(succ);
              }
                succ_Su=succ;
            }else{
                succ=nil;
            }

        }
        pred =rbTreePredecessor(succ_Pr);
        if(pred!=nil){
            if(*(pred->key)==key){
                 if( *(pred->value)==value){
                 rbDelete(pred);
              }
                succ_Pr=pred;
            }else{
                pred=nil;
            }
        }
     }
    }
}

void RBTree::rbDelete(Node * z){
    Node * x=nullptr;
    Node * y = z;
    char y_OriginalColor = z->color;
        if(z->left==nil){
            x = z->right;
            rbTransplant(z,z->right);
        }else if(z->right==nil){
            x = z->left;
            rbTransplant(z,z->left);
        }else{
            y = rbTreeMaximum(z->left);
            y_OriginalColor = y->color;
            x=y->left;
            if(y->parent==z){
                x->parent=y;
            }else{
                rbTransplant(y, y->left);
                y->left=z->left;
                y->left->parent=y;
            }//else
            rbTransplant(z, y);
            y->right=z->right;
            y->right->parent=y;
            y->color=z->color;
        }//else

        if(y_OriginalColor=='B'){
            rbDeleteFixup(x);
        }
}

void RBTree::rbDeleteFixup(Node* x){
    Node * w=nullptr;
    while(x!=root && x->color=='B'){
        if(x==x->parent->left){
            w=x->parent->right;
            if(w->color=='R'){
                w->color='B';
                x->parent->color='R';
                leftRotate(x->parent);
                w=x->parent->right;
            }
            if(w->left->color=='B' && w->right->color=='B'){
                w->color='R';
                x=x->parent;
            }else{
                 if(w->right->color=='B'){
                    w->left->color='B';
                    w->color='R';
                    rightRotate(w);
                    w=x->parent->right;
            }
                w->color=x->parent->color;
                x->parent->color='B';
                w->right->color='B';
                leftRotate(x->parent);
                x=root;
            }
        }else{
            w=x->parent->left;
            if(w->color=='R'){
                w->color='B';
                x->parent->color='R';
                rightRotate(x->parent);
                w=x->parent->left;
            }
            if(w->right->color=='B' && w->left->color=='B'){
                w->color='R';
                x=x->parent;
            }else{
                  if(w->left->color=='B'){
                    w->right->color='B';
                    w->color='R';
                    leftRotate(w);
                    w=x->parent->left;
            }
                w->color=x->parent->color;
                x->parent->color='B';
                w->left->color='B';
                rightRotate(x->parent);
                x=root;
            }
        }
    }
    x->color='B';
}


RBTree::Node* RBTree::rbTreeMinimum(Node* x){
    while(x->left!=nil){
        x=x->left;
    }
    return x;
}
RBTree::Node* RBTree::rbTreeMaximum(Node* x){

    while(x->right!=nil){
        x=x->right;
    }
    return x;
}

RBTree::Node* RBTree::rbTreeSuccessor(Node* x){
    if(x->right!=nil){
        return rbTreeMinimum(x->right);
    }
    Node * y = x->parent;
    while(y!=nil && x == y->right){
        x =y;
        y= y->parent;
    }
    return y;
}

RBTree::Node* RBTree::rbTreePredecessor(Node* x){
    if(x->left!=nil){
        return rbTreeMaximum(x->left);
    }
    Node * y = x->parent;
    while(y!=nil && x == y->left){
        x =y;
        y= y->parent;
    }
    return y;
}



void RBTree::leftRotate(Node* x){
    Node * y = x->right;
    x->right=y->left;
    if(y->left!=nil){
        y->left->parent=x;
    }
    y->parent=x->parent;
    if(x->parent==nil){
        root=y;
    }else if(x==x->parent->left){
        x->parent->left=y;
    }else{
        x->parent->right=y;
    }
    y->left=x;
    x->parent=y;
}
void RBTree::rightRotate(Node* x){
    Node * y = x->left;
    x->left=y->right;
    if(y->right!=nil){
        y->right->parent=x;
    }
    y->parent=x->parent;
    if(x->parent==nil){
        root=y;
    }else if(x==x->parent->right){
        x->parent->right=y;
    }else{
        x->parent->left=y;
    }
    y->right=x;
    x->parent=y;

}

void RBTree::rbTransplant(Node* x, Node* y){
    if(x->parent==nil){
        root=y;
    }else if(x==x->parent->left){
        x->parent->left=y;
    }else{
        x->parent->right=y;
    }
    y->parent=x->parent;

}
