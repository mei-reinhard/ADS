#pragma once

/**
* Struktur zur Darstellung eines Knotens eines (Binär-)Baumes
*
* @param data Zahlenwert der im Baum gespeichert wird
* @param height Höhe des Knotens im Baum
* @param left Linkes Kind des Knotens
* @param right Rechtes Kind des Knotens
*
*/
struct Node
{
	int data;
	int height;
	Node* left, * right;
};

/**
* Klasse zur Darstellung eines Binärbaumes
*
* @param root Wurzelknoten des Baumes
*
*/
class Bst
{
	
public:
	Node* find(int value);
	void insert(int value);
	void inorder();
	void preorder();
	void postorder();
	void levelorder(Node* start);
	void deleteValue(int value);
	Node* getmRoot() { return mRoot; }
private:
	Node* mRoot = nullptr;
	void updateHeight(Node* start);
};