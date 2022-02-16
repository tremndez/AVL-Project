#pragma once

#include <string>

struct Node
{
	Node* left;
	Node* right;
	int height, id;
	std::string name;
	Node(std::string(y), int(x)) : id(x), name(y), height(1), left(nullptr), right(nullptr) {}
};

class AVL
{
	Node* RotateLeft(Node*);
	Node* RotateRight(Node*);
	Node* RotateLeftRight(Node*);
	Node* RotateRightLeft(Node*);

	int HeightOfNode(Node*);
	int BalanceFactor(Node*);
	Node* LeftMostNode(Node*);

	bool ValidateName(std::string&);
	bool ValidateID(std::string&);

	Node* Insert(Node*, std::string&, int&);
	Node* Delete(Node*, int);
	Node* InorderRemoval(Node*&, int, bool&);

	Node* SearchID(Node*, int&);
	Node* SearchName(Node*, std::string&, bool);
	int PrintLevelCount(Node*);

	void Inorder(Node*);
	void Preorder(Node*);
	void Postorder(Node*);

	int Size(Node*);
	bool Search(Node*, int&);


public:
	void Interface(Node*&);
};
