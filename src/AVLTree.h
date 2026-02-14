//
// Created by Sanaa Chetal on 2/12/26.
//

#ifndef PROJECT1_AVLTREE_H
#define PROJECT1_AVLTREE_H
#include <string>
using namespace std;

class AVLTree {
    private:
    struct TreeNode {
        int ufid;
        string name;
        int height;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int id, string name): ufid(id), name(name), height(0), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    void heighthelper(TreeNode *node);
    void balancehelper(TreeNode *node, string direction);

    public:

    AVLTree();
    ~AVLTree();
    bool insert(int id, string name);
    bool remove(int id);
    bool search(int id);
    bool search(string name);
    vector<int>  printInOrder();
    vector<int> printPreOrder();
    vector<int> printPostOrder();
    void printLevelOrder();
    void removeInOrder();

};

#endif //PROJECT1_AVLTREE_H