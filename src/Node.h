
/*
 * Node class of the app
 *
 * Made by : Maheeppartap Singh and Conor Murphy
 */
#pragma once

template<class T>
class Node {
public:
    T data;     // The data in the node
    Node *next;   // Pointer to next node

    Node();

    Node(T theData);

    Node(T theData, Node *theNextNode);

}; // end Node
template<class T>
//Constructor of Node without data
Node<T>::Node() {
    data = 0;
    next = nullptr;
}

template<class T>
//Constructor of Node with data
Node<T>::Node(T theData) {
    data = theData;
    next = nullptr;
}

template<class T>
//Constructor of Node with data and pointer to next Node
Node<T>::Node(T theData, Node *theNextNode) {
    data = theData;
    next = theNextNode;
}
