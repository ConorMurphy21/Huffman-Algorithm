//
// Created by mahee on 2019-03-11.
//


#pragma once

#include <string>
#include <fstream>

#define TNODEVAL 512
#define EOFVAL 256

class HuffmanTree {

private:

    unsigned weight;
    unsigned height;

    class Node{
    private:
        Node* left;
        Node* right;
        unsigned short val;
    public:
        Node(unsigned short val);
        Node(Node* node);
        void attachNodes(Node* a, Node* b);
        unsigned short getVal();
        Node* getLeft();
        Node* getRight();
    };

    Node* root;

    void codeTab(Node* root, char *s,unsigned n,std::string str[257]);

public:

    HuffmanTree(const HuffmanTree& a,const HuffmanTree& b);

    HuffmanTree(unsigned weight, unsigned short c);

    HuffmanTree();

    ~HuffmanTree();

    void deleteStuff(Node* root);

    char getChar(std::ifstream& in, bool* done);

    void populateHuffCodeTable(std::string *table);

    friend bool operator < (const HuffmanTree& a, const HuffmanTree& b);
    friend bool operator <= (const HuffmanTree& a, const HuffmanTree& b);

};


