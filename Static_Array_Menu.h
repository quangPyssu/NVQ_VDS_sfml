#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "LinkedList.h"

using namespace sf;

enum Menu_stat { off = 0, on = 1 };

class Static_Array_Menu
{
public:
	Static_Array_Menu(Event* event);
	virtual ~Static_Array_Menu();

	void Render(RenderTarget* target);
	void update(const Vector2f mousePos);

	short unsigned stat;

	LinkedList l;

private:
	//BTN

	Button* btn_Initialize;	Button* btn_Add;
	Button* btn_Delete; Button* btn_Update;
	Button* btn_Search; Button* btn_back;

	//TEXT BOX

	TextBox* box_read;

	//Drawzie
	RenderTarget* target;
	Event* event;

	Texture tet;
	Sprite sprite;

	// Mouse pos
	Vector2f mousePosWindowf;
};

