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
}

unsigned frequencyCounter::getFreqOfChar(char c) {
    return arr[c];
}
