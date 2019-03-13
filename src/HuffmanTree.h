//
// Created by mahee on 2019-03-11.
//


#pragma once

#include <string>

class HuffmanTree {

private:

    unsigned weight;

    class Node{
    private:
        Node* left;
        Node* right;
        Node* parent;
        char val;
    public:
        Node(char val);
        void attachNodes(Node* a, Node* b);
        char getVal();
        Node* getLeft();
        Node* getRight();
        Node* getParent();
    };

    Node* root;

    void printTab(Node* root, char s[100],unsigned n);

public:

    HuffmanTree(const HuffmanTree& a,const HuffmanTree &b);

    HuffmanTree(unsigned weight, char c);

    HuffmanTree();

    void printTable();

    friend bool operator < (const HuffmanTree& a, const HuffmanTree& b);
    friend bool operator <= (const HuffmanTree& a, const HuffmanTree& b);

};


