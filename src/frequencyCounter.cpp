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
    while(in.get(c))
        arr[c]++;

    //128 is our end of character bit, so we need an encoding for it as well
    arr[128] = 1;
}

unsigned frequencyCounter::getFreqOfChar(char c) {
    return arr[c];
}
