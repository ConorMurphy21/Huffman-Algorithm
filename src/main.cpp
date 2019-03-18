/*
 * Desc : Contains the main() of the application. Also contains the algorithms to compress and decompress
 * the required text file.
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

bool checkExtension(const string& a){
    int i;
    for(i = 0 ; ; i++){
        if( a[i] == '.') break;
    }
    return (a[i+1] == 'h' && a[i+2] == 'u' && a[i+3] == 'f' && a[i+4] == 'f');
}

int compress(const string& txtName, const string& cmpName){

    ifstream in(txtName); //opening file

    if(!in.is_open()){
        cerr << "There was an error opening the file" << endl;
        return 1;
    }

    if(!in.peek()){
        ofstream out(cmpName);
        return 0;
    }

    //make frequancy table
    frequencyCounter fq(in);
    PriorityQueue<HuffmanTree> q;

    //turn frequencies into weighted huffman trees, and put in priority queue
    char numOfChars = 0;
    for(unsigned char c = 0; c < 129; c++){
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
    string codeTable[129];
    daTree.populateHuffCodeTable(codeTable);

    //encoding:
    //encode the number of characters, all of the characters and then all of their frequencies
    ofstream out(cmpName, ios::binary);
    if(!out.is_open()){
        cerr << "something went wrong when trying to open huff file" << endl;
        return 1;
    }

    //write the number of chars
    char* buffer = &numOfChars;
    out.write(buffer,sizeof(char));

    //write all of the characters that are
    buffer = new char[numOfChars];
    unsigned* uiBuffer = new unsigned[numOfChars*4];
    int i = 0;
    for(unsigned char c = 0; c < 129; c++){
        if(codeTable[c].empty())continue;
        buffer[i] = c;
        uiBuffer[i] = fq.getFreqOfChar(c);
        i++;
    }
    out.write(buffer,sizeof(char)*numOfChars);
    out.write((char*)uiBuffer,sizeof(unsigned)*numOfChars);

    in.clear();
    in.seekg(0,ifstream::beg);
    BitStream bs(codeTable);
    bool done = false;
    while(!done){
        char* buff = bs.getNext(in,&done);
        out.write(buff,1);
    }

    out.close();
    //read file back
    return 0;

}


int decompress(const string& txtName, const string& cmpName){
    ifstream in(cmpName, ios::binary);

    if(!in)return 1;

    if(!in.peek()){
        ofstream out(txtName);  //File is empty. So close it and return 0.
        return 0;
    }

    char num;
    in.read(&num,sizeof(char));

    char* buffer = new char[num];
    in.read(buffer,sizeof(char)*num);

    unsigned* freqs = new unsigned[num];
    in.read((char*)freqs,sizeof(unsigned)*num);

    PriorityQueue<HuffmanTree> q;
    for(int i = 0; i < num; i++){
        HuffmanTree huff(freqs[i],buffer[i]);
        q.enqueue(huff);
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

    ofstream out(txtName); //Close the file

    bool done = false;
    char c = daTree.getChar(in,&done);
    while(!done){
        out << c;
        c = daTree.getChar(in,&done);
    }

    out.close();

    return 0;
}

//Main starts here
int main(int argc,char** argv){

//Checking args
    if(argc != 4){
        cerr << "Incorrect number of arguments" << endl;
    }
    //Case of compression
    if(strcmp("-c",argv[1]) == 0){
            if(checkExtension(argv[3]))
               return compress(argv[2], argv[3]);
            else {
                cerr <<"Incorrect destination";
                return -1;
            }
    }
    else if (strcmp("-d",argv[1]) == 0){   //Case of decompression
        if(checkExtension(argv[2]))
                return decompress(argv[3], argv[2]);
        else{
            cerr << "Incorrect Source";
            return -1;
        }
    }else {
        cerr << "argument 1 is not recognized" << endl;
        return -1;
    }
}
//End of main