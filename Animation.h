#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "LinkedList.h"

using namespace std;
using namespace sf;


class Animation
{
public:
	Animation(Event* event,LinkedList* l,RenderWindow* window);
	virtual ~Animation();
	
	void display_Del_Head();

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

