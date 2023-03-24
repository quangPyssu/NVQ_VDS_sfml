#pragma once

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <math.h>

#include "LinkedList.h"

using namespace std;
using namespace sf;

struct DisplayNode {

	RectangleShape line;
    CircleShape arrow_head;
    CircleShape body;

    Font font;

    Text text;
	Text PosText;

    //attributes

    float angle = 0;
	float rad = 0;
    Color BodyColor;
    Color ChosenColor = Color::Green;
    Color IdleColor = Color::Black;
	Color DeleteColor = Color::Red;

	//redraw past node
	void renderNode(RenderTarget* window);

	// copy stat;
	void NodeCovert(Node* node);

	Vector2f NextPos=Vector2f(0,0);
};


class Animation
{
public:
	Animation(Event* event,LinkedList* l,RenderWindow* window);
	virtual ~Animation();
	
	int step = 0;
	vector <DisplayNode> DisplayRecord[30];
	vector <DisplayNode> AdditionalNode[30];
	int DisplayRecordSize[30]{0};

	//tool
	void clearAll();
	void MakeChoosenUpTo(int u,int v);
	void MakeFillIndex(int n, Color color);

	void CalculatePos(int pos);
	void CalculateLine(DisplayNode* cur, Vector2f NextPos);

	// uses

	void Del_pos(int v);
	void Add_pos(int v,int data);

	// render

	Texture tet;
	Sprite sprite;

	void render();
	void drawOneStep(int i);

private:
	Event* event;
	LinkedList* l;
	RenderWindow* window;

	//Stat for render

	void cloneList();
	void cloneState();

	//fake codes

	string s_Add_Head[3];
	string s_Add_Tail[3];
	string s_Add_Middle[7];


};

