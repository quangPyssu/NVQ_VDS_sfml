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

	shared_ptr<Font> font= make_shared<Font>();;

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

	void Dissolve();

	// Interpolate
	DisplayNode interpolate(DisplayNode* a, DisplayNode* b, float t);

	//next Point
	DisplayNode* NextPos=nullptr;
	void CalculateLine(DisplayNode* next);
};


class Animation
{
public:
	Animation(Event* event,LinkedList* l,RenderWindow* window);
	virtual ~Animation();
	
	int step = 0;
	int curStep = 0;
	vector <DisplayNode> DisplayRecord[30];
	DisplayNode AdditionalNode[30];
	int AdditionPos[30]{0};
	int DisplayRecordSize[30]{0};

	//tool
	void clearAll();
	void MakeChoosenUpTo(int u,int v);
	void MakeFillIndex(int n, Color color);

	void CalculatePos(int pos);
	

	// uses

	void Del_pos(int v);
	void Add_pos(int v,int data);
	void Upd_pos(int v, int data);
	void Ser_pos(int v);

	// render

	Texture tet;
	Sprite sprite;

	void render();
	void drawOneStep(int i);

	void drawSmoothTransition(int start, int end, float progress);

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

	string s_Del_Middle[7];
	string s_Del_Tail[7];

	string s_Upd[4];

	string s_Search[6];

	// transition
	void Link(int cur);
	
};

