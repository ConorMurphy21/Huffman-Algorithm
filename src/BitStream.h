




#pragma once

#include <fstream>
class BitStream {

private:
    std::string* codeTable;
    char* buffer;
    std::string carryOver;
public:

    BitStream(std::string codeTable[128]);
    ~BitStream();


    char* getNext(std::ifstream& in, bool* done);

};


