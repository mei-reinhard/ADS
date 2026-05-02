#include "Node.h"
/**
 * Konstruktor für eine leere Node
 */
Node::Node(){
    this->mValue = -1;
    this->mNext = nullptr;
    this->mPrev = nullptr;
}
/**
 * Konstruktor für eine Node mit bestimten Wert
 */
Node::Node(int value){
    this->mValue = value;
    this->mNext = nullptr;
    this->mPrev = nullptr;
}
/**
 * Getter für Wert der Node
 */
int Node::getValue(){
    return this->mValue;
}
/**
 * Getter für den Nachfolger der Node
 */
Node* Node::getNext(){
    return this->mNext;
}   
/**
 * Getter für den Vorgänger der Node
 */
Node* Node::getPrev(){
    return this->mPrev;
}
/**
 * Setter für Wert der Node
 */
void Node::Node(int value){
    this->mValue = value;
}
/**
 * Setter für den Nachfolger der Node
 */
void Node::setNext(Node* next){
    this->mNext = next;
}
/**
 * Setter für den Vorgänger der Node
 */
void Node::setPrev(Node* prev){
    this->mPrev = prev;
}