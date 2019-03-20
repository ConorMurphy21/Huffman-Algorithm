/* Name - frequencyCounter.h
 * Description - counts the number of occurrences of each character.
 *
 * Made by - Conor Murphy and Maheeppartap Singh
 */
#include <fstream>

#pragma once

class frequencyCounter {
private:
     unsigned* arr;

public:

    //constructor
    explicit frequencyCounter(std::ifstream& in);

    //deConstructor
    ~frequencyCounter();


    //pre: none
    //post: none
    //desc: returns the frequency of the character
    unsigned getFreqOfChar(unsigned short c);


    //desc: prints the table
    //pre: none
    //post: none
    void print();

};

//End of header file
