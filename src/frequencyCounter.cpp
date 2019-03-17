
#include "frequencyCounter.h"

#include <iostream>
frequencyCounter::frequencyCounter(std::ifstream& in){

    //if unable to open file
    if(!in.is_open()){
        std::cout << "cannot count unopened file" << std::endl;
        return;
    }
    char c;
    while(in.get(c))
        arr[c]++;   //saving the frequency of all characters

    //128 is our end of character bit, so we need an encoding for it as well
    arr[128] = 1;

}
//Return frequncy of the input character
unsigned frequencyCounter::getFreqOfChar(unsigned char c) {
    return arr[c];

}
