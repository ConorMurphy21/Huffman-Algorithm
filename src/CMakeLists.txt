cmake_minimum_required(VERSION 3.12)
project(Huffman-Project_CMPT225)

set(CMAKE_C_STANDARD 99)
add_executable(Huffman-Project_CMPT225 main.cpp BitStream.cpp PriorityQueue.h HuffmanTree.cpp map.cpp frequencyCounter.cpp)
