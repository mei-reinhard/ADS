/*************************************************
 * ADS Praktikum 1.1
 * Unit-Testdatei fuer BST
 * Umgeschrieben auf BST / Node
 *
 *************************************************
 * Änderungen am Produktivcode nicht notwendig
 *************************************************/

#define private public
#include "bst.h"
#undef private

#include "catch.h"
#include <iostream>
#include <string>

using namespace std;

// Zugriff auf die Wurzel analog zur alten Friend-Methode
Node* get_anker(Bst& tree)
{
    return tree.mRoot;
}

/***********************************************
 * Testroutine des Baums:
 *  - Einfaches Hinzufuegen und Suchen
 *  - Loeschen in unterschiedlicher Ausprägung
 *  + Loeschen ohne Nachfolger
 *  + Loeschen mit einem Nachfolger
 *  + Loeschen mit zwei Nachfolger
 *  + Loeschen der Wurzel
 *  - Hinzufuegen vieler Nodes als Grossbaum
 */
TEST_CASE("BST Testing", "[BST]")
{


    SECTION("Hinzufuegen von Nodes und Suche - simple")
    {
        Bst* nTree = new Bst();
        nTree->insert(20);
        nTree->insert(10);
        nTree->insert(30);
        nTree->insert(40);
        nTree->insert(35);
        nTree->insert(25);
        nTree->insert(26);

        REQUIRE(nTree->find(20) != nullptr);
        REQUIRE(nTree->find(26) != nullptr);
        REQUIRE(nTree->find(25) != nullptr);
        REQUIRE(nTree->find(35) != nullptr);
        REQUIRE(nTree->find(40) != nullptr);
        REQUIRE(nTree->find(30) != nullptr);
        REQUIRE(nTree->find(10) != nullptr);

        REQUIRE(nTree->find(999) == nullptr);
        REQUIRE(nTree->find(-1) == nullptr);
    }

    SECTION("Loeschen von Nodes - ohne Nachfolger")
    {
        Bst* nTree = new Bst();
        nTree->insert(20);
        nTree->insert(10);
        nTree->insert(30);
        nTree->insert(40);
        nTree->insert(35);
        nTree->insert(25);
        nTree->insert(26);

        nTree->insert(8);
        REQUIRE(nTree->find(8) != nullptr);

        Node* tnanker = get_anker(*nTree);

        nTree->deleteValue(8);
        REQUIRE(tnanker->left->left == nullptr);
    }

    SECTION("Loeschen von Nodes - mit einem Nachfolger")
    {
        Bst* nTree = new Bst();
        nTree->insert(20);
        nTree->insert(10);
        nTree->insert(30);
        nTree->insert(40);
        nTree->insert(35);
        nTree->insert(25);
        nTree->insert(26);

        nTree->insert(8);
        nTree->insert(7);

        REQUIRE(nTree->find(8) != nullptr);
        REQUIRE(nTree->find(7) != nullptr);

        Node* tnanker = get_anker(*nTree);

        // linke Seite
        nTree->deleteValue(8);
        REQUIRE(tnanker->left->left != nullptr);
        REQUIRE(tnanker->left->right == nullptr);
        REQUIRE(tnanker->left->left->data == 7);

        nTree->deleteValue(7);
        REQUIRE(tnanker->left->left == nullptr);
        REQUIRE(tnanker->left->right == nullptr);
        REQUIRE(tnanker->left->data == 10);

        REQUIRE(nTree->find(8) == nullptr);
        REQUIRE(nTree->find(7) == nullptr);

        // rechte Seite
        nTree->insert(8);
        nTree->insert(9);

        REQUIRE(nTree->find(8) != nullptr);
        REQUIRE(nTree->find(9) != nullptr);

        nTree->deleteValue(8);
        REQUIRE(tnanker->left->left != nullptr);
        REQUIRE(tnanker->left->left->data == 9);

        nTree->deleteValue(9);
        REQUIRE(tnanker->left->left == nullptr);
        REQUIRE(tnanker->left->data == 10);

        REQUIRE(nTree->find(8) == nullptr);
        REQUIRE(nTree->find(9) == nullptr);
    }

    SECTION("Loeschen von Nodes - mit zwei Nachfolger")
    {
        Bst* nTree = new Bst();
        nTree->insert(20);
        nTree->insert(10);
        nTree->insert(30);
        nTree->insert(40);
        nTree->insert(35);
        nTree->insert(25);
        nTree->insert(26);

        Node* tnanker = get_anker(*nTree);

        REQUIRE(tnanker->data == 20);
        REQUIRE(tnanker->right->data == 30);
        REQUIRE(tnanker->right->left->data == 25);
        REQUIRE(tnanker->right->left->right->data == 26);
        REQUIRE(tnanker->right->right->left->data == 35);

        nTree->deleteValue(30);
        REQUIRE(tnanker->data == 20);
        REQUIRE(tnanker->right->data == 35);
        REQUIRE(tnanker->right->right->data == 40);
        REQUIRE(tnanker->right->right->left == nullptr);
        REQUIRE(tnanker->right->right->right == nullptr);
        REQUIRE(tnanker->right->left->data == 25);
        REQUIRE(tnanker->right->left->right->data == 26);
        REQUIRE(tnanker->right->left->left == nullptr);

        nTree->deleteValue(35);
        REQUIRE(tnanker->data == 20);
        REQUIRE(tnanker->right->data == 40);
        REQUIRE(tnanker->right->left->data == 25);
    }

    SECTION("Loeschen von Nodes - ab Wurzel")
    {
        Bst* nTree = new Bst();
        nTree->insert(20);
        nTree->insert(10);
        nTree->insert(30);
        nTree->insert(40);
        nTree->insert(35);
        nTree->insert(25);
        nTree->insert(26);

        Node* tnanker = get_anker(*nTree); // Initiale Übergabe des Ankers

        /*
        Lösche den Baum schrittweise durch Entfernen der Wurzel
        */
        REQUIRE(tnanker->data == 20);
        nTree->deleteValue(20);
        tnanker = get_anker(*nTree); // Wurzel hat sich geändert

        REQUIRE(tnanker->data == 25);
        REQUIRE(tnanker->right->data == 30);
        REQUIRE(tnanker->right->left->data == 26);
        REQUIRE(tnanker->right->right->data == 40);

        nTree->deleteValue(25);
        tnanker = get_anker(*nTree);

        REQUIRE(tnanker->data == 26);
        REQUIRE(tnanker->right->data == 30);
        REQUIRE(tnanker->right->left == nullptr);
        REQUIRE(tnanker->right->right->data == 40);

        nTree->deleteValue(26);
        tnanker = get_anker(*nTree);

        REQUIRE(tnanker->data == 30);
        REQUIRE(tnanker->right->data == 40);
        REQUIRE(tnanker->right->left->data == 35);
        REQUIRE(tnanker->right->right == nullptr);

        nTree->deleteValue(30);
        tnanker = get_anker(*nTree);

        REQUIRE(tnanker->data == 35);
        REQUIRE(tnanker->right->data == 40);
        REQUIRE(tnanker->right->left == nullptr);
        REQUIRE(tnanker->right->right == nullptr);

        nTree->deleteValue(35);
        tnanker = get_anker(*nTree);

        REQUIRE(tnanker->data == 40);
        REQUIRE(tnanker->right == nullptr);
        REQUIRE(tnanker->left->data == 10);

        nTree->deleteValue(40);
        tnanker = get_anker(*nTree);

        REQUIRE(tnanker->data == 10);
        REQUIRE(tnanker->right == nullptr);
        REQUIRE(tnanker->left == nullptr);

        nTree->deleteValue(10);
        tnanker = get_anker(*nTree);

        REQUIRE(tnanker == nullptr);
    }

    SECTION("Hinzufuegen von Nodes - Erzeuge Grossbaum")
    {
        Bst* nTree = new Bst();
        for (int i = 0; i < 120; i++)
        {
            int value = rand() + 1;
            nTree->insert(value);
        }

        nTree->inorder();
        nTree->preorder();
        nTree->postorder();
        nTree->levelorder(get_anker(*nTree));

        std::cout << "========================================" << endl;
        std::cout << "Testausgabe des Grossbaums abgeschlossen" << endl;
    }
}

/***********************************************
 * Testroutine des Knotens:
 *  - Einfaches Prüfen der Strukturfelder in Ausführung
 */
TEST_CASE("Node Testing", "[NODE]")
{
    Bst* smallTree = new Bst();
    smallTree->insert(20);
    Node* ref = get_anker(*smallTree);

    SECTION("Getter von Node - simple")
    {
        REQUIRE(ref != nullptr);
        REQUIRE(ref->data == 20);
        REQUIRE(ref->left == nullptr);
        REQUIRE(ref->right == nullptr);

        // Höhe hängt von deiner Implementierung ab.
        // Wenn insert/updateHeight korrekt arbeitet, ist bei der Wurzel oft 0 oder 1 üblich.
        // Daher absichtlich kein harter REQUIRE auf ref->height.
    }

    SECTION("Setter von Node - simple")
    {
        ref->data = 22;
        REQUIRE(ref->data == 22);

        ref->left = nullptr;
        REQUIRE(ref->left == nullptr);

        ref->right = nullptr;
        REQUIRE(ref->right == nullptr);

        ref->height = 5;
        REQUIRE(ref->height == 5);
    }

    delete smallTree;
}