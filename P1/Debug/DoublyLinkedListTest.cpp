#include <iostream>
#include "DoublyLinkedList.h"
#include "gip_mini_catch.h"
#include <sstream>
#include <string>
#include <cstdint>  // for uintptr_t
#include <iomanip>  // for hex formatting
using namespace std;

string findAddress(DoublyLinkedList* list, int value){
    Node* tmp = list->getAnchor();
        if(list->getAnchor()!= nullptr){
        for(int i = 0; i < list->getNodesCount(); i++){
            if(tmp->getValue() == value){
                ostringstream oss;
                oss << hex << reinterpret_cast<uintptr_t>(tmp);
                return "0x" + oss.str();
            }
            tmp = tmp->getNext();
        }
    }
    return "";
}

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

TEST_CASE("Vertauschen von zwei Elementen - Erster Knoten mit direktem Nachbar")
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
    for (int i = 0; i < 2; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string originalAddressSecondNode = findAddressOfPosition(list, pos);

    REQUIRE(list->swap(4, 9) == true);
    tmp = list->getAnchor();
    pos = 0;
    string newAddressSecondNode = findAddressOfPosition(list, pos);
    for (int i = 0; i < 2; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string newAddressFirstNode = findAddressOfPosition(list, pos);

    REQUIRE(originalAddressFirstNode == newAddressFirstNode);
    REQUIRE(originalAddressSecondNode == newAddressSecondNode);
}

TEST_CASE("Vertauschen von zwei Elementen - Letzer Knoten mit direktem Nachbar")
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
    for (int i = 0; i < 7; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string originalAddressFirstNode = findAddressOfPosition(list, pos);
    for (int i = 0; i < 8; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string originalAddressSecondNode = findAddressOfPosition(list, pos);

    REQUIRE(list->swap(8, 1) == true);
    tmp = list->getAnchor();
    pos = 0;
    for (int i = 0; i < 7; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string newAddressSecondNode = findAddressOfPosition(list, pos);
    for (int i = 0; i < 8; i++){
        pos = i;
        if(tmp->getNext())
            tmp = tmp->getNext();
    }
    string newAddressFirstNode = findAddressOfPosition(list, pos);

    REQUIRE(originalAddressFirstNode == newAddressFirstNode);
    REQUIRE(originalAddressSecondNode == newAddressSecondNode);
}

TEST_CASE("Vertauschen von zwei Elementen - Nur zwei Elemente in der Liste")
{
    DoublyLinkedList* list = new DoublyLinkedList();

    list->addNode(4);
    list->addNode(9);

    REQUIRE(list->getNodesCount() == 2);
    string originalAddressFirstNode = findAddressOfPosition(list, 0);
    string originalAddressSecondNode = findAddressOfPosition(list, 1);

    REQUIRE(list->swap(4, 9) == true);
    string newAddressSecondNode = findAddressOfPosition(list, 0);
    string newAddressFirstNode = findAddressOfPosition(list, 1);

    REQUIRE(originalAddressFirstNode == newAddressFirstNode);
    REQUIRE(originalAddressSecondNode == newAddressSecondNode);
}


TEST_CASE("Tauschen eines Elements mit einem Neuen")
{

    DoublyLinkedList* list = new DoublyLinkedList();
    list->addNode(2);
    list->addNode(5);
    list->addNode(6);
    list->addNode(56);
    list->addNode(4);

    //Replacing a Middle Node
    string originalAddress = findAddress(list, 6);
    list->replace(6, 3);
    string newAddress = findAddress(list, 3);
    REQUIRE(originalAddress != newAddress);

    //Replacing the First Node
    originalAddress = findAddress(list, 2);
    list->replace(2, 12);
    newAddress = findAddress(list, 12);
    REQUIRE(originalAddress != newAddress);

    list->addNode(101);

    //Replacing the Last Node
    originalAddress = findAddress(list, 101);
    list->replace(101, 10);
    newAddress = findAddress(list, 10);
    REQUIRE(originalAddress != newAddress);

    //Replacing an already swapped Node
    originalAddress = findAddress(list, 3);
    list->replace(3, 21);
    newAddress = findAddress(list, 21);
    REQUIRE(originalAddress != newAddress);

    //Trying to replace node with an existing value, nothing should happen
    originalAddress = findAddress(list, 5);
    list->replace(5, 21);
    newAddress = findAddress(list, 21);
    REQUIRE(originalAddress != newAddress);
    
    REQUIRE(list->getNodesCount() == 6);
}
