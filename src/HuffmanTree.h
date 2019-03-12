//
// Created by mahee on 2019-03-11.
//


#pragma once

class HuffmanTree {

private:

    int weight;

    class Node{
    private:
        Node* left;
        Node* right;
        Node* parent;
        char val;
    public:
        Node(char val);
        void attachNodes(Node* a, Node* b);
    };

    Node* root;

public:

    HuffmanTree(const HuffmanTree& a,const HuffmanTree &b);

    HuffmanTree(int weight, char c);

    friend bool operator < (const HuffmanTree& a, const HuffmanTree& b);

};


