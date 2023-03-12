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
    int Size=0;

    void add(Node* cur,Node* node);

    void addTail(Node* node);

    void addHead(Node* node);

    void addKth(Node* node, int k);

    void del(Node* Cur);

    void delTail();

    void delHead();

    void delKth(int k);

    void delAll();

    void UpdateKth(int k,int data);

    short find(int data);
};

Node* New(int data);