#include <iostream>
#include "DoublyLinkedList.h"
#include "gip_mini_catch.h"
#include <string>
#include <cstdint>  // for uintptr_t
#include <iomanip>  // for hex formatting
using namespace std;

string findAddressOfPosition(DoublyLinkedList* list, int position){
    Node* tmp = list->getAnchor();
    for(int i = 0; i < list->getNodesCount(); i++){
        if(i == position){
                            ostringstream oss;
                oss << hex << reinterpret_cast<uintptr_t>(tmp);
                return "0x" + oss.str();
        }
        tmp = tmp->getNext();
    }
    return "";
}


TEST_CASE("Hinzufuegen und Suche von Nodes")
{
    DoublyLinkedList* list = new DoublyLinkedList();
    list->addNode(5);
    list->addNode(7);

    list->addNode(9);
    list->addNode(4);

    REQUIRE(list->getNodesCount() == 4);

    REQUIRE(list->search(7) == true);
    REQUIRE(list->search(8) == false);
    REQUIRE(list->search(3) == false);
    REQUIRE(list->search(9) == true);

    int key;
    key = list->getFront();
    REQUIRE(key == 5);
    key = list->getBack();
    REQUIRE(key == 4);
}


TEST_CASE("Hinzufuegen und Loeschen von Nodes - simpel")
{
    DoublyLinkedList* list = new DoublyLinkedList();
    list->addNode(5);
    list->addNode(7);
    list->addNode(9);
    list->addNode(4);

    list->addNode(3);
    list->addNode(2);
    list->addNode(4);
    list->addNode(1);

    REQUIRE(list->getNodesCount() == 7);

    REQUIRE(list->deleteValue(8) == false);
    REQUIRE(list->deleteValue(4) == true);
    REQUIRE(list->deleteValue(1) == true);
    REQUIRE(list->deleteValue(5) == true);

    REQUIRE(list->getNodesCount() == 4);

    int key;
    key = list->getFront();
    REQUIRE(key == 7);
    key = list->getBack();
    REQUIRE(key == 2);
}


TEST_CASE("Vertauschen von zwei Elementen - Zwei Knoten aus der Mitte, nicht nebeneinander")
{
    DoublyLinkedList* list = new DoublyLinkedList();


    list->addNode(4);
    list->addNode(9);
    list->addNode(7);
    list->addNode(5);
    list->addNode(3);
    list->addNode(2);
    list->addNode(8);
    list->addNode(1);

    REQUIRE(list->getNodesCount() == 8);
    Node* tmp = list->getAnchor();
    // prüfe ob 2 an neuem Platz
    int pos = 0;
    for (int i = 0; i < 3; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string originalAddressFirstNode = findAddressOfPosition(list, pos);
    for (int i = 0; i < 3; i++){
        pos += i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string originalAddressSecondNode = findAddressOfPosition(list, pos);

    REQUIRE(list->swap(7, 2) == true);
    tmp = list->getAnchor();
    for (int i = 0; i < 3; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string newAddressSecondNode = findAddressOfPosition(list, pos);
    for (int i = 0; i < 3; i++){
        pos += i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string newAddressFirstNode = findAddressOfPosition(list, pos);

    REQUIRE(originalAddressFirstNode == newAddressFirstNode);
    REQUIRE(originalAddressSecondNode == newAddressSecondNode);
}

TEST_CASE("Vertauschen von zwei Elementen - Erster Knoten mit einem aus der Mitte, nicht nebeneinander")
{
    DoublyLinkedList* list = new DoublyLinkedList();


    list->addNode(4);
    list->addNode(9);
    list->addNode(7);
    list->addNode(5);
    list->addNode(3);
    list->addNode(2);
    list->addNode(8);
    list->addNode(1);

    REQUIRE(list->getNodesCount() == 8);
    Node* tmp = list->getAnchor();
    int pos = 0;
    string originalAddressFirstNode = findAddressOfPosition(list, pos);
    for (int i = 0; i < 4; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string originalAddressSecondNode = findAddressOfPosition(list, pos);

    REQUIRE(list->swap(4, 5) == true);
    tmp = list->getAnchor();
    pos = 0;
    string newAddressSecondNode = findAddressOfPosition(list, pos);
    for (int i = 0; i < 4; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string newAddressFirstNode = findAddressOfPosition(list, pos);

    REQUIRE(originalAddressFirstNode == newAddressFirstNode);
    REQUIRE(originalAddressSecondNode == newAddressSecondNode);
}
TEST_CASE("Vertauschen von zwei Elementen - Letzter Knoten mit einem aus der Mitte, nicht nebeneinander")
{
    DoublyLinkedList* list = new DoublyLinkedList();

    list->addNode(4);
    list->addNode(9);
    list->addNode(7);
    list->addNode(5);
    list->addNode(3);
    list->addNode(2);
    list->addNode(8);
    list->addNode(1);

    Node* tmp = list->getAnchor();
    int pos = 0;
    for (int i = 0; i < 5; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string originalAddressFirstNode = findAddressOfPosition(list, pos);
    for (int i = 0; i < 3; i++){
        pos += i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string originalAddressSecondNode = findAddressOfPosition(list, pos);

    REQUIRE(list->swap(1, 3) == true);
    tmp = list->getAnchor();
    for (int i = 0; i < 5; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string newAddressSecondNode = findAddressOfPosition(list, pos);
    for (int i = 0; i < 3; i++){
        pos += i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string newAddressFirstNode = findAddressOfPosition(list, pos);

    REQUIRE(originalAddressFirstNode == newAddressFirstNode);
    REQUIRE(originalAddressSecondNode == newAddressSecondNode);
}

TEST_CASE("Vertauschen von zwei Elementen - Zwei Knoten aus der Mitte, nebeneinander")
{
    DoublyLinkedList* list = new DoublyLinkedList();

    list->addNode(4);
    list->addNode(9);
    list->addNode(7);
    list->addNode(5);
    list->addNode(3);
    list->addNode(2);
    list->addNode(8);
    list->addNode(1);

    Node* tmp = list->getAnchor();
    int pos = 0;
    for (int i = 0; i < 6; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string originalAddressFirstNode = findAddressOfPosition(list, pos);
    for (int i = 0; i < 2; i++){
        pos += i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }

    string originalAddressSecondNode = findAddressOfPosition(list, pos);

    REQUIRE(list->swap(8, 2) == true);
    tmp = list->getAnchor();
    for (int i = 0; i < 6; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string newAddressSecondNode = findAddressOfPosition(list, pos);
    for (int i = 0; i < 2; i++){
        pos += i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string newAddressFirstNode = findAddressOfPosition(list, pos);

    REQUIRE(originalAddressFirstNode == newAddressFirstNode);
    REQUIRE(originalAddressSecondNode == newAddressSecondNode);
}