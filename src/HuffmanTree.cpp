//
// Created by mahee on 2019-03-11.
//

#include "HuffmanTree.h"
#include <iostream>


HuffmanTree::HuffmanTree(unsigned weight, unsigned short c) {
    root = new Node(c);
    this->weight = weight;
    this->height = 0;
}
HuffmanTree::HuffmanTree(const HuffmanTree& a, const HuffmanTree& b) {
    this->weight = a.weight + b.weight;
    this->height = (a.height > b.height) ? a.height+1:b.height+1;
    this->root = new Node(512);
    Node* an = new Node(a.root);
    Node* bn = new Node(b.root);
    this->root->attachNodes(an,bn);
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
HuffmanTree::Node::Node(unsigned short val) {
    this->val = val;
    this->left = nullptr;
    this->right = nullptr;
}

HuffmanTree::Node::Node(HuffmanTree::Node *node) {
    this->val = node->getVal();
    if(val == TNODEVAL) {
        this->left = new Node(node->getLeft());
        this->right = new Node(node->getRight());
    }
}


void HuffmanTree::Node::attachNodes(HuffmanTree::Node *left, HuffmanTree::Node *right) {
    this->left = left;
    this->right = right;
}

unsigned short HuffmanTree::Node::getVal() {
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
        if(node->getVal() != TNODEVAL){
            if(node->getVal() == EOFVAL) *done = true;
            return (char)node->getVal();
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

HuffmanTree::~HuffmanTree() {
    //deleteStuff(root);
}

void HuffmanTree::deleteStuff(HuffmanTree::Node* root){
    if(root->getVal() == TNODEVAL) {
        deleteStuff(root->getLeft());
        deleteStuff(root->getLeft());
    }
    delete root;
}

void HuffmanTree::codeTab(HuffmanTree::Node* root, char* s,unsigned n,std::string* table) {

    if(root->getVal() != TNODEVAL){
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

