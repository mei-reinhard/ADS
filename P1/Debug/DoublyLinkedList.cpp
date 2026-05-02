#include "DoublyLinkedList.h"
#include <iostream>
#include <string>
#include <sstream>
/**
 * Konstruktor für eine leere Liste
 */
DoublyLinkedList::DoublyLinkedList(){
    mNodesCount = 0;
    mAnchor = nullptr;
}
/**
 * Getter für die Anzahl der Nodes in der Liste
 */
int DoublyLinkedList::getNodesCount(){
    return this->mNodesCount;
}
/**
 * Getter für den Pointer Anchor welches auf das erste Element zeigt
 */
Node*  DoublyLinkedList::getAnchor(){
    return this->mAnchor;
}

/**
 * Getter für den Wert der ersten Node
 */
int DoublyLinkedList::getFront(){
    if(mAnchor != nullptr){
        return mAnchor->getValue();
    }
    return -99999;
}

/**
 * Getter für den Wert der letzten Node
 */
int DoublyLinkedList::getBack(){
    if (mAnchor == nullptr) return -99999;
    Node* tmp = mAnchor;
    for(int i = 0; i < mNodesCount; i++){
        if(tmp->getNext() == nullptr){
            return tmp->getValue();
        }
        tmp = tmp->getNext();
    }
    return -99999;
}

/**
 * Fügt eine Node der Liste am Ende hinzu
 */
void DoublyLinkedList::addNode(int value){
    Node* newNode = new Node(value);
    Node* tmp = mAnchor;
    if(mAnchor == nullptr){
        mAnchor = newNode;
        newNode->setNext(nullptr);
        newNode->setPrev(nullptr);
        mNodesCount++;
    }
    else if(!search(value)){
        for(int i = 0; i < mNodesCount; i++) {
            if(tmp->getNext() == nullptr){
                tmp->setNext(newNode);
                newNode->setPrev(tmp);
                mNodesCount++;
                return;
            }
            tmp = tmp->getNext();
        }
    }
}
/**
 * Sucht ob eine Node mit einem bestimmten Wert bereits in der Liste ist
 */
bool DoublyLinkedList::search(int value){
    Node* search = mAnchor;
    if(mAnchor != nullptr){
        for(int i = 0; i < mNodesCount; i++){
            if(search->getValue() == value){
                return true;
            }
            search = search->getNext();
        }
    }
    return false;
}

/**
 * Löscht eine Node mit einem bestimmten Wert
 */
bool DoublyLinkedList::deleteValue(int value){
    if(mAnchor == nullptr){
        return false;
    }
    Node* tmp = mAnchor;
    if(search(value)){
        for(int i = 0; i < mNodesCount; i++){
            if(tmp->getValue() == value){
                if (tmp->getNext() != nullptr && tmp->getPrev() != nullptr) {
                    tmp->getPrev()->setNext(tmp->getNext());
                    tmp->getNext()->setPrev(tmp->getPrev());
                }
                else if (tmp->getNext() == nullptr && tmp->getPrev() != nullptr) {
                    tmp->getPrev()->setNext(nullptr);
                }
                else if (tmp->getNext() != nullptr && tmp->getPrev() == nullptr) {
                    tmp->getNext()->setPrev(nullptr);
                }

                delete tmp;
                mNodesCount--;
                return true;
                
            }
            tmp = tmp->getNext();
        }
    }
    return false;
}

/**
 * Vertauscht zwei Nodes basierend auf ihren Werten
 */
bool DoublyLinkedList::swap(int valueOne, int valueTwo) {
    if (valueOne == valueTwo || mNodesCount < 2) return false;

    Node* first = nullptr;
    Node* second = nullptr;
    Node* current = mAnchor;

    // Find both nodes
    while (current) {
        if (current->getValue() == valueOne) first = current;
        else if (current->getValue() == valueTwo) second = current;
        current = current->getNext();
    }

    if (!first || !second) return false;

    int temp = first->getValue();
    first->setValue(second->getValue());
    mNodesCount++;
    second->setValue(temp);

    return true;
}

void DoublyLinkedList::replace(int valueOne, int valueTwo) {
};