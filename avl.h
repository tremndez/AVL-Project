#include <string>
struct Node
{
  Node *left;
  Node *right;
  int height, id;
  std::string name;
  Node(int, std::string);
};