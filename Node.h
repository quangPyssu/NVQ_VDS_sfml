#pragma once
class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int data = 0, Node* next = nullptr, Node* prev = nullptr) {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }

    void pushHead(Node*& Head, int k);
    void delHead(Node*& Head);
    void delAll(Node*& Head);
};