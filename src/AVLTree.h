//
// Created by Sanaa Chetal on 2/12/26.
//

#ifndef PROJECT1_AVLTREE_H
#define PROJECT1_AVLTREE_H
#include <string>
#include <vector>
using namespace std;

class AVLTree {
    private:
    struct TreeNode {
        int ufid;
        string name;
        int height;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int id, string name): ufid(id), name(name), height(1), left(nullptr), right(nullptr) {}
    };


    int heighthelper(TreeNode *node);
    int balancehelper(TreeNode *node);
    TreeNode* insertHelper(TreeNode *node, int id, string name);
    TreeNode* LRotation(TreeNode *node);
    TreeNode* RRotation(TreeNode *node);
    TreeNode* LRRotation(TreeNode *node);
    TreeNode* RLRotation(TreeNode *node);


    public:

    TreeNode* root;

    AVLTree();
    ~AVLTree();
    bool insert(string id, string name);
    bool remove(int id);
    bool search(int id);
    bool search(string name);
    vector<int>  printInOrder();
    vector<int> printPreOrder();
    vector<int> printPostOrder();
    void printLevelOrder();
    bool removeInOrder(int N);

};

#endif //PROJECT1_AVLTREE_H