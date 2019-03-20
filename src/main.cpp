/*
 * Desc : Contains the main() of the application. Also contains the algorithms to compress and decompress
 * the required file.
 *
 * made by - Conor Murphy and Maheeppartap Singh
 */

// Header files
#include <iostream>
#include <fstream>
#include "frequencyCounter.h"
#include "PriorityQueue.h"
#include "HuffmanTree.h"
#include "BitStream.h"
#include <string.h>


using namespace std;

int compress(const string& txtName, const string& cmpName){

    ifstream in(txtName,ios::binary);//opening file

    if(!in.is_open()){
        cout << "There was an error opening the file" << endl;
        return 1;
    }

    in.seekg(0, ios::end);
    ifstream::pos_type size = in.tellg();
    cout << txtName << " -> " << size << " bytes" << endl;
    if (size == 0) {
        ofstream of(txtName);
        cout << cmpName << " -> 0 bytes" << endl;
        return 0;
    }

    in.clear();
    in.seekg(0,ios::beg);

    //make frequancy table
    frequencyCounter fq(in);
    PriorityQueue<HuffmanTree> q;

    //turn frequencies into weighted huffman trees, and put in priority queue
    unsigned int numOfChars = 0;
    for(unsigned short c = 0; c < 257; c++){
        unsigned f = fq.getFreqOfChar(c);
        if(f == 0)continue;
        HuffmanTree huff(f,c);
        q.enqueue(huff);
        //count the number of chars that appear for later
        numOfChars++;
    }
    numOfChars--;

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
    string* codeTable = new string[257];
    daTree.populateHuffCodeTable(codeTable);

    //encoding:
    //encode the number of characters, all of the characters and then all of their frequencies
    ofstream out(cmpName, ios::binary);
    if(!out.is_open()){
        cout << "something went wrong when trying to open huff file" << endl;
        return 1;
    }

    char* numOfCharsPtr = (char*)&numOfChars;
    //write the number of chars
    out.write(numOfCharsPtr,sizeof(unsigned));
    //write all of the characters that are
    char* buffer = new char[numOfChars];
    unsigned* uiBuffer = new unsigned[numOfChars*4];
    int i = 0;
    //we don't write the freq of the null char because the decoder will know its 1
    for(unsigned short c = 0; c < 256; c++){
        if(codeTable[c].empty())continue;
        buffer[i] = (unsigned char)c;
        uiBuffer[i] = fq.getFreqOfChar(c);
        i++;
    }

    out.write(buffer,sizeof(unsigned char)*numOfChars);
    out.write((char*)uiBuffer,sizeof(unsigned)*numOfChars);

    delete[] buffer;
    delete[] uiBuffer;

    BitStream bs(codeTable);

    in.clear();
    in.seekg(0,ios::beg);
    bool done = false;
    while(!done){
        char* buff = bs.getNext(in,&done);
        out.write(buff,1);
    }
    delete[] codeTable;

    cout << cmpName << " -> " << out.tellp() << " bytes" << endl;
    if(size < out.tellp()) cout << "*** Size of compressed file > size of source file ***" << endl;
    out.close();
    in.close();
    //read file back
    return 0;

}


int decompress(const string& txtName, const string& cmpName){
    ifstream in(cmpName, ios::binary);

    if(!in)return 1;

    in.seekg(0, ios::end);  //read the file
    if (in.tellg() == 0) {
        ofstream of(txtName);
        return 0;
    }
    in.clear();
    in.seekg(0,ios::beg);

    unsigned n;
    in.read((char*)&n,sizeof(unsigned));
    unsigned int num = n;
    unsigned char* buffer = new unsigned char[num];
    in.read((char*)buffer,sizeof(char)*num);

    unsigned* freqs = new unsigned[num];
    in.read((char*)freqs,sizeof(unsigned)*num);

    PriorityQueue<HuffmanTree> q;   //create a new priority queue to store the characters in order
    for(int i = 0; i < num; i++){
        HuffmanTree huff(freqs[i],(unsigned short)buffer[i]);
        q.enqueue(huff);
    }
    HuffmanTree huffhuff(1,256);
    q.enqueue(huffhuff);

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

    string* codeTable = new string[257];
    daTree.populateHuffCodeTable(codeTable);    //adding everything to the table to push to the file later in order
//clearing the allocated space
    delete[] buffer;
    delete[] freqs;
    delete[] codeTable;

    ofstream out(txtName,ios::binary);

    bool done = false;
    char c = daTree.getChar(in,&done);
    while(!done){
        out.write(&c,sizeof(char));
        c = daTree.getChar(in,&done);
    }
    out.close(); //close the file and done!

    return 0;
}

//Main starts here
int main(int argc,char** argv){

//Checking args
    if(argc != 4){
        cout << "Incorrect number of arguments" << endl;
        return 1;
    }
    //Case of compression
    if(strcmp("-c",argv[1]) == 0){

        return compress(argv[2], argv[3]);
    }else if (strcmp("-d",argv[1]) == 0){
        return decompress(argv[3], argv[2]);
    }else {
        cout << "argument 1 is not recognized" << endl;
    }
}
//End of main
