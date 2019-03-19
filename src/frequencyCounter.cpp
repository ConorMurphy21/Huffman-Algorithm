//
// Created by mahee on 2019-03-11.
//

#include "frequencyCounter.h"

#include <iostream>
frequencyCounter::frequencyCounter(std::ifstream& in){
    if(!in.is_open()){
        std::cout << "cannot count unopened file" << std::endl;
        return;
    }
    char c;
    while(in.read(&c,sizeof(char)))
        arr[(unsigned char)c]++;

    //128 is our end of character bit, so we need an encoding for it as well
    arr[256] = 1;

}

frequencyCounter::~frequencyCounter() {
    delete[] arr;
}

unsigned frequencyCounter::getFreqOfChar(unsigned short c) {
    return arr[c];
}
