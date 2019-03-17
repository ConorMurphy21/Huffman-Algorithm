

#pragma once

#include <string>
#include <fstream>

class HuffmanTree {

private:

    unsigned weight;
    unsigned height;

    class Node{
    private:
        Node* left;
        Node* right;
        unsigned char val;
    public:
        Node(unsigned char val);
        void attachNodes(Node* a, Node* b);
        unsigned char getVal();
        Node* getLeft();
        Node* getRight();
    };

    Node* root;

    void codeTab(Node* root, char *s,unsigned n,std::string str[129]);

public:

    HuffmanTree(const HuffmanTree& a,const HuffmanTree &b);

    HuffmanTree(unsigned weight, unsigned char c);

    HuffmanTree();

    char getChar(std::ifstream& in, bool* done);

    void populateHuffCodeTable(std::string *table);

    friend bool operator < (const HuffmanTree& a, const HuffmanTree& b);
    friend bool operator <= (const HuffmanTree& a, const HuffmanTree& b);

};


