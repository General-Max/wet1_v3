//
// Created by User on 25/11/2022.
//

#ifndef DATA_STRUCTRS_WET1_TwoWayList_H
#define DATA_STRUCTRS_WET1_TwoWayList_H
#include <iostream>
#include "SortByScore.h"

template<class T>
class TwoWayList{
public:
    struct ListNode{
        ListNode *m_prev;
        ListNode *m_next;
        T m_nodeData;
    };

    // Node Functions
    ListNode *initNode(T data);

    // Two-Way List Functions
    TwoWayList();
    ~TwoWayList();

    ListNode* getHead();
   // ListNode<T>* m_next;

    void setHead(ListNode* newHeadNode);
//    void setTail(ListNode<T>* newTailNode);

    void insertAfter(ListNode* newNode, ListNode* prevNode);
    void insertBefore(ListNode* newNode, ListNode* nextNode);
    void removeNode(ListNode* nodeToDelete);

    void printList();
private:
    ListNode* m_head;

};

template <class T>
TwoWayList<T>::TwoWayList(): m_head(nullptr) {}

template<class T>
typename TwoWayList<T>::ListNode *TwoWayList<T>::initNode(T data) {
    ListNode* node = new ListNode();

    node->m_prev = nullptr;
    node->m_next =nullptr;
    node->m_nodeData=data;

    return node;
}

template <class T>
TwoWayList<T>::~TwoWayList()
{
    ListNode* toDelete = this->m_head;
    ListNode* temp;
    while(toDelete!= nullptr){
        temp = toDelete->m_next;
        delete toDelete;
        toDelete = temp;
    }
}

template <class T>
void TwoWayList<T>::insertAfter(TwoWayList<T>::ListNode* newNode, TwoWayList<T>::ListNode* prevNode)
{
    ListNode* nextNode = prevNode->m_next;
    newNode->m_next = nextNode;
    prevNode->m_next = newNode;
    if(nextNode!=nullptr){
        nextNode->m_prev = newNode;
    }
    newNode->m_prev = prevNode;
}

template <class T>
void TwoWayList<T>::insertBefore(TwoWayList::ListNode* newNode, TwoWayList::ListNode *nextNode)
{
    ListNode* prevNode = nextNode->m_prev;
    if(prevNode){
        newNode->m_next = nextNode;
        prevNode->m_next = newNode;
        newNode->m_prev = prevNode;
        nextNode->m_prev = newNode;
    }
    else{
        this->m_head = newNode;
        newNode->m_next = nextNode;
        nextNode->m_prev = newNode;
    }
}

template <class T>
void TwoWayList<T>::removeNode(TwoWayList<T>::ListNode* nodeToDelete)
{
    if(nodeToDelete == nullptr){
        std::cout<< "error in deleting node from a list" << std::endl;
    }
    ListNode* prevNode = nodeToDelete->m_prev;
    ListNode* nextNode = nodeToDelete->m_next;

    if(prevNode == nullptr){
        this->m_head = nextNode;
        nextNode->m_prev = nullptr;
    }
    else if(nextNode == nullptr){
        prevNode->m_next = nullptr;
    }
    else{
        prevNode->m_next = nextNode;
        nextNode->m_prev = prevNode;
    }

    std::cout << "delete list node" << nodeToDelete->m_nodeData;
    delete nodeToDelete;
}

template<class T>
void TwoWayList<T>::printList()
{
    if(this->m_head== nullptr){
        return;
    }
    std::cout << *this->m_head->m_nodeData <<  "-> ";
    ListNode* temp = this->m_head->m_next;
    while(temp != nullptr){
        std::cout << *temp->m_nodeData <<  "-> ";
        temp = temp->m_next;
    }
    std::cout << std::endl;
}

template<class T>
void TwoWayList<T>::setHead(TwoWayList::ListNode *newHeadNode) {
    this->m_head = newHeadNode;
}

template<class T>
typename TwoWayList<T>::ListNode *TwoWayList<T>::getHead() {
    return m_head;
}

#endif //DATA_STRUCTRS_WET1_TwoWayList_H
