
/*
 * Description : Counts the occurence of all characters in the input file
 */


//Header files
#include "frequencyCounter.h"

#include <iostream>
frequencyCounter::frequencyCounter(std::ifstream& in) {

    //if unable to open file
    if (!in.is_open()) {
        std::cout << "cannot count unopened file" << std::endl;
        return;
    }
    char c;
    while (in.read(&c, sizeof(char)))
        arr[(unsigned char) c]++; //saving all freqs

    //128 is our end of character bit, so we need an encoding for it as well
    arr[128] = 1;
}
//deconstructor
frequencyCounter::~frequencyCounter(){
    delete[] arr;
}
//returns frequency of the input character
unsigned frequencyCounter::getFreqOfChar(unsigned short c) {
    return arr[c];
}
