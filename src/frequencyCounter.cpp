
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
    while (in.get(c))
        arr[(unsigned char) c]++; //saving all freqs

    //128 is our end of character bit, so we need an encoding for it as well
    arr[256] = 1;
}
//deconstructor
frequencyCounter::~frequencyCounter(){
    delete[] arr;
}
//returns frequency of the input character
unsigned frequencyCounter::getFreqOfChar(unsigned short c) {
    return arr[c];
}

void frequencyCounter::print(){
    for(int i = 0; i < 257; i++){
        if(arr[i] == 0)continue;
        std::cout << i << ": " << arr[i] << std::endl;
    }
}
