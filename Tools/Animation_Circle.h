#pragma once

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <math.h>

#include "LinkedList.h"

using namespace std;
using namespace sf;

//event type

struct DisplayNode_Circle {

	RectangleShape line;
	CircleShape arrow_head;
	CircleShape body;

	shared_ptr<Font> font = make_shared<Font>();;

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
	void NodeCovert(Round_Display_Node* node);

	void Dissolve();

	// Interpolate
	DisplayNode_Circle interpolate(DisplayNode_Circle* a, DisplayNode_Circle* b, float t);

	//next Point
	DisplayNode_Circle* NextPos = nullptr;
	void CalculateLine(DisplayNode_Circle* next);
};


class Animation_Circle
{
public:
	Animation_Circle(Event* event, LinkedList* l, RenderWindow* window);

	enum FakeCodeStatus { Appear = 1, Disappear=-1,Display=0 };

	virtual ~Animation_Circle();

	int step = 0;
	int curStep = 0;
	vector <DisplayNode_Circle> DisplayRecord[30];
	DisplayNode_Circle AdditionalNode[30];

	short HeadPos[30]{ 0 };
	short TailPos[30];

	int AdditionPos[30]{ 0 };

	RectangleShape line1, line2, line3, line4;

	CircleShape arrow;

	int tailPos[30],headPos[30];
	int DisplayRecordSize[30]{ 0 };
	int DisplayRecordStringId[30]{ 0 };

	//tool
	void clearAll();
	void MakeChoosenUpTo(int u, int v);
	void MakeFillIndex(int n, Color color);

	void CalculatePos(int pos);


	// uses

	void Del_pos(int v);
	void Add_pos(int v, int data);
	void Upd_pos(int v, int data);
	void Ser_pos(int v);

	// render

	Texture tet;
	Sprite sprite;

	void render();
	void drawOneStep(int i);

	void drawFakeCode(int cur,float posX);

	void drawSmoothTransition(int start, int end, float progress,short CodeStatus);


	//fake Code
	int eventType = 0;

	RectangleShape CodeBox;
	Text FakeCode;
	Font Fonte;

	Color CodeBoxColor = Color(252, 142, 172);

	Vector2f FakeCodeSize = Vector2f(650, 40);
	Vector2f FakeCodePos;

private:

	enum evType { E_DelHead = 0, E_DelMiddle = 1, E_AddHead = 2, E_AddMiddle = 3, E_Update = 4, E_Search = 5 };

	Event* event;
	LinkedList* l;
	RenderWindow* window;

	//Stat for render

	void cloneList();
	void cloneState();

	CircleShape arrow_head2;

	//fake codes

	int fakeId[6] = {10,10,10,10,5,6};

	string Code[6][11];

	// transition
	void Link(int cur);

};

