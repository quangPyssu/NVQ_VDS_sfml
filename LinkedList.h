#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

#define PI 3.14159265

enum pos { isHead = 0, isMiddle = 1, isTail = 2 };

struct Node {
    int data = 0;

    RectangleShape line;
    CircleShape arrow_head;
    CircleShape body;
    
    Font font;

    Text text;

    //attributes
    
    float angle=0;
    Color BodyColor;
    Color ChosenColor;
    Color IdleColor;

    short unsigned isPos = isMiddle;

    Node* Next = nullptr;
    Node* Prev = nullptr;

    //draw one node;

    void renderNode(RenderTarget* window);
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

    //display
    
    void render(RenderWindow* window);

    void choose(int n);
};

Node* New(int data);