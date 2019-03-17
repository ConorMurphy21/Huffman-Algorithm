/* Name - frequencyCounter.h
 * Description - counts the number of occurrences of each character.
 *
 * Made by - Conor Murphy and Maheeppartap Singh
 */
#include <fstream>

#pragma once

class frequencyCounter {
private:
     unsigned arr[129] = {0}; // array of 129 characters.

public:
    //constructor
    frequencyCounter(std::ifstream& in);

    // counts frequency of all characters in file
    unsigned getFreqOfChar(unsigned char c);


};

//End of header file
