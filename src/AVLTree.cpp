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

bool AVLTree::insert(string ufid, string name) {

    //Check if ID is valid input
    //Searched up to know how to multiply [0-9] by 8
    regex obj = regex("^[0-9]{8}$");
    if (!regex_match(ufid, obj)) {
        cout << "unsuccessful" << endl;
        return false;
    }

    //Check if name is valid input
    regex obj2("^[a-zA-Z\\s]+$");
    if (!regex_match(name, obj2)){
        cout << "unsuccessful" << endl;
        return false;
    }

    int id = stoi(ufid);

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
    cout << "successful" << endl;
    return true;
}

bool AVLTree::remove(int id) {
    if (this->root == nullptr) {
        return false;
    }

    //Reworked code from my insert to check ID inorder and capture parent node
    TreeNode* parent = nullptr;
    TreeNode* current = this->root;
    bool found = false;

    while (current != nullptr) {
        if (id == current->ufid) {
            found = true;
            break;
        }
        parent = current;
        if (id < current->ufid) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (!found) {
        cout << "unsuccessful" << endl;
        return false;
    }
    //No children case
    if (current->left == nullptr && current->right == nullptr && found) {
        //if node to remove is root
        if (current == this->root) {this->root = nullptr;}
        else if (parent->left == current){ parent->left = nullptr;}
        else if (parent->right == current){ parent->right = nullptr;}
        delete current;
        cout << "successful" << endl;
        return true;
    }
    //One child case
    else if ((current->left == nullptr || current->right == nullptr) && found) {
        //if node to remove is root
        if (current == this->root) {
            if (current->left != nullptr) {
                this->root = this->root->left;
                delete current;
                cout << "successful" << endl;
                return true;
            }
            if (current->right != nullptr) {
                this->root = this->root->right;
                delete current;
                cout << "successful" << endl;
                return true;
            }
        }
        else if (current->left != nullptr) {
            if (parent->left == current) {
                parent->left = current->left;
                delete current;
                cout << "successful" << endl;
                return true;
            }
            else {
                parent->right = current->left;
                delete current;
                cout << "successful" << endl;
                return true;
            }
        }

        else if (current->right != nullptr) {
            if (parent->right == current) {
                parent->right = current->right;
                delete current;
                cout << "successful" << endl;
                return true;
            }
            else {
                parent->left = current->right;
                delete current;
                cout << "successful" << endl;
                return true;
            }
        }
    }

    //Two child case
    else if (current->left != nullptr && current->right != nullptr) {

        // Find inorder successor
        TreeNode* successor = current->right;
        TreeNode* successorParent = current;

        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }


        current->ufid = successor->ufid;
        current->name = successor->name;

        // Remove copied successor node safely
        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }

        delete successor;

        cout << "successful" << endl;
        return true;
    }

    cout << "unsuccessful" << endl;
    return false;
}

bool AVLTree::search(int id) {
    //Reworked code from insert when checking for duplicates to check ID inorder
    string ufid = to_string(id);
    while (ufid.length() < 8) {
        ufid = "0" + ufid;
    }
    regex obj = regex("^[0-9]{8}$");
    if (!regex_match(ufid, obj)) {
        cout << "unsuccessful" << endl;
        return false;
    }

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
    regex obj2("^[a-zA-Z\\s]+$");
    if (!regex_match(name, obj2)){
        cout << "unsuccessful" << endl;
        return false;
    }

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
                string id = to_string(current->ufid);
                while (id.length() < 8) {
                    id = "0" + id;
                }
                cout<< id <<endl;
                found = true;
            }
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        current = current->right;
    }
    if (!found) {
        cout << "unsuccessful" << endl;
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
            if (result.size() == 0) {
                cout<< current->name <<"";
            }
            else {
                cout << ", " << current->name <<"";
            }
            result.push_back(current->ufid);
            //move to check right children in outer loop
            current = current->right;
    }
    cout<< endl;
    return result;
}

vector<int> AVLTree::printPreOrder() {
    TreeNode* current = this->root;
    stack<TreeNode*> s;
    vector<int> result;
    while (current != nullptr || !s.empty()) {
        while(current != nullptr) {
            if (result.size() == 0) {
                cout<< current->name <<"";
            }
            else {
                cout << ", " << current->name <<"";
            }
            result.push_back(current->ufid);
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        current = current->right;
    }
    cout << endl;
    return result;

}

vector<int> AVLTree::printPostOrder() {
    TreeNode* current = this->root;
    stack<TreeNode*> s, collector;
    vector<int> result;
    if (current == nullptr) {
        cout << endl;
        return result;
    }
    s.push(current);
        while(!s.empty()) {
            current = s.top();
            collector.push(current);
            s.pop();
            if (current->left != nullptr) {s.push(current->left);}
            if (current->right != nullptr) {s.push(current->right);}
        }
        while (!collector.empty()) {
            current = collector.top();
            if (result.size() ==  0) {
                cout<< current->name <<"";
            }
            else {
                cout << ", " << current->name <<"";
            }
            result.push_back(current->ufid);
            collector.pop();
        }
    cout << endl;
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

bool AVLTree::removeInOrder(int N) {
    //Altered print inorder code to collect vector of inorder TreeNodes
    if (N < 0) {
        cout << "unsuccessful" << endl;
        return false;
    }
    TreeNode* current = this->root;
    stack<TreeNode*> s;
    vector<TreeNode*> nodes;
    while (current != nullptr || !s.empty()) {
        while(current != nullptr) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        nodes.push_back(current);
        current = current->right;
    }
    if (N > (int)nodes.size() - 1) {
        cout << "unsuccessful" << endl;
        return false;
    }
    //Get id of Nth node and call remove using id
    int id = nodes[N]->ufid;
    bool success = remove(id);
    return success;

}
