//
// Created by mahee on 2019-03-11.
//

#include "HuffmanTree.h"
#include <iostream>


HuffmanTree::HuffmanTree(unsigned weight, unsigned char c) {
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
HuffmanTree::Node::Node(unsigned char val) {
    this->val = val;
    this->left = nullptr;
    this->right = nullptr;
}
void HuffmanTree::Node::attachNodes(HuffmanTree::Node *left, HuffmanTree::Node *right) {
    this->left = left;
    this->right = right;
}

unsigned char HuffmanTree::Node::getVal() {
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

char HuffmanTree::getChar(std::ifstream& in, bool* done){
    static char c;
    static short n = 8;

    HuffmanTree::Node* node = root;

    for( ; ; ) {
        if(node->getVal() != 0){
            if(node->getVal() == 128) *done = true;
            return node->getVal();
        }

        if(n >= 8){
            if(!in.get(c)){
                *done = true;
                return 0;
            }
            n = 0;
        }

        int path = 0x80 & c;
        if (path)
            node = node->getRight();
        else
            node = node->getLeft();
        c <<= 1;

        n++;
    }

}

void HuffmanTree::codeTab(HuffmanTree::Node* root, char* s,unsigned n,std::string table[129]) {
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

