//
// Created by mahee on 2019-03-09.
//

#include "BitStream.h"


BitStream::BitStream(std::string codeTable[129]) {
    this->buffer = new char[1];
    this->codeTable = codeTable;
}
BitStream::~BitStream() {
    delete[] buffer;
}



char* BitStream::getNext(std::ifstream& in, bool* done) {
    static bool onEof;
    unsigned char buff = 0;
    char c;
    std::string code = carryOver;
    int i = 0;
    for( ; ; ) {
        for (unsigned j = 0; j < code.length(); j++) {
            i++;
            buff <<= 1;
            if (code.at(j) == '1')buff |= 0x1;
            if (i >= 8) {
                carryOver = code.substr(j + 1);
                break;
            }
        }
        if (i >= 8)break;

        if(onEof){
            *done = true;
            buff <<= (8-i);
            break;
        }

        if (!in.get(c)) {
            code = codeTable[128];
            onEof = true;
        } else {
            code = codeTable[c];
        }
    }

    *buffer = buff;
    return buffer;
}



