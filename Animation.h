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
    Color BodyColor;
    Color ChosenColor=Color::Green;
    Color IdleColor=Color::Black;

	//redraw past node
	void renderNode(RenderTarget* window);

	// copy stat;
	void clone(Node* node);
};


class Animation
{
public:
	Animation(Event* event,LinkedList* l,RenderWindow* window);
	virtual ~Animation();
	
	void display_Del_Head();

	int step = 0;
	vector <DisplayNode> DisplayRecord[15];

	void clearAll();
	void MakeChoosenUpTo(int u,int v);

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

	//fake codes

	string s_Add_Head[3];
	string s_Add_Tail[3];
	string s_Add_Middle[7];

};

