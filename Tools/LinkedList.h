#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

#define PI 3.14159265

enum pos { isHead = 0, isMiddle = 1, isTail = 2, isSingle = 0, isDouble = 1, isCircle = 3};

struct Node {
    int data = 0;

    RectangleShape line;
    CircleShape arrow_head;
    CircleShape body;
  
    shared_ptr<Font> font = make_shared<Font>();;

    Text text;
    Text PosText;

    //attributes
    
    float angle=0;
    Color BodyColor = Color::White;
    Color OutlineColor = Color::Black;
    Color ChosenColor = Color::Green;
    Color LineColor = Color::Color(91, 91, 91, 255);
    
    Color BodyColor_D = Color::Color(91, 91, 91, 255);
    Color OutlineColor_D = Color::Color(240, 240, 240, 255);
    Color ChosenColor_D = Color::Green;
    Color LineColor_D = Color::Color(211, 211, 211, 255);

    float size=40;

    short unsigned isPos = isMiddle;

    Node* Next = nullptr;
    Node* Prev = nullptr;

    //draw one node;

    void renderNode(RenderTarget* window);

    void change(int sizeId, bool theme);
};

struct LinkedList
{    
    Node* Head = nullptr;
    Node* Tail = nullptr;

    int Size=0;
    int Distance = 150;

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

    short unsigned Type = 0;

    void change(int sizeId, bool theme);
};

Node* New(int data);