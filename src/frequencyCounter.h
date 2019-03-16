//
// Created by mahee on 2019-03-11.
//

#include <fstream>

#pragma once

class frequencyCounter {
private:
     unsigned arr[129] = {0};

public:

    frequencyCounter(std::ifstream& in);

    unsigned getFreqOfChar(char c);


};


