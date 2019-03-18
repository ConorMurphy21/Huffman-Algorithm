
/*
 * Description : implementation of the Huffman tree
 */

#pragma once
//Header files
#include <string>
#include <fstream>


class HuffmanTree {

private:

    unsigned weight;
    unsigned height;

    class Node{
    private:
        Node* left; //left subtree
        Node* right;    //right subtree
        unsigned char val;
    public:
        Node(unsigned char val);    //constructor
        void attachNodes(Node* a, Node* b);
        unsigned char getVal();
        Node* getLeft();
        Node* getRight();
    };

    Node* root;

    void codeTab(Node* root, char *s,unsigned n,std::string str[129]);

public:

    //Constructor with two tree. Function joins them.
    HuffmanTree(const HuffmanTree& a,const HuffmanTree &b);

    //Constructor with weight and character
    HuffmanTree(unsigned weight, unsigned char c);

    // Default constructor
    HuffmanTree();

    // Returns the next character from the tree to be put in order
    char getChar(std::ifstream& in, bool* done);

    // Adds values to the table to maintain for order
    void populateHuffCodeTable(std::string *table);


    //Overloading few operators for convenience
    friend bool operator < (const HuffmanTree& a, const HuffmanTree& b);
    friend bool operator <= (const HuffmanTree& a, const HuffmanTree& b);

};

//End of header file
