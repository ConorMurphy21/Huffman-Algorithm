
/*
 * Description : Counts the occurence of all characters in the input file.
 *
 * made by - Conor Murphy and Maheeppartap Singh
 */


//Header files
#include "frequencyCounter.h"
#include <iostream>

//desc: counts and returns the frequency of all the chars in the file
//pre: a valid file which exists in the directory
//post: file will be read
frequencyCounter::frequencyCounter(std::ifstream &in) {

    arr = new unsigned[257]{0};

    //if unable to open file
    if (!in.is_open()) {
        std::cout << "cannot count unopened file" << std::endl;
        return;
    }
    char c;
    while (in.get(c)) {
        arr[(unsigned char) c]++; //saving all freqs
    }
    //128 is our end of character bit, so we need an encoding for it as well
    arr[256] = 1;

}

//deconstructor
frequencyCounter::~frequencyCounter() {
    delete[] arr;
}

//pre: none
//post: none
//desc: returns the frequency of the character
unsigned frequencyCounter::getFreqOfChar(unsigned short c) {
    return arr[c];
}

//desc: prints the table
//pre: none
//post: none
void frequencyCounter::print() {
    for (int i = 0; i < 257; i++) {
        if (arr[i] == 0)continue;
        std::cout << i << ": " << arr[i] << std::endl;
    }
}

//end of file