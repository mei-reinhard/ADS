#define CATCH_CONFIG_RUNNER
#include "bst.h"
#include "catch.h"
#include <iostream>

using namespace std;

///////////////////////////////////////
// Hilfsmethoden fürs Menü hier:

void mainscreenMenu()
{
    cout << "=========================================" << endl
        << "1) Datensatz einfuegen, manuell " << endl
        << "2) Suchen " << endl
        << "3) Datensatz löschen" << endl
        << "4) Datenstruktur anzeigen " << endl
        << "5) Beenden" << endl
        << "?>";
}

void mainscreenAddNode(Bst*& ref)
{
    int data;
    cout << "+ Bitte geben Sie die den Datensatz ein:" << endl;
    cout << " Data ?> ";
    cin >> data;
    ref->insert(data);
    cout << "+ Ihr Datensatz wurde eingefügt" << endl;
}

void mainscreenSearchNode(Bst*& ref)
{
    int data;
    cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
    cout << " Data ?> ";
    cin.ignore();
    cin >> data;
    if (ref->find(data)->data == data) {
        cout << endl << "Data wurde im BST gefunden." << endl;
        return;
    }
    else
    {
        cout << endl << "Data wurde nicht im BST gefunden." << endl;
        return;
    }
}

void mainscreenDelNode(Bst*& ref)
{
    int delData = 0;
    cout << "+ Bitte geben Sie den zu löschenden Datensatz an" << endl;
    cout << " Data ?> ";
    cin >> delData;
    ref->deleteValue(delData);
}

void printAll(Bst*& ref) {
    cout << "Tree in Inorder:" << endl;
    ref->inorder();
    cout << endl << endl;
    cout << "Tree in Preorder:" << endl;
    ref->preorder();
    cout << endl << endl;
    cout << "Tree in Postorder:" << endl;
    ref->postorder();
    cout << endl << endl;
    cout << "Tree in Levelorder:" << endl;
    ref->levelorder(ref->getmRoot());
    cout << endl << endl;
}

//
///////////////////////////////////////
int main()
{

    Catch::Session().run();

    ///////////////////////////////////////
    // Ihr Code hier:
    Bst* nTree = new Bst();

    cout << "=========================================" << endl;

    int menu_option = 0;
    bool loop_flag = true;
    while (loop_flag)
    {
        do
        {
            mainscreenMenu();
            cin >> menu_option;
        } while (menu_option < 1 || menu_option > 6);

        switch (menu_option)
        {
        case 1:
            mainscreenAddNode(nTree);
            break;
        case 2:
            mainscreenSearchNode(nTree);
            break;
        case 3:
            mainscreenDelNode(nTree);
            break;
        case 4:
            printAll(nTree);
            break;
        case 5:
            cout << "Thanks, mate!" << endl;
            loop_flag = false;
            break;
        }
    }
    //mainscreen_menu();

    //
    ///////////////////////////////////////
    system("PAUSE");

    return 0;
}
