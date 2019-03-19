
/*Name - Bitsream.h
 * Description : To read bits from File.
 *
 * made by - Conor Murphy and Maheeppartap Singh
 */



#pragma once
//Header files
#include <fstream>
//End of headers


class BitStream {

private:
    std::string* codeTable;
    char* buffer;
    std::string carryOver;
public:

    explicit BitStream(std::string* codeTable);
    ~BitStream();

    //Reads the file.
    char* getNext(std::ifstream& in, bool* done);

};

//End of header file.


