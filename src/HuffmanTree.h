
/*
 * Description : implementation of the Huffman tree. Based on the algorithm described by Huffman.
 *
 * made by - Maheeppartap Singh and Conor Murphy
 */

#pragma once
//Header files
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
        Node* left; //left subtree
        Node* right; //right subtree
        unsigned short val;
    public:
        Node(unsigned short val); //constructor
        void attachNodes(Node* a, Node* b);
        unsigned short getVal();
        Node* getLeft();
        Node* getRight();
    };

    Node* root;

    void codeTab(Node* root, char *s,unsigned n,std::string str[257]);

public:


    //Constructor with two tree. Function joins them.
    HuffmanTree(const HuffmanTree& a,const HuffmanTree& b);

    //Constructor with weight and character
    HuffmanTree(unsigned weight, unsigned short c);

    // Default constructor
    HuffmanTree();

    ~HuffmanTree();

    void deleteStuff(Node* root);

    // Returns the next character from the tree to be put in order
    char getChar(std::ifstream& in, bool* done);

    // Adds values to the table to maintain for order
    void populateHuffCodeTable(std::string *table);

    void print();

    //Overloading few operators for convenience
    friend bool operator < (const HuffmanTree& a, const HuffmanTree& b);
    friend bool operator <= (const HuffmanTree& a, const HuffmanTree& b);

};

//End of header file
