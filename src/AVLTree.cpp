//
// Created by Sanaa Chetal on 2/12/26.
//
#include <iostream>
#include <regex>
#include "AVLTree.h"
using namespace std;

AVLTree::AVLTree(): root(nullptr) {}

AVLTree::~AVLTree() {

}


int AVLTree::heighthelper(TreeNode *node) {
    //Loosely found height code in lecture slides
    //Used to find height of individual nodes
    if (node == nullptr) {
        return 0;
    }
    return  1 + max(heighthelper(node->left), heighthelper(node->right));
}

int AVLTree::balancehelper(TreeNode *node) {
    //Calculates the balance value for any given node
    TreeNode* current = node;
    int leftHeight = 0;
    int rightHeight = 0;

    if (current == nullptr) {return 0;}

    if (current->left == nullptr) {leftHeight = 0;}
    else{leftHeight = current->left->height;}

    if (current->right == nullptr) {rightHeight = 0;}
    else{rightHeight = current->right->height;}

    int balance = leftHeight - rightHeight;

    return balance;
}

AVLTree::TreeNode* AVLTree::insertHelper(TreeNode* node, int id, string name) {
    //Code found on lecture slides
    //Actually inserts node and updates all heights affected upon insertion
    if (node == nullptr) {
        return new TreeNode(id, name);
    }

    if (id < node->ufid) {
        node->left = insertHelper(node->left, id, name);
    }

    else if (id > node->ufid) {
        node->right = insertHelper(node->right, id, name);
    }

    node->height = heighthelper(node);

    //Balances any affected nodes
    int balance = balancehelper(node);
    int left = balancehelper(node->left);
    int right = balancehelper(node->right);

    if (balance > 1 && left == 1) {
        return RRotation(node);
    }

    if (balance > 1 && left == -1) {
        return LRRotation(node);
    }

    if (balance < -1 && right == -1) {
        return LRotation(node);
    }

    if (balance < -1 && right == 1) {
        return RLRotation(node);
    }

    return node;
}

AVLTree::TreeNode* AVLTree::LRotation(TreeNode* node) {
    //code found from lecture slides
    TreeNode* grandchild = node->right->left;
    TreeNode* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;

    //Recalculating height after rotation
    node->height = heighthelper(node);
    newParent->height = heighthelper(newParent);
    return newParent;
}

AVLTree::TreeNode* AVLTree::RRotation(TreeNode* node) {
    //mirrored code from above
    TreeNode* grandchild = node->left->right;
    TreeNode* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;

    //Recalculating height after rotation
    node->height = heighthelper(node);
    newParent->height = heighthelper(newParent);
    return newParent;
}
AVLTree::TreeNode* AVLTree::LRRotation(TreeNode* node) {
    node->left = LRotation(node->left);
    return RRotation(node);

}
AVLTree::TreeNode* AVLTree::RLRotation(TreeNode* node) {
    node->right = RRotation(node->right);
    return LRotation(node);

}

bool AVLTree::insert(int id, string name) {
    //Check if ID is valid input
    if (id < 10000000 || id > 99999999 ) {
        cout << "unsuccessful" << endl;
        return false;
    }
    //Check if name is valid input
    regex obj("^[a-zA-Z\\s]+$");
    if (!regex_match(name, obj)){
        cout << "unsuccessful" << endl;
        return false;
    }

    //Check if ufid is found anywhere else
    TreeNode* current = this->root;
    while (current != nullptr) {
        if (id == current->ufid) {
            cout << "unsuccessful" << endl;
            return false;
        }
        else if (id < current->ufid) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    //Reassign the root node
    this->root = insertHelper(this->root, id, name);
    //Note for Sunny, remove this print statement before you turn in
    cout << this->root->ufid << this->root->name << endl;
    cout << "successful" << endl;
    return true;
}

bool AVLTree::remove(int id) {
    //Reworked code from my printinorder to check ID inorder
    TreeNode* current = this->root;
    stack<TreeNode*> s;
    while (current != nullptr || !s.empty()) {
        while(current != nullptr) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        //Checks each node for id
        if (id == current->ufid) {
           break;
        }
        s.pop();
        current = current->right;
    }
    if (current->left == nullptr && current->right == nullptr) {
        delete current;
    }
    else if (current->left == nullptr || current->right == nullptr) {
        if (current->left != nullptr) {
            //link parent to child
            delete current;
        }
        if (current->right != nullptr) {
            //link parent to child
            delete current;
        }
    }
    else if (current->left != nullptr && current->right != nullptr) {

    }
    return false;
}
bool AVLTree::search(int id) {
    //Reworked code from insert when checking for duplicates to check ID inorder
    TreeNode* current = this->root;
    while (current != nullptr) {
        if (id == current->ufid) {
            cout << current->name << endl;
            return true;
        }
        else if (id < current->ufid) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    //No nodes were found with id
    cout << "unsuccessful" << endl;
    return false;
}
bool AVLTree::search(string name) {
    //Reworked code from my printpreorder to check for instances of name
    bool found = false;
    TreeNode* current = this->root;
    stack<TreeNode*> s;
    vector<int> result;
    while (current != nullptr || !s.empty()) {
        while(current != nullptr) {
            result.push_back(current->ufid);
            //If name found will print ufid
            if (name == current->name) {
                cout<< current->ufid <<endl;
                found = true;
            }
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        current = current->right;
    }
    return found;
}

vector<int>  AVLTree::printInOrder() {
    //Using stack iteration to also be able to return vector for testing
    TreeNode* current = this->root;
    stack<TreeNode*> s;
    vector<int> result;
    //Loop to check both right and left children
    while (current != nullptr || !s.empty()) {
        //Loop to check left children
        while(current != nullptr) {
            s.push(current);
            current = current->left;
        }
            current = s.top();
            s.pop();
            result.push_back(current->ufid);
            if (current->ufid == result[0]) {
                cout<< current->name <<"";
            }
            else {
                cout << ", " << current->name <<"";
            }
            //move to check right children in outer loop
            current = current->right;
    }
    return result;
}

vector<int> AVLTree::printPreOrder() {
    TreeNode* current = this->root;
    stack<TreeNode*> s;
    vector<int> result;
    while (current != nullptr || !s.empty()) {
        while(current != nullptr) {
            result.push_back(current->ufid);
            if (current->ufid == result[0]) {
                cout<< current->name <<"";
            }
            else {
                cout << ", " << current->name <<"";
            }
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        current = current->right;
    }
    return result;

}

vector<int> AVLTree::printPostOrder() {
    vector<int> result = {1, 2, 3};
    return result;
}

void AVLTree::printLevelOrder() {
    if (this->root == nullptr) {
        cout << "0" << endl;
    }
    else {
        int maxHeight = heighthelper(this->root);
        cout << maxHeight << endl;
    }
}

void AVLTree::removeInOrder(int N) {
//Use inorder print to return vector of item then remove by uf id
}