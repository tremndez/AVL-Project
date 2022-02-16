#pragma once

#include <string>

struct Node
{
  Node *left;
  Node *right;
  int height, id;
  std::string name;
  Node(std::string(y), int(x)) : id(x), name(y), height(1), left(nullptr), right(nullptr) {}
};

class AVL
{
  Node *RotateLeft(Node *);
  Node *RotateRight(Node *);
  Node *RotateLeftRight(Node *);
  Node *RotateRightLeft(Node *);

  int HeightOfNode(Node *);
  int BalanceFactor(Node *);
  Node *LeftMostNode(Node *);

  bool ValidateName(std::string &);
  bool ValidateID(std::string &);

public:
  void Interface(Node *);

  Node *Insert(Node *, std::string &, int &);
  Node *Delete(Node *, int);
  Node *InorderRemoval(Node *, int);

  Node *SearchID(Node *, int &);
  Node *SearchName(Node *, std::string &, bool);
  int PrintLevelCount(Node *);

  void Inorder(Node *);
  void Preorder(Node *);
  void Postorder(Node *);
};
