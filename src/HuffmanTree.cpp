//
// Created by mahee on 2019-03-11.
//

#include "HuffmanTree.h"
#include <iostream>


HuffmanTree::HuffmanTree(unsigned weight, char c) {
    root = new Node(c);
    this->weight = weight;
    this->height = 0;
}
HuffmanTree::HuffmanTree(const HuffmanTree &a, const HuffmanTree &b) {
    this->weight = a.weight + b.weight;
    this->height = (a.height > b.height) ? a.height:b.height +1;
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
    this->left = nullptr;
    this->right = nullptr;
}
void HuffmanTree::Node::attachNodes(HuffmanTree::Node *left, HuffmanTree::Node *right) {
    this->left = left;
    this->right = right;
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

void HuffmanTree::populateHuffCodeTable(std::string *table){
    char s[height];
    codeTab(root,s,0,table);
}

void HuffmanTree::codeTab(HuffmanTree::Node* root, char* s,unsigned n,std::string table[128]) {
    if(root->getVal() != 0){
        std::string code;
        s[n] = 0;
        code = s;
        table[root->getVal()] = s;
        return;
    }

    s[n]= '0';
    codeTab(root->getLeft(),s,n+1,table);

    s[n] = '1';
    codeTab(root->getRight(),s,n+1,table);

}

