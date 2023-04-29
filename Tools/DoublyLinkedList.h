#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

#define PI 3.14159265

enum pos { isHead = 0, isMiddle = 1, isTail = 2};
enum LLtype { isRound = 0, isSquare = 1, isTwo=2, isCircle=3 };

struct Node {
    int data = 0;

    Node* Next = nullptr;
    Node* Prev = nullptr;
};

struct Display_Node_Doubly
{
    void NewDoubly(int data);
    int data;

    RectangleShape line;
    CircleShape arrow_head;

    RectangleShape back;
    CircleShape arrow_back;

    CircleShape body;

    shared_ptr<Font> font = make_shared<Font>();;

    Text text;
    Text PosText;

    //attributes

    float angle = 0;
    Color BodyColor = Color::White;
    Color OutlineColor = Color::Black;
    Color ChosenColor = Color::Green;
    Color LineColor = Color::Color(91, 91, 91, 255);

    Color BodyColor_D = Color::Color(91, 91, 91, 255);
    Color OutlineColor_D = Color::Color(240, 240, 240, 255);
    Color ChosenColor_D = Color::Green;
    Color LineColor_D = Color::Color(211, 211, 211, 255);

    float size = 40;

    Vector2f nextPos;
    Vector2f prevPos;

    short unsigned isPos = isMiddle;

    //draw one node;

    void renderNode(RenderTarget* window);

    void change(int sizeId, bool theme);
};

struct DoublyLinkedList
{    
    Node* Head = nullptr;
    Node* Tail = nullptr;

    int Size=0;
    int Distance = 150;

    short type = isRound;//display type

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

    vector <Display_Node_Doubly> Two_Node;

    void AddDisplay(int i, int data);
    void DelDisplay(int i);
    
    void render(RenderWindow* window);

    void change(int sizeId, bool theme);
};

Node* NewDoubly(int data);