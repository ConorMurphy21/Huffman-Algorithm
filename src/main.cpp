//
// Created by mahee on 2019-03-11.
//

#include <iostream>
#include <fstream>
#include "frequencyCounter.h"
#include "PriorityQueue.h"
#include "HuffmanTree.h"

using namespace std;

int main(){

    ifstream in;


    in.open("../../res/Muppets.txt");
    if(!in.is_open()){
        cout << "There was an error opening the file" << endl;
        return 0;
    }

    frequencyCounter fq(in);

    PriorityQueue<HuffmanTree> q;

    for(unsigned char c = 0; c < 128; c++){
        unsigned f = fq.getFreqOfChar(c);
        if(f == 0)continue;
        HuffmanTree huff = HuffmanTree(f,c);
        q.enqueue(huff);
    }

    HuffmanTree daTree = q.peek();
    q.dequeue();
    while(!q.isEmpty()){
        HuffmanTree huff2 = q.peek();
        q.dequeue();
        HuffmanTree huff3(daTree,huff2);
        q.enqueue(huff3);
        daTree = q.peek();
        q.dequeue();
    }

    string codeTable[256];
    daTree.populateHuffCodeTable(codeTable);

    for(unsigned char c = 0; c < 128; c++){
        if(codeTable[c].empty())continue;
        cout << c << " : " << codeTable[c] << endl;
    }

}