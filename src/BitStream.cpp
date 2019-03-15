//
// Created by mahee on 2019-03-09.
//

#include "BitStream.h"


BitStream::BitStream(std::string codeTable[128]) {
    this->buffer = new char[1];
    this->codeTable = codeTable;
}
BitStream::~BitStream() {
    delete[] buffer;
}



char* BitStream::getNext(std::ifstream& in, bool* done) {

    //first put carrOver into the front of the buffer

    //then fill up the remains.
    unsigned char buff = 0;
    char c;
    std::string code;
    int i = 0;
    code = carryOver;
    for(unsigned j = 0; j < code.length(); j++){
        buff <<= 1;
        if(code.at(j) == '1')buff |= 0x1;
        i++;
        if(i >= 8){
            carryOver = code.substr(j+1);
            break;
        }
    }
    if(i >= 8){
        *buffer = buff;
        return buffer;
    }

    while(in.get(c)){

        code = codeTable[c];
        for(unsigned j = 0; j < code.length(); j++){
            buff <<= 1;
            if(code.at(j) == '1')buff |= 0x1;
            i++;
            if(i >= 8){
                carryOver = code.substr(j+1);
                break;
            }
        }
        if(i >= 8)break;
    }

    *done = in.eof();
    *buffer = buff;
    return buffer;
}

