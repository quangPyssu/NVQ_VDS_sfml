#pragma once
struct Node {
    int data = 0;
    Node* Next = nullptr;
    Node* Prev = nullptr;
};

struct LinkedList
{
    Node* Head = nullptr;
    Node* Tail = nullptr;

    void addTail(Node* node);

    void addHead(Node* node);

    void del(Node* Cur);

    void delTail();

    void delHead();

    void delKth(int k);

    void delAll();
};

Node* New(int data);