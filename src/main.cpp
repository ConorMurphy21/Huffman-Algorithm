//
// Created by mahee on 2019-03-11.
//

#include <iostream>
#include <fstream>
#include "frequencyCounter.h"
#include "PriorityQueue.h"
#include "HuffmanTree.h"
#include "BitStream.h"


using namespace std;

int encode(){

    ifstream in("../../res/Muppets.txt");

    if(!in.is_open()){
        cout << "There was an error opening the file" << endl;
        return 0;
    }

    //make frequancy table
    frequencyCounter fq(in);
    PriorityQueue<HuffmanTree> q;

    //turn frequencies into weighted huffman trees, and put in priority queue
    char numOfChars = 0;
    for(unsigned char c = 0; c < 128; c++){
        unsigned f = fq.getFreqOfChar(c);
        if(f == 0)continue;
        HuffmanTree huff = HuffmanTree(f,c);
        q.enqueue(huff);
        //count the number of chars that appear for later
        numOfChars++;
    }

    //add trees together, and place back into queue until the queue is empty
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

    //get codeTable from the huffman tree
    string codeTable[128];
    daTree.populateHuffCodeTable(codeTable);

    for(unsigned char c = 0; c < 128; c++){
        if(!codeTable[c].empty()){
            cout << c << ": " << codeTable[c] << endl;
        }
    }

    in.clear();
    in.seekg(0,ifstream::beg);

    BitStream bs(codeTable);
    bool done = false;
    printf("encoding:\n");
    while(!done){
        char* buff = bs.getNext(in,&done);
        printf("%x ", 0xff & *buff);
    }
    printf("\ndone\n");

    //encoding:
    //encode the number of characters, all of the characters and then all of their frequencies
    ofstream out("../../res/Muppets.huff", ios::binary);
    if(!out.is_open()){
        cout << "something went wrong when trying to open huff file" << endl;
        return 1;
    }

    //write the number of chars
    char* buffer = &numOfChars;
    out.write(buffer,sizeof(char));

    //write all of the characters that are
    buffer = new char[numOfChars];
    int i = 0;
    for(unsigned char c = 0; c < 128; c++){
        if(codeTable[c].empty())continue;
        buffer[i] = c;
        i++;
    }
    out.write(buffer,sizeof(char)*numOfChars);

    unsigned* uiBuffer = new unsigned[numOfChars*4];
    i=0;
    for(unsigned char c = 0; c < 128; c++){
        if(codeTable[c].empty())continue;
        uiBuffer[i] = fq.getFreqOfChar(c);
        i++;
    }
    out.write((char*)uiBuffer,sizeof(unsigned)*numOfChars);

    in.clear();
    in.seekg(0,ifstream::beg);

    out.close();
    //read file back
    return 0;

}


int decode(){
    ifstream in("../../res/Muppets.huff", ios::binary);
    char num;
    in.read(&num,sizeof(char));

    char* buffer = new char[num];
    in.read(buffer,sizeof(char)*num);

    unsigned* freqs = new unsigned[num];
    in.read((char*)freqs,sizeof(unsigned)*num);

    for(int i = 0; i < num; i++){
        cout << buffer[i] << " : " << freqs[i] << endl;
    }
    return 0;
}

int main(){
    encode();
    decode();
}