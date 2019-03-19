




#pragma once

#include <fstream>
class BitStream {

private:
    std::string* codeTable;
    char* buffer = new char[1];
    std::string carryOver;
public:

    explicit BitStream(std::string* codeTable);
    ~BitStream();


    char* getNext(std::ifstream& in, bool* done);

};


