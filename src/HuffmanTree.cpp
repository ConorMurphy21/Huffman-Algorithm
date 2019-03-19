
/* File name : Hufmmantree.cpp
 * Desc : A special implementation of the binary tree, Used to encode and decode each occurrence in binary to compress files.
 * Uses the "Huffman Algorithm"  published by Huffman in 1952.
 *
 * made by - Maheeppartap Singh and Conor Murphy
 */


//Header files
#include "HuffmanTree.h"
#include <iostream>

//Start Node Methods

// Node constructor with a value
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

//Attaching two nodes given their addresses
void HuffmanTree::Node::attachNodes(HuffmanTree::Node *left, HuffmanTree::Node *right) {
    this->left = left;
    this->right = right;
}

//Returns the value of the node
unsigned short HuffmanTree::Node::getVal() {
    return val;
}

//returns the address of the left node.
HuffmanTree::Node* HuffmanTree::Node::getLeft() {
    return left;
}

//returns the address of the right node
HuffmanTree::Node* HuffmanTree::Node::getRight() {
    return right;
}

// Constructor with weight and character
HuffmanTree::HuffmanTree(unsigned weight, unsigned short c) {
    root = new Node(c);
    this->weight = weight;
    this->height = 0;
}

// constructor with two trees and joining them together
HuffmanTree::HuffmanTree(const HuffmanTree& a, const HuffmanTree& b) {
    this->weight = a.weight + b.weight;
    this->height = (a.height > b.height) ? a.height+1:b.height+1;
    this->root = new Node(512);
    Node* an = new Node(a.root);
    Node* bn = new Node(b.root);
    this->root->attachNodes(an,bn);
}
//End Node Methods

//start Tree methods
//Default constructor
HuffmanTree::HuffmanTree() {
    this->weight = 0;
    this->root = NULL;
}

//Poppulate the code table recursively
void HuffmanTree::populateHuffCodeTable(std::string *table){
    char s[height];
    codeTab(root,s,0,table);
}

//Gets the next char from the tree to decode
char HuffmanTree::getChar(std::ifstream& in, bool* done){
    static char c;
    static short n = 8;
    HuffmanTree::Node* node = root;
    for( ; ; ) {
        if(node->getVal() != TNODEVAL){//check if node is not 0
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

//Used to put the poppulate the tree
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

//Overloading < operator to compare the weights
bool operator<(const HuffmanTree &a, const HuffmanTree &b) {
    return a.weight < b.weight;
}

//overloading the <= operator to compare weights
bool operator<=(const HuffmanTree &a, const HuffmanTree &b) {
    return a.weight <= b.weight;
}

//End of HuffmanTree.cpp