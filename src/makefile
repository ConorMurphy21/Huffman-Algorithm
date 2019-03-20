all: x

x: Main.o PriorityQueue.h Node.h BitStream.o FrequencyCounter.o HuffmanTree.o
    g++ -Wall -o main Main.o BitStream.o FrequencyCounter.o HuffmanTree.o

Main.o: Main.cpp
    g++ -c -std=c++17 Main.cpp

BitStream.o: BitStream.h BitStream.cpp
    g++ -c BitStream.cpp

FrequencyCounter.o: FrequencyCounter.h FrequencyCounter.cpp
    g++ -c FrequencyCounter.cpp

HuffmanTree.o: HuffmanTree.cpp HuffmanTree.h
    g++ -c HuffmanTree.cpp

clean:
    rm -f sim *.o