#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace sf;

enum Menu_stat { off = 0, on = 1 };

class Static_Array_Menu
{
public:
	Static_Array_Menu();
	virtual ~Static_Array_Menu();

	void Render(RenderTarget* target);
	void update(const Vector2f mousePos);

	short unsigned stat;

private:
	//BTN

	Button* btn_Initialize;	Button* btn_Add;
	Button* btn_Delete; Button* btn_Update;
	Button* btn_Search; Button* btn_back;

	//Drawzie
	RenderTarget* target;

	Texture tet;
	Sprite sprite;

	// Mouse pos
	Vector2f mousePosWindowf;
};

