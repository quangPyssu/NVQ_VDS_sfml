#pragma once

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <math.h>

#include "LinkedList.h"

using namespace std;
using namespace sf;

//event type

struct DisplayNode_Dynamic {

	RectangleShape body;

	shared_ptr<Font> font = make_shared<Font>();;

	Text text;
	Text PosText;

	//attributes

	Color BodyColor;
	Color ChosenColor = Color::Green;
	Color IdleColor = Color::Black;
	Color DeleteColor = Color::Red;

	//redraw past node
	void renderNode(RenderTarget* window);

	// copy stat;
	void NodeCovert(Square_Display_Node* node);

	void Dissolve();

	// Interpolate
	DisplayNode_Dynamic interpolate(DisplayNode_Dynamic* a, DisplayNode_Dynamic* b, float t);

	//next Point
	DisplayNode_Dynamic* NextPos = nullptr;
	void CalculateLine();
};


class Animation_Dynamic
{
public:
	Animation_Dynamic(Event* event, LinkedList* l, RenderWindow* window);

	enum FakeCodeStatus { Appear = 1, Disappear=-1,Display=0 };

	virtual ~Animation_Dynamic();

	int step = 0;
	int curStep = 0;
	vector <DisplayNode_Dynamic> DisplayRecord[30];
	DisplayNode_Dynamic AdditionalNode[30];

	int AdditionPos[30]{ 0 };

	int DisplayRecordSize[30]{ 0 };
	int DisplayRecordStringId[30]{ 0 };

	//tool
	void clearAll();
	void MakeChoosenUpTo(int u, int v);
	void MakeFillIndex(int n, Color color);
	void MakeCopyNext(int n);
	void MakeCopyPrev(int n);

	void CalculatePos(int pos);


	// uses

	void Add_pos(int v, int data);
	void Del_pos(int v);
	void Upd_pos(int v, int data);
	void Ser_pos(int v);
	void Grow_pos(int v);

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

	Vector2f FakeCodeSize = Vector2f(600, 50);
	Vector2f FakeCodePos = Vector2f(800, 150);

private:

	enum evType { E_Update =0, E_Search = 1 ,E_Grow=2, E_Nul=4};

	Event* event;
	LinkedList* l;
	RenderWindow* window;

	//Stat for render

	void cloneList();
	void cloneState();

	CircleShape arrow_head2;

	//fake codes

	int fakeId[8] = {2,6,3,0};

	string Code[3][6];

	// transition
	void Link(int cur);

};

