#include <iostream>
#include <sstream>
#include <string>
#include "avl.h"

int main()
{
  AVL *obj = new AVL;
  Node *root = nullptr;
  obj->Interface();

  std::string input = "Yuh";

  int num = 2;
  root = obj->Insert(root, input, num);
  num = 1;
  root = obj->Insert(root, input, num);

  num = 3;
  root = obj->Insert(root, input, num);

  num = 4;
  root = obj->Insert(root, input, num);

  num = 5;
  root = obj->Insert(root, input, num);

  // num = 6;
  // root = obj->Insert(root, input, num);
  int sum = 4;
  obj->Preorder(root);
  std::cout << std::endl;
  obj->Delete(root, sum);
  obj->Preorder(root);

  return 0;
}