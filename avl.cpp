#include "avl.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <functional>

// Rotates the nodes left
Node* AVL::RotateLeft(Node* root)
{
    Node* grandchild = root->right->left;
    Node* parent = root->right;
    parent->left = root;
    root->right = grandchild;
    root->height = (1 + std::max(HeightOfNode(root->left), HeightOfNode(root->right)));
    parent->height = (1 + std::max(HeightOfNode(parent->left), HeightOfNode(parent->right)));
    return parent;
}

// Rotates the nodes right. Also keeps any children that the rotated node has
Node* AVL::RotateRight(Node* root)
{
    Node* grandchild = root->left->right;
    Node* parent = root->left;
    parent->right = root;
    root->left = grandchild;
    root->height = (1 + std::max(HeightOfNode(root->left), HeightOfNode(root->right)));
    parent->height = (1 + std::max(HeightOfNode(parent->left), HeightOfNode(parent->right)));
    return parent;
}

// First rotates the nodes left, then right. Keeps the children that the rotated node has
Node* AVL::RotateRightLeft(Node* root)
{
    root->right = RotateRight(root->right);
    return RotateLeft(root);
}

// First rotates the nodes right, then left
Node* AVL::RotateLeftRight(Node* node)
{
    node->left = RotateLeft(node->left);
    return RotateRight(node);
}

// Returns the height of the node, which prevents segfaults due to root potentially being a nullptr
int AVL::HeightOfNode(Node* root)
{
    if (root == nullptr)
        return 0;
    return root->height;
}

// Finds the balance factor for the node
int AVL::BalanceFactor(Node* root)
{
    if (root == nullptr)
        return 0;
    return HeightOfNode(root->left) - HeightOfNode(root->right);
}

// Inserts a particular node
Node* AVL::Insert(Node* root, std::string& name, int& id)
{
    if (root == nullptr)
    {
        std::cout << "successful" << std::endl;
        return new Node(name, id);
    }

    if (id < root->id)
        root->left = Insert(root->left, name, id);
    else if (id > root->id)
        root->right = Insert(root->right, name, id);
    else
    {
        std::cout << "unsuccessful" << std::endl;
        return root;
    }

    root->height = (1 + std::max(HeightOfNode(root->left), HeightOfNode(root->right))); // updates the height of all of the nodes

    // checks to see if the tree is balanced. If not, makes appropriate adjustments
    if (BalanceFactor(root) > 1)
        if (BalanceFactor(root->left) >= 0)
            return RotateRight(root);
        else
            return RotateLeftRight(root);

    else if (BalanceFactor(root) < -1)
        if (BalanceFactor(root->right) > 0)
            return RotateRightLeft(root);
        else
            return RotateLeft(root);

    return root;
}

// prints tree inorderly
void AVL::Inorder(Node* root)
{
    if (root == nullptr)
        return;
    Inorder(root->left);
    if (root->left != nullptr)
        std::cout << ", ";
    std::cout << root->name;
    if (root->right != nullptr)
        std::cout << ", ";
    Inorder(root->right);
}

// prints the tree preorderly
void AVL::Preorder(Node* root)
{
    if (root == nullptr)
        return;
    std::cout << root->name;
    if (root->left != nullptr || root->right != nullptr)
        std::cout << ", ";
    Preorder(root->left);
    if (root->left != nullptr && root->right != nullptr)
        std::cout << ", ";
    Preorder(root->right);
}

// prints the tree postorderly
void AVL::Postorder(Node* root)
{
    if (root == nullptr)
        return;
    Postorder(root->left);
    if (root->left != nullptr)
        std::cout << ", ";
    Postorder(root->right);
    if (root->right != nullptr)
        std::cout << ", ";
    std::cout << root->name;
}

// seraches the tree for a given id. Prints "unsuccessful" if id is not located
Node* AVL::SearchID(Node* root, int& id)
{
    if (root == nullptr)
    {
        std::cout << "unsuccessful" << std::endl;
        return root;
    }
    else if (root->id == id)
    {
        std::cout << root->name << std::endl;
        return root;
    }
    else if (id < root->id)
        return SearchID(root->left, id);
    else if (id > root->id)
        return SearchID(root->right, id);
}

// searches the entire tree for all the given name. Prints "unsucessful" if name is not located
Node* AVL::SearchName(Node* root, std::string& name, bool found)
{
    if (root == nullptr)
    {
        if (found == false)
            std::cout << "unsuccessful" << std::endl;
        return root;
    }
    else if (root->name == name)
    {
        found = true;
        std::cout << root->id << std::endl;
    }
    SearchName(root->left, name, found);
    SearchName(root->right, name, found);
}

// returns the level count, i.e. the height of the root
int AVL::PrintLevelCount(Node* root)
{
    return root->height;
}

// help function to find the leftmost node in a subtree/tree
Node* AVL::LeftMostNode(Node* root)
{
    Node* current = root;

    while (current->left != nullptr)
        current = current->left;
    return current;
}

// deletes a node from the tree after finding a certain id, and balances the tree
Node* AVL::Delete(Node* root, int id)
{
    if (root == nullptr)
    {
        std::cout << "unsuccessful" << std::endl;
        return root;
    }

    if (id < root->id)
        root->left = Delete(root->left, id);
    else if (id > root->id)
        root->right = Delete(root->right, id);
    else
    if (root->right == nullptr || root->left == nullptr)
    {
        Node* temp = root->left ? root->left : root->right;

        if (temp == nullptr)
        {
            temp = root;
            root = nullptr;
        }

        else
        {
            *root = *temp;
            free(temp);
        }
    }
    else
    {

        Node* temp = LeftMostNode(root->right);
        root->id = temp->id;
        root->name = temp->name;
        root->height = temp->height;

        root->right = Delete(root->right, temp->id);
    }

    if (root == nullptr)
        return root;

    root->height = (1 + std::max(HeightOfNode(root->left), HeightOfNode(root->right)));

    if (BalanceFactor(root) > 1)
        if (BalanceFactor(root->left) >= 0)
            return RotateRight(root);
        else
            return RotateLeftRight(root);

    else if (BalanceFactor(root) < -1)
        if (BalanceFactor(root->right) <= 0)
            return RotateLeft(root);
        else
            return RotateRightLeft(root);


    return root;
}

// helper function to print out if function is successful or not
void PrintSuccessful(bool success)
{
    if (success)
        std::cout << "successful" << std::endl;
    else
        std::cout << "unsuccessful" << std::endl;
}

// removes the n-th node in order
Node* AVL::InorderRemoval(Node*& root, int n, bool& removed)
{
    static int count = 0;
    if (root == nullptr)
        return root;
    if (count <= n)
    {
        InorderRemoval(root->left, n, removed);
        if (count == n)
        {
            root = Delete(root, root->id);
            removed = true;
            return root;
        }
        count++;
        InorderRemoval(root->right, n, removed);
    }
    return root;
}

// valids and checks to see if name only consists of letters
bool AVL::ValidateName(std::string& name)
{
    std::regex obj = std::regex("^[A-Za-z\\s]+$");
    return regex_search(name, obj);
}

// valids and checks if the input is a digit and has 8 numbers
bool AVL::ValidateID(std::string& id)
{
    if (id.length() < 8)
        return false;
    else
    {
        for (char const& c : id)
            if (std::isdigit(c) == 0)
                return false;
        return true;
    }
}

// helper function that returns if the id/node exists
bool AVL::Search(Node* root, int& id)
{
    if (root == nullptr)
        return false;

    if (root->id == id)
        return true;

    bool left = Search(root->left, id);

    if (left)
        return true;

    bool right = Search(root->right, id);

    return right;
}

// helper function to find the size of tree 
int AVL::Size(Node* root)
{
    static int count = 0;
    if (root == nullptr)
        return 0;
    return(Size(root->left) + 1 + Size(root->right));
}

// takes the inputs of the commands and does the appropriate tasks
void AVL::Interface(Node*& root)
{
    int numOfLines;
    std::cin >> numOfLines;
    std::cin.ignore(1, '\n');

    for (int i = 0; i < numOfLines; i++)
    {
        std::string input;
        std::getline(std::cin, input);

        std::stringstream inputStream(input);

        std::string command;
        inputStream >> command;

        if (command == "insert")
        {
            std::string next;
            getline(inputStream, next, '"');
            getline(inputStream, next, '"');
            if (!ValidateName(next))
                std::cout << "unsuccessful" << std::endl;
            else
            {
                std::string idStr;
                inputStream >> idStr;
                if (!ValidateID(idStr))
                    std::cout << "unsucessful" << std::endl;
                else
                {
                    int id = stoi(idStr);
                    root = Insert(root, next, id);
                }
            }
        }
        else if (command == "remove")
        {
            std::string idStr;
            inputStream >> idStr;
            if (!ValidateID(idStr))
                std::cout << "unsuccessful" << std::endl;
            else
            {
                int id = stoi(idStr);
                if (!Search(root, id))
                    std::cout << "unsuccessful" << std::endl;
                else
                {
                root = Delete(root, id);
                std::cout << "successful" << std::endl;
                }
            }
        }
        else if (command == "search")
        {
            std::string next;
            getline(inputStream, next, '"');
            getline(inputStream, next, '"');
            next.erase(next.begin(), std::find_if(next.begin(), next.end(), std::bind1st(std::not_equal_to<char>(), ' '))); // removes any leading spaces
            if (!ValidateID(next))
                SearchName(root, next, false);
            else
            {
                int id = stoi(next);
                SearchID(root, id);
            }
        }
        else if (command == "printInorder")
        {
            if (root == nullptr)
                std::cout << "unsuccessful" << std::endl;
            else {
                Inorder(root);
                std::cout << std::endl;
            }
        }
        else if (command == "printPreorder")
        {
            if (root == nullptr)
                std::cout << "unsuccessful" << std::endl;
            else {
                Preorder(root);
                std::cout << std::endl;
            }
        }
        else if (command == "printPostorder")
        {
            if (root == nullptr)
                std::cout << "unsuccessful" << std::endl;
            else {
                Postorder(root);
                std::cout << std::endl;
            }
        }
        else if (command == "printLevelCount")
            if (root==nullptr)
                std::cout << "0" << std::endl;
            else
            std::cout << PrintLevelCount(root) << std::endl;
        else if (command == "removeInorder")
        {
            std::string next;
            inputStream >> next;
            int num = stoi(next);
            if (num >= Size(root))
                std::cout << "unsuccessful" << std::endl;
            else
            {
                bool found = false;
                root = InorderRemoval(root, num, found);
                PrintSuccessful(found);
            }
        }
        else
            std::cout << "unsuccessful" << std::endl;
    }
}