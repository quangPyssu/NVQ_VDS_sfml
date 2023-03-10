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
	void update_del();
	void update_upd();

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
	ToggleButton* tog_add_pos;

	Toggle_Group Toggle_Group_Add;

	int add_data_val=nothing,add_data_pos=nothing;

	//TEXT BOX & BTN for DELETE

	TextBox* box_del_pos;
	ToggleButton* tog_del_head;
	ToggleButton* tog_del_tail;
	ToggleButton* tog_del_pos;

	Toggle_Group Toggle_Group_Del;
	
	int  del_data_pos = nothing;

	//TEXT BOX & BTN for UPDATE

	TextBox* box_upd_val;
	TextBox* box_upd_pos;
	ToggleButton* tog_upd_head;
	ToggleButton* tog_upd_tail;
	ToggleButton* tog_upd_pos;

	Toggle_Group Toggle_Group_Upd;

	int upd_data_val = nothing, upd_data_pos = nothing;

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

