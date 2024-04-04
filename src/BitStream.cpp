/*
 * Description : To read bits from a file
 *
 * made by - Maheeppartap Singh and Conor Murphy.
 *
 */
#include "BitStream.h"


// constructor implementation
BitStream::BitStream(std::string *codeTable) {
    this->buffer = new char[1];
    this->codeTable = codeTable;
}

BitStream::~BitStream() {
    delete[] buffer;
}


char *BitStream::getNext(std::ifstream &in, bool *done) {
    // this is always false, except if we start writing the eof character
    // see line 38
    static bool onEof = false;

    // write code to fill buff (an 8 bit character) with as many character codes as can fit
    // if only part of a code can fit, make sure you store information (as a member variable)
    // so that you can finish writing the code
    // i.e. (imagine 22222222 was a code (even tho there are only 1 and 0)) |01012222|22220101|
    // you must be able to write this out in 2 parts, getNext returns |01012222| first and then the next
    // getNext call returns |22220101|
    // if the eof code stops somewhere in the middle of a char, pad the rest of the char with 0's

    // This snippet of code will get you the sequentially next code to encode
    // a code string, e.g. '0100' or '10' or '01101001000111'
    std::string code;
    char c; // OUT VARIABLE (int.get(c) sets c to the next char in the sequence)
    // if there is no next character, the code is the code for EOF
    if (!in.get(c)) {
        code = codeTable[256];
        // set onEof to be true so we know we are writing the end of the file
        onEof = true;
    } else {
        // otherwise grab the code associated with the next char in the stream
        code = codeTable[(unsigned char) c];
    }

    // it's your job to write buff
    *buffer = buff;
    return buffer;
}


//End of Bitsream.cpp
