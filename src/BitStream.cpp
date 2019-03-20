/*
 * Description : To read bits from a file
 *
 * made by - Maheeppartap Singh and Conor Murphy.
 *
 */
#include "BitStream.h"


// constructor implementation
BitStream::BitStream(std::string* codeTable) {
    this->buffer = new char[1];
    this->codeTable = codeTable;
}
BitStream::~BitStream() {
    delete[] buffer;
}


//desc: returns the next char of encoding
//pre: the file should be open
//post: carryOver will contain any bits that did not fit for next call
char* BitStream::getNext(std::ifstream& in, bool* done) {
    static bool onEof;
    unsigned char buff = 0; // buff al 0s.
    char c;
    std::string code = carryOver;
    int i = 0;
    for( ; ; ) {
        for (unsigned j = 0; j < code.length(); j++) {
            i++;
            buff <<= 1; // right shift buff.
            if (code.at(j) == '1')buff |= 0x1;  // checks if the string code has '1' at jth position and makes buff = 1 if it does
            if (i >= 8) {   //when i is at least 8, change carryover to the changed code from above
                carryOver = code.substr(j + 1);
                break; //move out of the nested loop
            }
        }
        if (i >= 8)break; // move out of the final loop.

        if(onEof){  //if file ends
            *done = true;
            buff <<= (8-i); // if the last 8 bits not complete, we shift it.
            break;
        }

        if (!in.get(c)) {
            code = codeTable[256];
            onEof = true;
        } else {
            code = codeTable[(unsigned char)c];
        }
    }

    *buffer = buff;
    return buffer;
}


//End of Bitsream.cpp
