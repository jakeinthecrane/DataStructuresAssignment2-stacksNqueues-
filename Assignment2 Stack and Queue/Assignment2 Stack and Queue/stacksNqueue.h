#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <limits>

using namespace std;

class Node 
{
public:
    string message;
    shared_ptr<Node> next;
    shared_ptr<Node> prev;

    Node(const string& msg) : message(msg), next(nullptr), prev(nullptr) 
    {}
};

class Browser 
{
private:
    shared_ptr<Node> head;
    shared_ptr<Node> tail;

public:
    Browser();
    ~Browser();

    void pushMessage(const string& message);   // Stack behavior (LIFO)
    string popMessage();                       // Stack behavior (LIFO)
    void enqueueMessage(const string& message); // Queue behavior (FIFO)
    string dequeueMessage();                   // Queue behavior (FIFO)
    void clearList();                          // Clear the linked list
    void displayList(const vector<string>& messages) const; // Display predefined list
    void playMessages(bool useStack);          // Play messages using stack or queue
    void menu();                               // Menu for user interaction
};
