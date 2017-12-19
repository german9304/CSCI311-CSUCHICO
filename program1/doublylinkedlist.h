/**
 * @file doublylinkedlist.h
 *
 * @brief
 *    Template for doubly linked list class.
 *
 * @author Judy Challinger & German Razo
 * @date 1/1/16
 */
#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H
using namespace std;
#include <iostream>

template <class T>
class DoublyLinkedList {

public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void append(T* data);
    bool empty() const { return (head == nullptr); }
    T* remove();
    T* first();
    T* next();

private:
    class Node {
    public:
        Node();
        Node(T* data);
        Node* next;
        Node* prev;
        T* data;
    };
    Node* head;
    Node* tail;
    Node* current;
};

/**
 * @brief   Node constructor.
 */
template <class T>
DoublyLinkedList<T>::Node::Node() {
    // Your code here...
    next=nullptr;
    prev=nullptr;

}

/**
 * @brief   DoublyLinkedList constructor.
 */
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
        head=nullptr;
        tail=nullptr;
        current=nullptr;
}

/**
 * @brief   DoublyLinkedList destructor.
 */

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {

    Node *ptr = head;
    while(ptr != nullptr){
        Node *temp = ptr;
        ptr = ptr->next;
        delete temp->data;
        delete temp;//deletes Node

    }
}

/**
 * @brief   Appends a new Node at the end of the DoublyLinkedList.
 * @param   data A pointer to the data to be stored in the new Node.
 * @return  Nothing.
 *
 * Creates a new Node to hold the data and appends the Node at the end
 * of the list. The current Node pointer is set to point to the newly
 * appended Node.
 */
template <class T>
void DoublyLinkedList<T>::append(T* data) {


    if(empty()){
        Node * newn = new Node();
        newn->data = data;
        newn->prev=nullptr;
        newn->next=nullptr;
        tail=newn;
        head=newn;
        current = newn;
        return;

    }

    Node * newnode = new Node();
    newnode->data = data;
    newnode->prev=current;
    current->next=newnode;
    tail=newnode;
    current = newnode;
}

/**
 * @brief   Get the first thing on the list.
 * @return  A pointer to the data stored in the first Node on the list,
 *          or nullptr if the list is empty.
 *
 * The current pointer is set to point to the first Node in the list,
 * or nullptr if the list is empty.
 */
template <class T>
T* DoublyLinkedList<T>::first() {

    if(empty()){
        return nullptr;
    }

    Node * cur = head;
    current=head;
    return cur->data;

}

/**
 * @brief   Get the next thing on the list.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following whatever the current pointer is pointing
 *          to. If there is no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list,
 * or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::next() {


    if(current==nullptr){
        return nullptr;
    }
    if(current->next==nullptr){
        return nullptr;
    }

    Node * cur = current->next;
    T * data = cur->data;
    current = cur;
    return data;
}

/**
 * @brief   Remove the Node pointed to by the current pointer.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following the Node that was removed. If there is
 *          no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list, following
 * the Node that was removed, or nullptr if there is no next Node.
 */

 template <class T>
 T* DoublyLinkedList<T>::remove() {
     // Your code here...
     if(empty()){
         return nullptr;
     }
    /**
    * This condition checks if current pointer is head,
    * and if head next is not nullptr
    */
     if(current==head && current->next!=nullptr){
         Node * curh=head;
         Node * curhn=head->next;
         head=curhn;
         current =curhn;
         curhn->prev=nullptr;
         delete curh->data;
         delete curh;
         return curhn->data;
     }
     /**
     * This condition checks if there is one element in the list,
     * if head and tail point to the same node.
     */
     if(head==tail){
         Node * temph = head;
         head=head->next;
         tail=tail->next;
         head=nullptr;
         tail=nullptr;
         current=nullptr;
         delete temph->data;
         delete temph;
         return nullptr;
     }
     /**
     * This condition checks if current pointer is tail
     * and if tail previous is not nullptr, remove tail
     */
     if(current==tail && tail->prev!=nullptr){
         Node * temp = tail;
         Node * tempp= tail->prev;
         tail=tempp;
         tail->next=nullptr;
         current=nullptr;
         delete temp->data;
         delete temp;
         return nullptr;
     }

     /**
     * This condition checks if current pointer is not nullptr
     * and if current is not nullptr, remove current pointer.
     */
     Node * cur = current;
     if(cur!=nullptr){
     Node * curn = cur->next;
     Node * curnprev= cur->prev;
     curn->prev = current->prev;
     curnprev->next=curn;
     current =curn;
     delete cur->data;
     delete cur;
     cur=nullptr;
     return curn->data;

     }

     return nullptr;
 }

#endif // CSCI_311_DOUBLYLINKEDLIST_H
