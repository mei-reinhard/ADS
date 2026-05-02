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
    return -99999; //FEHLER nicht jeder Pfad hatte ein return
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
    return tmp->getValue(); //FEHLER nicht jeder Pfad hatte ein return
}

/**
 * Fügt eine Node der Liste am Ende hinzu
 */
void DoublyLinkedList::addNode(int value){
    Node* newNode = new Node(value);
    Node* tmp = mAnchor;
    if(mAnchor == nullptr){
        mAnchor = newNode;
        //FEHLER: newNode Next und Prev muessen nicht auf nullptr gesetzt werden
        mNodesCount++;
        return;
    }
    else if(!search(value)){
        for(int i = 0; i < mNodesCount; i++) {
            if(tmp->getNext() == nullptr){
                tmp->setNext(newNode);
                newNode->setPrev(tmp);
                mNodesCount++; //FEHLER: mNodeCount wurde NICHT geupdatet
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
                return true; //FEHLER: wenn Wert bereits da ist, sollte true returned werden
            }
            search = search->getNext();
        }
    }
    return false; //FEHLER: Umkehrschluss von voherigem Fehler
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
                    mAnchor = tmp->getNext();
                }
                //FEHLER: nicht alle Faelle fuer Nullptr wurden richtig abgedeckt + Anker wurde vergessen
                delete tmp;
                mNodesCount--;//FEHLER: -- wurde vergessen
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
    //FEHLER: hat Werte und nicht Nodes getauscht

    Node* tmpFirstPrev = first->getPrev();
    Node* tmpFirstNext = first->getNext();
    Node* tmpSecondPrev = second->getPrev();
    Node* tmpSecondNext = second->getNext();

    if (tmpFirstPrev) first->getPrev()->setNext(second);
    else mAnchor = second;
    if (tmpFirstNext) first->getNext()->setPrev(second);
    if (tmpSecondPrev) second->getPrev()->setNext(first);
    if (tmpSecondNext) second->getNext()->setPrev(first);

    if (first->getPrev() == second || first->getNext() == second) {
        if (first->getNext() == second) {
            first->setPrev(second);
            second->setNext(first);
        }
        else {
            first->setNext(second);
            second->setPrev(first);
        }
    }
    else {
        first->setNext(tmpSecondNext);
        first->setPrev(tmpSecondPrev);
        second->setNext(tmpFirstNext);
        second->setPrev(tmpFirstPrev);
    }
    return true;
}

void DoublyLinkedList::replace(int valueOne, int valueTwo) {
    if (!search(valueTwo) && mAnchor != nullptr) {
        Node* tmp = mAnchor;
        Node* newNode = new Node(valueTwo);
        while (tmp) {
            if (tmp->getValue() == valueOne) {
                if (tmp->getPrev()) tmp->getPrev()->setNext(newNode);
                else mAnchor = newNode;
                if (tmp->getNext()) tmp->getNext()->setPrev(newNode);
                newNode->setNext(tmp->getNext());
                newNode->setPrev(tmp->getPrev());
                return;
            }
            tmp = tmp->getNext();
        }
    }
};
