/**
@File
rbtree.cpp
@Author German Razo Rodriguez
@Date 04/29/2017
*/
#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;

/**
@Description
  This function calls the function reverseInOrderPrint tree walk,
  and that prints each node on a line.
  @param none
  @return none
 */
void RBTree::rbPrintTree(){
  Node * x = root;
  reverseInOrderPrint(x, 0);
}
/**
@Description
This function does a reverse in-order (go right, print, go left) tree walk,
and prints each node on a line.
@param x this parameter gets a node of the tree.
@param depth this parameter gets the depth of the tree.
 */
void RBTree::reverseInOrderPrint(Node *x, int depth) {
    if ( x != nil ) {
        reverseInOrderPrint(x->right, depth+1);
        cout << setw(depth*4+4) << x->color << " ";
        cout << *(x->key) << " " << *(x->value) << endl;
        reverseInOrderPrint(x->left, depth+1);
    }
}
/*
@Description
Node constructor
@return none
*/
RBTree::Node::Node(){
    parent=nullptr;
    left=nullptr;
    right=nullptr;
    color='B';
    key=nullptr;
    value =nullptr;
}
/*
@Description
Node destructor
@return none
*/
RBTree::Node::~Node(){
    delete value;
    delete key;
}
/*
@Description
RBTree constructor
initializes the one nil node 
created the nil node
@return none
*/
RBTree::RBTree(){
    nil=new Node();
    root=nil;
}
/*
@Description
RBTree destructor
@return none
*/
RBTree::~RBTree(){
  Node * x = root;
  clean(x);
  delete nil;
}
/**
 @Description
  This function checks if the current node is empty/null
  It traverse the left subtree,
   by calling the post-order function.
  It Traverse the right subtree,
  by recursively calling the post-order function.
  and it frees the node from memory calling delete at the node.
 @param x it accepts a node as a parameter.
 */
void RBTree::clean(Node *x){
  if(x==nil){
    return;
  }
  clean(x->left);
  clean(x->right);
  delete x;
}
/**
@Brief
  This function calls function creates a new node in the heap
  and sets its key and value.
  After setting the new node it calls the function rbInsert
  and it passes the newly created to node to rbInsert.
@param key This is the key value passed from main.
@param value This is the value passed from main.
@return none
*/
void RBTree::rbInsert(const string& key, const string& value){
  Node * z = new Node(); //newly created node
  z->key=new string(key);
  z->value=new string(value);
  rbInsert(z);
}
/**
@Brief This function inserts the newly created node z in the tree.
  It compares its key with the other nodes in the tree startng at the root
  to place it in its correct position.
  if node key is greater than the current key node,
  the node is placed to left of the current node, if it is smaller
  it is placed to the right of current the node.
  After the node is placed in its correct position,
  it points its left and right node to nil.
  It also sets the color of the node, red color.
  At the end,
  this function calls the function rbInsertFixup to fix up the tree.
@param z this is the newly created node passed from rbInsert
@return none
 */
void RBTree::rbInsert(Node* z){
  Node * y = nil;//nil node
  Node * x = root;//root of the tree
  while(x!=nil){
    y=x;
    if(*(z->key)<*(x->key)){
      x=x->left;
    }else{
      x=x->right;
    }//else
  }//while
  z->parent=y;//sets node parent
  if(y==nil){
    root = z;//sets root
  }else if(*(z->key)<*(y->key)){
    y->left=z;//sets node left
  }else{
    y->right=z;//sets node right
  }//else
  z->left=nil;;//sets node left to nil node
  z->right=nil;//sets node right to nil node
  z->color='R';
  rbInsertFixup(z); //fixing the tree
}
/**
@Brief This function fixes the tree after the node is inserted in the tree.
  if a a property of the Red black tree is violated.
  The properties are:
  *The root is black
  *Every leaf (NiL) is black
  *if a node is red, then both of its children are black
  *For each node, all sample paths from the node to descent leaves
  contain the same number of black nodes.
  This function checks four cases to fix up the tree,
  if one of these properties are violated.
* Case 1: x's uncle y is red, Occurs when both parent of x node,
 and node y are red.
  Because node x's parent parent is black,
  we can color both x's parent and y black,
  thereby fixing the problem of x and  both being red,
  and we can color z's parent red, thereby maintaining property 5.
  * Case 2: x's uncle node y is black and x is a right child
  This case Case 2 makes x's node point to x->parent, which is red.
  No further change to x or its color occurs in cases 2 and 3.
  * Case 3: x’s uncle node y is black and x is a left child.
  This case Case 3 makes x's parent black, so that if x->parent
  is the root at the start of the next iteration, it is black.
@param x this is the node passed from rbinsert, to fix the tree.
@return none
 */

void RBTree::rbInsertFixup(Node* x){
 Node * y=nullptr;
 while(x->parent->color=='R'){
   if(x->parent==x->parent->parent->left){
     y=x->parent->parent->right;
     if(y->color=='R'){                 //case1
       x->parent->color='B';            //case1
       y->color='B';                    //case1
       x->parent->parent->color='R';    //case1
       x=x->parent->parent;
     }else{
       if(x==x->parent->right){
         x=x->parent;                  //case2
         leftRotate(x);                //case2 //left rotate operation
       }//if
       x->parent->color='B';            //case3
       x->parent->parent->color='R';    //case3
       rightRotate(x->parent->parent);  //case3 //right rotate operation
     }//else
   }else{
     y=x->parent->parent->left;
     if(y->color=='R'){                  //case1
       x->parent->color='B';             //case1
       y->color='B';                     //case1
       x->parent->parent->color='R';
       x=x->parent->parent;
     }else{
       if(x==x->parent->left){
         x=x->parent;                   //case2
         rightRotate(x);                //case2 //right rotate operation
       }//if
       x->parent->color='B';             //case3
       x->parent->parent->color='R';     //case3
       leftRotate(x->parent->parent);    //case3 //left rotate operation
     }//else
   }//else
 }//while
root->color='B';
}//rbInsertFixup(Node* x)
/**
 @Brief This function searches for nodes with a matching key.
  It calls rbTreeSearch to check if the node exists.
  It then calls successor and predecessor for additional matches.
 @param key the key value to be searched
 @return a vector of strings that matches the key
 */
vector<const string*> RBTree::rbFind(const string& key){
  Node* xroot=root;
  vector<const string *> av;
  Node* search=rbTreeSearch(xroot, key); //search function is called
  if(search!=nil){
    av.push_back(search->value);
    Node* pred=nullptr;
    Node * succ=nullptr;
    Node * succ_Pr=search;
    Node * succ_Su=search;
    while(pred!=nil||succ!=nil){
      succ=rbTreeSuccessor(succ_Su); //successor of node
      if(succ!=nil){
        if(*(succ->key)==key){ //if key matches push it into the vector
          av.push_back(succ->value);
          succ_Su=succ;
        }else{
          succ=nil;
        }//else
      }//if
      pred=rbTreePredecessor(succ_Pr); //Predecessor of node
      if(pred!=nil){
        if(*(pred->key)==key){ //if key matches push it into the vector
          av.push_back(pred->value);
          succ_Pr=pred;
        }else{
          pred=nil;
        }//else
      }//if
    }//while
  }//if
 return av;
}//rbFind(const string& key)
/**
@Brief This function searches for a node with mathing key.
 it compares the key of node to be searched with the current key node.
 @param x node of the tree
 @param Key key of the node to be compared
 @return returns the node with matching key
 */
RBTree::Node* RBTree::rbTreeSearch(Node* x, const string& Key){
  while(x!=nil&&Key!=*(x->key)){
    if(Key<*(x->key)){
      x=x->left;
    }else{
      x=x->right;
    }
  }
 return x;
}//rbTreeSearch(Node* x, const string& Key)
/**
 @Brief This function deletes a node with mathing key and value.
 First, it calls the function findNodes,
 to get all nodes that match key and value.
 It iterates throught the vector of nodes and calls the function rbDelete,
 if the node key and value matches with the key and value of the node
 it calls the function rbDelete to delete the node.
 At the end, it frees de memory of the node deleting it.
 @param key <#key description#>
 @param value <#value description#>
 */
void RBTree::rbDelete(const string& key, const string& value){
 vector<Node*> av = findNodes(key);
 for(int i=0;i< (int) av.size();i++){
   if(*(av[i]->key)==key && *(av[i]->value)==value){
     Node * temp=av[i];
     rbDelete(av[i]);
     delete temp;
     temp=nullptr;
   }//if
 }//for
}//rbDelete(const string& key, const string& value)
/**
 @Brief This function finds the node with matching key,
  and it calls rbTreeSearch, to check if the node exists.
  It also calls predecessor and successor to find additional matches.
 @param key Key to be searched
 @return vector of nodes
 */
vector<RBTree::Node*> RBTree::findNodes(const string& key){
 Node * xroot = root;
 vector<Node*> av;
 Node * search = rbTreeSearch(xroot, key);
 if(search!=nil){
   av.push_back(search);
   Node* pred=nullptr;
   Node * succ=nullptr;
   Node * succ_Pr=search;
   Node * succ_Su=search;
   while(pred!=nil||succ!=nil){      //stop while if pred or succ is null
     succ=rbTreeSuccessor(succ_Su);
     if(succ!=nil){
       if(*(succ->key)==key){
         av.push_back(succ);
         succ_Su=succ;
       }else{
         succ=nil;                 //if no mathing keys, successor is nil
       }//else
     }//if
     pred =rbTreePredecessor(succ_Pr);
     if(pred!=nil){
       if(*(pred->key)==key){
         av.push_back(pred);
         succ_Pr=pred;
       }else{
         pred=nil;                 //if no mathing keys, predecessor is nil
       }//else
     }//if
   }//while
 }//if
return av;
}//RBTree::findNodes(const string& key)
/**
 @Brief This function deletes node z from the tree.
   it then calls rbDeleteFixup to fixed the tree after deletion of node.
 @param z node to be deleted from tree
 */
void RBTree::rbDelete(Node * z){
 Node * x=nullptr;
 Node * y=z;
 char y_OriginalColor =z->color;
 if(z->left==nil){              //if Z node has no left subtree
   x=z->right;
   rbTransplant(z,z->right);
 }else if(z->right==nil){       //if Z node has no right subtree
   x = z->left;
   rbTransplant(z,z->left);
 }else{
   y=rbTreeMaximum(z->left);    //y is set to Z's predecessor
   y_OriginalColor=y->color;
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
 }//if
}//RBTree::rbDelete(Node * z)
/**
@Brief This function fixes the tree after the node is deleted.
  if a a property of the Red black tree is violated.
  The properties are:
  *The root is black
  *Every leaf (NiL) is black
  *if a node is red, then both of its children are black
  *For each node, all sample paths from the node to descent leaves
  contain the same number of black nodes.
  This function checks four cases to fix up the tree,
  if one of these properties are violated.
* Case 1: x's sibling w is red
  This case occurs when node w, the sibling of node x, is red.
  Since w must have black children, we can switch the colors w and
  x's parent and then perfom a left rotation on x's parent
  without violating any red black property.
  The following cases occur when node w is black.
  * Case 2: x's sibling w is black, and both of w's children are black.
  In this case, both of w's children are black. Since w is also black,
  we can take one black off both x and w, leaving x with only one black
  and leaving w red.
  * Case 3: x's sibling w is black, w's left child is red,
  and w's right child is black.
  This case occurs when w is black. its left child is red, and its right
  child is black. In this case colors of node w are switched
  and w's left child node and then it performs a right rotation on w
  without violating any of the red-black properties.
  *case 4: x's sibling w is black, and w's right child is red.
   This case occurs when node x's sibling w is black,
   and w's right child is red. It performs some color changes and
   a left rotation on x's parent, so extra black is on node x is removed
   making it one black without violating any of the red-black properties.

@param x this is the node passed from rbinsert, to fix the tree.
@return none
 */
void RBTree::rbDeleteFixup(Node* x){
  Node * w=nullptr;
  while(x!=root && x->color=='B'){
    if(x==x->parent->left){
      w=x->parent->right;
      if(w->color=='R'){
        w->color='B';                    //case1
        x->parent->color='R';            //case1
        leftRotate(x->parent);           //case1
        w=x->parent->right;              //case1
      }//if
      if(w->left->color=='B' && w->right->color=='B'){
        w->color='R';                    //case2
        x=x->parent;                     //case2
      }else{
        if(w->right->color=='B'){
          w->left->color='B';             //case3
          w->color='R';                   //case3
          rightRotate(w);                 //case3
          w=x->parent->right;             //case3
        }//if
        w->color=x->parent->color;        //case4
        x->parent->color='B';             //case4
        w->right->color='B';              //case4
        leftRotate(x->parent);            //case4
        x=root;                           //case4
      }//else
    }else{
      w=x->parent->left;
      if(w->color=='R'){                  //case1
        w->color='B';                     //case1
        x->parent->color='R';             //case1
        rightRotate(x->parent);           //case1
        w=x->parent->left;
      }//if
      if(w->right->color=='B' && w->left->color=='B'){
        w->color='R';                     //case2
        x=x->parent;                      //case2
      }else{
        if(w->left->color=='B'){
          w->right->color='B';            //case3
          w->color='R';                   //case3
          leftRotate(w);                  //case3
          w=x->parent->left;
        }//if
        w->color=x->parent->color;        //case4
        x->parent->color='B';             //case4
        w->left->color='B';               //case4
        rightRotate(x->parent);           //case4
        x=root;                           //case4
      }//else
    }//else
  }//while
  x->color='B';
}//RBTree::rbDeleteFixup(Node* x)
/**
 @brief This function searches for the minimum Node in the tree or subtree
  and returns it.
  It searches to the left subtree.

 @param x Node to be searched
 @return the minimum Node of the tree or subtree
 */
RBTree::Node* RBTree::rbTreeMinimum(Node* x){
  while(x->left!=nil){
      x=x->left;
  }
  return x;
}//while
/**
 @brief
  This function searches for the maximum Node in the tree or subtree
  and returns it. I searches to the left subtree.

 @param x Node to be searched
 @return the maximum Node of the tree or subtree
 */
RBTree::Node* RBTree::rbTreeMaximum(Node* x){
  while(x->right!=nil){
        x=x->right;
  }
  return x;
}//while
/**
 @brief
  This function searches for the succesor in the tree or subtree
  and returns it. I searches to the right subtree.

 @param x Node to be searched
 @return the succesor Node of the tree or subtree
 */
RBTree::Node* RBTree::rbTreeSuccessor(Node* x){
  if(x->right!=nil){
      return rbTreeMinimum(x->right);
  }//if
  Node * y = x->parent;
  while(y!=nil && x == y->right){
      x=y;
      y=y->parent;
  }//while
  return y;
}//RBTree::rbTreeSuccessor(Node* x)
/**
 @brief
  This function searches for the predecessor in the tree or subtree
  and returns it. I searches to the left subtree.

 @param x Node to be searched
 @return the predecessor Node of the tree or subtree
 */
RBTree::Node* RBTree::rbTreePredecessor(Node* x){
  if(x->left!=nil){
      return rbTreeMaximum(x->left);
  }//if
  Node * y=x->parent;
  while(y!=nil && x == y->left){
      x=y;
      y=y->parent;
  }//while
  return y;
}//RBTree::rbTreePredecessor(Node* x)
/**
 @brief This function perfoms a right rotation to the red black tree
 to preserve the binary search property.

 @param x Node to be rotated to left
 @return none
 */
void RBTree::leftRotate(Node* x){
  Node * y = x->right;
  x->right=y->left;
  if(y->left!=nil){
    y->left->parent=x;
  }//if
  y->parent=x->parent;
  if(x->parent==nil){
     root=y;
  }else if(x==x->parent->left){
           x->parent->left=y;
  }else{
     x->parent->right=y;
  }//else
  y->left=x;
  x->parent=y;
}//RBTree::leftRotate(Node* x)
/**
 @brief This function perfoms a right rotation to the red black tree
  to preserve the binary search property.

 @param x Node to be rotated to right
 @return none
 */
void RBTree::rightRotate(Node* x){
  Node * y = x->left;
  x->left=y->right;
  if(y->right!=nil){
      y->right->parent=x;
  }//if
  y->parent=x->parent;
  if(x->parent==nil){
      root=y;
  }else if(x==x->parent->right){
      x->parent->right=y;
  }else{
      x->parent->left=y;
  }//else
  y->right=x;
  x->parent=y;
}//RBTree::rightRotate(Node* x)
/**
 @brief This function moves a subtree in the binary tree
 It replaces one subtree as a child to its parent with
 another subtree. When transplant replaces the subtree roooted at node x
 with the subtree rooted at y, node y's parent, and x's parent ends up
 having y as its appropiate child.

 @param x Node x subtree rooted at x
 @param y Node y subtree to be replaced
 @return none
 */
void RBTree::rbTransplant(Node* x, Node* y){
  if(x->parent==nil){
      root=y;
  }else if(x==x->parent->left){
      x->parent->left=y;
  }else{
      x->parent->right=y;
  }//else
  y->parent=x->parent;
}//RBTree::rbTransplant(Node* x, Node* y)
