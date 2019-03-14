//
// Created by mahee on 2019-03-11.
//


#pragma once

#include <string>

class HuffmanTree {

private:

    unsigned weight;
    unsigned height;

    class Node{
    private:
        Node* left;
        Node* right;
        char val;
    public:
        Node(char val);
        void attachNodes(Node* a, Node* b);
        char getVal();
        Node* getLeft();
        Node* getRight();
    };

    Node* root;

    void codeTab(Node* root, char *s,unsigned n,std::string str[128]);

public:

    HuffmanTree(const HuffmanTree& a,const HuffmanTree &b);

    HuffmanTree(unsigned weight, char c);

    HuffmanTree();

    void populateHuffCodeTable(std::string *table);

    friend bool operator < (const HuffmanTree& a, const HuffmanTree& b);
    friend bool operator <= (const HuffmanTree& a, const HuffmanTree& b);

};


