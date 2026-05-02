#pragma once

class Node{
    private:
        int mValue; // Wert des Knotens
        Node* mNext; // Nachfolger
        Node* mPrev; // Vorgänger

    public:
        Node();
        Node(int value);

        int getValue(); // Gibt den Wert des Knotens aus
        Node* getNext(); // Gibt den Nachfolger des Knotens aus
        Node* getPrev(); // Gibt den Vorgänger des Knotens aus

        void setValue(int value); // Setzt den Wert des Knotens
        void setNext(Node* next); // Setzt den Nachfolger des Knotens
        void setPrev(Node* prev); // Setzt den Vorgänger des Knotens

};