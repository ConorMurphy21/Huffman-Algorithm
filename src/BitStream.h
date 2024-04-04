
/*Name - Bitsream.h
 * Description : reads chars, converts them using a given codeTable, and then returns bytes of encoding
 *
 * made by - Conor Murphy and Maheeppartap Singh
 */



#pragma once
//Header files
#include <fstream>
//End of headers


class BitStream {

private:
    std::string *codeTable;
    char *buffer;
public:

    //Constructor
    explicit BitStream(std::string *codeTable);

    //DeConstructor
    ~BitStream();


    //desc: returns the next char of encoding
    //pre: the file should be open
    //post: carryOver will contain any bits that did not fit for next call
    char *getNext(std::ifstream &in, bool *done);

};

//End of header file.


