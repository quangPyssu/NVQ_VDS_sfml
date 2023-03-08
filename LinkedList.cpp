#include "LinkedList.h"

Node* New(int data)
{
    Node* node = new Node;
    node->data = data;
    node->Next = node->Prev = nullptr;
    return node;
}

void LinkedList::addTail(Node* node)
{
    Size++;
    if (Tail == nullptr)
    {
        Head = node;
        Tail = node;
        return;
    }

    Tail->Next = node;
    node->Prev = Tail;
    Tail = node;
}

void LinkedList::addHead(Node* node)
{
    add(Head, node);
}

void LinkedList::addKth(Node* node,int k)
{
    int i = 0;
    Node* tmp = Head;

    while (tmp != nullptr)
    {
        if (i++ >= k)
        {
            add(tmp,node);
            return;
        }
        tmp = tmp->Next;
    }

    addTail(node);
}

void LinkedList::add(Node* cur,Node* node)
{
    Size++;
    if (cur == nullptr)
    {
        Head = node;
        Tail = node;
        return;
    }

    node->Prev = cur->Prev;
    node->Next = cur;

    if (cur->Prev!= nullptr) cur->Prev->Next = node; else Head = node;
    cur->Prev = node;
}

void LinkedList::delTail()
{
    if (Tail == nullptr) return;

    del(Tail);
}

void LinkedList::delHead()
{
    if (Head == nullptr) return;

    del(Head);
}

void LinkedList::delKth(int k)
{
    int i = 0;
    Node* tmp = Head;

    while (tmp != nullptr)
    {
        if (i++ == k)
        {
            del(tmp);
            break;
        }
        tmp = tmp->Next;
    }
}

void LinkedList::del(Node* Cur) // Delete specific node on List
{    
    Size--;
    if (Cur == nullptr) return;

    if (Cur->Prev != nullptr) Cur->Prev->Next = Cur->Next;
    if (Cur->Next != nullptr) Cur->Next->Prev = Cur->Prev;

    if (Cur == Head) Head = Head->Next; 
    if (Cur == Tail) Tail = Tail->Prev;

    delete Cur;
}

void LinkedList::delAll()
{
    while (Head)
    {
        Node* tmp = Head;
        Head = Head->Next;
        delete tmp;
    }
}