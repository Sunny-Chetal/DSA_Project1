//
// Created by Sanaa Chetal on 2/12/26.
//
#include <iostream>
#include <regex>
#include "AVLTree.h"
using namespace std;

AVLTree::AVLTree() {
    root = nullptr;
}

AVLTree::~AVLTree() {

}


void AVLTree::heighthelper(TreeNode *node) {

}

void AVLTree::balancehelper(TreeNode *node, string direction) {

}

bool AVLTree::insert(int id, string name) {
    return false;
}

bool AVLTree::remove(int id) {
    return true;
}
bool AVLTree::search(int id) {
    return true;
}
bool AVLTree::search(string name) {
    return true;
}
vector<int>  AVLTree::printInOrder() {
    vector<int> result = {1, 2, 3};
    return result;
}
vector<int> AVLTree::printPreOrder() {
    vector<int> result = {1, 2, 3};
    return result;
}
vector<int> AVLTree::printPostOrder() {
    vector<int> result = {1, 2, 3};
    return result;
}
void AVLTree::printLevelOrder() {

}
void AVLTree::removeInOrder() {

}