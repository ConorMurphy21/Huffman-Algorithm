
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

    //pre: none
    //desc: recursively builds a table of huffman encodings
    void codeTab(Node* root, char *s,unsigned n,std::string str[257]);

public:


    //Desc: Constructor that joins 2 trees
    HuffmanTree(const HuffmanTree& a,const HuffmanTree& b);

    //Desc: Constructor with weight and character
    HuffmanTree(unsigned weight, unsigned short c);

    // Default constructor
    HuffmanTree();

    //Desc: returns next character from in stream
    //pre: file open at location of encoded section
    //post: remaining character is saved in static variable
    char getChar(std::ifstream& in, bool* done);

    //Desc: put huffman Encodings in a table where index represents the char it represents
    //pre: table must have at least 257 spots
    //post: understand how the table is represented
    void populateHuffCodeTable(std::string *table);

    //Overloading few operators for convenience
    friend bool operator < (const HuffmanTree& a, const HuffmanTree& b);
    friend bool operator <= (const HuffmanTree& a, const HuffmanTree& b);

};

//End of header file
