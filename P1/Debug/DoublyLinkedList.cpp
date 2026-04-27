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
    return -1;
}

/**
 * Getter für den Wert der letzten Node
 */
int DoublyLinkedList::getBack(){
    if (mAnchor == nullptr)
            return -1;
    Node* tmp = mAnchor;
    for(int i = 0; i < mNodesCount; i++){
        if(tmp->getNext() == nullptr){
            return tmp->getValue();
        }
        tmp = tmp->getNext();
    }
    return tmp->getValue();
}

/**
 * Fügt eine Node der Liste am Ende hinzu
 */
void DoublyLinkedList::addNode(int value){
    Node* newNode = new Node(value);
    Node* tmp = mAnchor;
    if(mAnchor == nullptr){
        mAnchor = newNode;
        mNodesCount++;
        return;
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
                if(tmp->getPrev())
                    tmp->getPrev()->setNext(tmp->getNext());
                else
                    mAnchor = tmp->getNext();
                if(tmp->getNext())
                    tmp->getNext()->setPrev(tmp->getPrev());
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
    if (valueOne == valueTwo || mNodesCount < 2)
        return false;

    Node* first = nullptr;
    Node* second = nullptr;
    Node* current = mAnchor;

    // Find both nodes
    while (current) {
        if (current->getValue() == valueOne && !first) first = current;
        else if (current->getValue() == valueTwo && !second) second = current;
        current = current->getNext();
    }
    if (!first || !second) return false;

    Node* fprev = first->getPrev();
    Node* fnext = first->getNext();
    Node* sprev = second->getPrev();
    Node* snext = second->getNext();

    if (fprev) fprev->setNext(second);
    else mAnchor = second;
    if (fnext) fnext->setPrev(second);
    if (sprev) sprev->setNext(first);
    if (snext) snext->setPrev(first);

    first->setNext(second->getNext());
    first->setPrev(second->getPrev());
    second->setNext(fnext);
    second->setPrev(fprev);
    return true;
}