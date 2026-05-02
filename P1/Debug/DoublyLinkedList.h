#pragma once
#include <string>
#include "Node.h"

class DoublyLinkedList{
    private:
        Node* mAnchor; // Zeiger auf Kopfelement
        int mNodesCount; // Länge der Kette

    public:
        DoublyLinkedList(); // Konstruktor

        void addNode(int value); // Einfügen eines Knotens am Ende
        bool search(int value); // Suchen eines Knoten
        bool deleteValue(int value); // löschen eines Knotens [value]

        bool swap(int valueOne, int valueTwo); // Knoten in der Liste vertauschen
        void replace(int valueOne, int valueTwo); //Knoten in der Liste ersetzen
        //FEHLER replace hat in beiden Datein gefehlt

        int getNodesCount(); // Größe der Lise (Anzahl der Knoten)
        Node* getAnchor(); // Gibt den Pointer auf die erste Node aus

        int getFront(); // Wert des ersten Eintrags
        int getBack(); // Wert des letzten Eintrags
};