//
// Created by mahee on 2019-03-11.
//

#include "HuffmanTree.h"
#include <iostream>


HuffmanTree::HuffmanTree(unsigned weight, char c) {
    root = new Node(c);
    this->weight = weight;
}
HuffmanTree::HuffmanTree(const HuffmanTree &a, const HuffmanTree &b) {
    this->weight = a.weight + b.weight;
    this->root = new Node(0);
    this->root->attachNodes(a.root,b.root);
}
HuffmanTree::HuffmanTree() {
    this->weight = 0;
    this->root = NULL;
}
bool operator<(const HuffmanTree &a, const HuffmanTree &b) {
    return a.weight < b.weight;
}

bool operator<=(const HuffmanTree &a, const HuffmanTree &b) {
    return a.weight <= b.weight;
}
HuffmanTree::Node::Node(char val) {
    this->val = val;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
void HuffmanTree::Node::attachNodes(HuffmanTree::Node *left, HuffmanTree::Node *right) {
    this->left = left;
    this->right = right;
    left->parent = this;
    right->parent = this;
}

char HuffmanTree::Node::getVal() {
    return val;
}

HuffmanTree::Node* HuffmanTree::Node::getLeft() {
    return left;
}
HuffmanTree::Node* HuffmanTree::Node::getRight() {
    return right;
}
HuffmanTree::Node* HuffmanTree::Node::getParent() {
    return parent;
}
void HuffmanTree::printTable() {
    char s[100];
    printTab(root,s,0);
}

void HuffmanTree::printTab(HuffmanTree::Node* root, char s[100],unsigned n) {
    if(root->getVal() != 0){
        std::cout << root->getVal() << " : ";
        for(int i = 0; i < n; i++)printf("%c",s[i]);

        printf("\n");
        return;
    }

    s[n]= '0';
    printTab(root->getLeft(),s,n+1);

    s[n] = '1';
    printTab(root->getRight(),s,n+1);


}

