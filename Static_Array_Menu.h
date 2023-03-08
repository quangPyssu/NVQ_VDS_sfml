#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ToggleButton.h"
#include "Toggle_Group.h"
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

	// update for stuff

	void update_add();

	//menu stat

	short unsigned stat;

	//LL

	LinkedList l;

private:
	//BTN

	ToggleButton* tog_Initialize;ToggleButton* tog_Add;
	ToggleButton* tog_Delete; ToggleButton* tog_Update;
	ToggleButton* tog_Search; Button* btn_back;

	Toggle_Group Toggle_Group_Static_Array;

	//TEXT BOX & BTN for ADD

	TextBox* box_add_val;
	TextBox* box_add_pos;
	ToggleButton* tog_add_head;
	ToggleButton* tog_add_tail;

	int add_data_val=0,add_data_pos=0;

	//Drawzie
	RenderTarget* target;
	Event* event;

	Texture tet;
	Sprite sprite;

	// Mouse pos
	Vector2f mousePosWindowf;

	// stats
	bool init_stat = 0;
	bool add_stat = 0;
	bool del_stat = 0;
	bool upd_stat = 0;
	bool ser_stat = 0;
};

