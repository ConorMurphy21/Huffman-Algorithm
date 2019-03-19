//
// Created by mahee on 2019-03-11.
//

#include <fstream>

#pragma once

class frequencyCounter {
private:
     unsigned* arr = new unsigned[257]{0};

public:

    explicit frequencyCounter(std::ifstream& in);

    ~frequencyCounter();

    unsigned getFreqOfChar(unsigned short c);


};


