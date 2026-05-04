// ADS Praktikum 1.2 BST Musterl�sung
// Stand M�rz 2025
// Autor Carlhoff
#include <iostream>
#include <queue>
#include "bst.h"



/**
* Start-Funktion zur Suche eines Integer-Zahlenwertes im Baum
*
* @param value Integer-Zahlenwert, der gesucht werden soll
*
*/
Node* Bst::find(int value)
{
	//TODO: Suche im BST
	if (mRoot == nullptr) return nullptr;
	if (value == mRoot->data) return mRoot;
	if (value < mRoot->data) return subFind(value, mRoot->left);
	if (value > mRoot->data) return subFind(value, mRoot->right);
	return nullptr;


	// //TODO: Return demo node ersetzen
	// return new node;
}

Node* Bst::subFind(int value, Node* node) {
	if (value == node->data) return node;
	if (value < node->data) {
		if (node->left == nullptr) return nullptr;
		return subFind(value, node->left);
	} ;
	if (value > node->data) {
		if (node->right == nullptr) return nullptr;
		return subFind(value, node->right);
	}
	return nullptr;
}

/**
* Funktion zum Einf�gen eines Integer-Zahlenwertes in den Baum
*
* @param value Integer-Zahlenwert, der eingef�gt werden soll
*
*/
void Bst::insert(int value)
{
	Node* node = new Node;
	node->data = value;
	node->left = nullptr;
	node->right = nullptr;
	if (mRoot == nullptr) {
		mRoot = node;
		return;
	}

	if (value < mRoot->data) {
		if (mRoot->left == nullptr) mRoot->left = node;
		else subInsert(mRoot->left, node);
	}
	else if (value > mRoot->data) {
		if (mRoot->right == nullptr) mRoot->right = node;
		else subInsert(mRoot->right, node);
	}
}

void Bst::subInsert(Node* node, Node* toInsert) {
	if (node->data > toInsert->data) {
		if (node->left == nullptr) {
			node->left = toInsert;
		}
		else subInsert(node->left, toInsert);
	}
	else if (node->data < toInsert->data) {
		if (node->right == nullptr) {
			node->right = toInsert;
		}
		else subInsert(node->right, toInsert);
	}

}

void Bst::inorder() {

	//TODO: Ausagbe des BST in Inorder
	subInorder(mRoot);
}

void Bst::subInorder(Node* node) {
	if (node->left != nullptr) subInorder(node->left);
	std::cout << node->data << std::endl;
	if (node->right != nullptr) subInorder(node->right);
}

void Bst::preorder() {

	//TODO: Ausagbe des BST in Preorder
	subPreorder(mRoot);

}

void Bst::subPreorder(Node* node) {
	std::cout << node->data << std::endl;
	if (node->right != nullptr) subPreorder(node->right);
	if (node->left != nullptr) subPreorder(node->left);
}


void Bst::postorder() 
{
	//TODO: Ausagbe des BST in Postorder
	subPostorder(mRoot);

}

void Bst::subPostorder(Node* node) {
	if (node->right != nullptr) subPostorder(node->right);
	if (node->left != nullptr) subPostorder(node->left);
	std::cout << node->data << std::endl;
}

void Bst::levelorder(Node* start) 
{
	//TODO: Ausagbe des BST in Levelorder
	std::queue<Node*> q;
	Node* node = start;
	q.push(node);
	while (!q.empty()) {
		node = q.front();
		if (node->left) q.push(node->left);
		if (node->right) q.push(node->right);
		std::cout << node->data;
		q.pop();
	}
}


/**
* Start-Funktion zum L�schen eines Integer-Zahlenwertes im Baum
*
* @param value Integer-Zahlenwert, der gel�scht werden soll
*
*/

void Bst::deleteValue(int value) {
	Node* dele = find(value);
	if (!dele) return;

	Node* deleParent = findParent(dele);
	//Wenn dele zwei Childknoten hat
	if (dele->left && dele->right) {
		Node* minLeft = dele->right;
		Node* minLeftParent = dele;

		while (minLeft->left) {
			minLeftParent = minLeft;
			minLeft = minLeft->left;
		}

		if (minLeftParent != dele) {
			minLeftParent->left = minLeft->right;
			minLeft->right = dele->right;
		}

		minLeft->left = dele->left;

		if (dele == mRoot) mRoot = minLeft;
		else {
			if (deleParent->right == dele) deleParent->right = minLeft;
			else deleParent->left = minLeft;

		}
		delete dele;
	}
	//Wenn dele keine Childknoten hat
	else if (!(dele->left || dele->right)) {
		if (dele == mRoot) mRoot = nullptr;
		else {
			if (deleParent->right == dele) deleParent->right = nullptr;
			else deleParent->left = nullptr;
		}


		delete dele;

	}
	//Wenn dele nur einen Childknoten hat
	else {
		if (dele->right) {
			if (deleParent) {
				if (deleParent->right == dele) deleParent->right = dele->right;
				else deleParent->left = dele->right;
			}
			if (dele == mRoot) mRoot = dele->right;
			delete dele;
		}
		else {
			if (deleParent) {
				if (deleParent->right == dele) deleParent->right = dele->left;
				else deleParent->left = dele->left;
			}

			if (dele == mRoot) mRoot = dele->left;
			delete dele;
		}

	}
}

Node* Bst::findParent(Node* node) {
	if (mRoot == nullptr || node == mRoot || node == nullptr ) return nullptr;
	Node* tmp = mRoot;
	while (true) {

		if (tmp->left == node || tmp->right == node) return tmp;

		else if (node->data > tmp->data) {
			if (tmp->right != nullptr) tmp = tmp->right;
			else return nullptr;
		}

		else if (node->data < tmp->data) {
			if (tmp->left != nullptr) tmp = tmp->left;
			else return nullptr;
		}
	}
}

void Bst::updateHeight(Node* start) {
	if (start == mRoot) start->height = 0;
	if (start->left) {
		start->left->height = start->height +1;
		updateHeight(start->left);
	}
	if (start->right) {
		start->right->height = start->height +1;
		updateHeight(start->right);
	}
}
