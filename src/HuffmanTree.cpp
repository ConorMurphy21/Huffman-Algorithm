//
// Created by mahee on 2019-03-11.
//

#include "HuffmanTree.h"


HuffmanTree::HuffmanTree(int weight, char c) {
    root = new Node(c);
    this->weight = weight;
}
HuffmanTree::HuffmanTree(const HuffmanTree &a, const HuffmanTree &b) {
    this->weight = a.weight + b.weight;
    this->root = new Node(0);
    this->root->attachNodes(a.root,b.root);
}
bool operator<(const HuffmanTree &a, const HuffmanTree &b) {
    return a.weight < b.weight;
}

HuffmanTree::Node::Node(char val) {
    this->val = val;
}
void HuffmanTree::Node::attachNodes(HuffmanTree::Node *left, HuffmanTree::Node *right) {
    this->left = left;
    this->right = right;
    left->parent = this;
    right->parent = this;
}
