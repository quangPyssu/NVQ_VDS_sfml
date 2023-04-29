#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <fstream>
#include "Tools/Button.h"
#include "Tools/ToggleButton.h"
#include "Tools/Toggle_Group.h"
#include "Tools/TextBox.h"
#include "Tools/LinkedList.h"
#include "Tools/StringProccess.h"
#include "Tools/Animation_Static.h"
#include "Tools/Slider.h"

using namespace sf;

class Static_Array_Menu
{
public:
	Static_Array_Menu(Event* event, RenderWindow* window);
	virtual ~Static_Array_Menu();

	void Render();
	void update(const Vector2f mousePos);


	// update for stuff

	void update_init();
	void update_add();
	void update_del();
	void update_upd();
	void update_search();

	//menu stat

	short unsigned stat;
	short init_stat = 0;

	//LL

	LinkedList l;
	int n = 0;
	StringProccess init_get;
	int Search_Result = -1;

	//Stat for render
	Animation_Static* anime;
	short unsigned render_Speed = slow;

	// animation

	void TimeTravel();

	void drawFrom(int step, bool hasHead);

	void drawTrans(int start, int end, short CodeStatus);

	short unsigned isDrawing = DrawNormal;

	int sizeId = 3; bool theme = 0;

	Color BGColor[2] = { Color::Color(230, 208, 159), Color::Color(91, 101, 101, 255) };

private:
	enum dras { DrawNormal = 0, DrawStep = 1, DrawAnimation_Static = 2 };
	enum Menu_stat { off = 0, on = 1, init_empty = 0, init_random = 1, init_fixed = 2, init_read = 3, init_load = 4, fast = 1, slow = 0 };

	//BTN

	ToggleButton* tog_Initialize; ToggleButton* tog_Update;
	ToggleButton* tog_Add; ToggleButton* tog_Delete;
	ToggleButton* tog_Search; Button* btn_back;

	Toggle_Group Toggle_Group_Static_Array;

	//TEXT BOX & BTN for INITIALIZE

	TextBox* box_init_read;
	TextBox* box_init_fixed;

	ToggleButton* tog_init_empty;
	ToggleButton* tog_init_random;
	ToggleButton* tog_init_fixed;
	ToggleButton* tog_init_read;
	ToggleButton* tog_init_load;

	Toggle_Group Toggle_Group_Init;

	string init_data_val = ""; int init_data_size = nothing;

	//TEXT BOX & BTN for ADD

	TextBox* box_add_val;
	TextBox* box_add_pos;
	ToggleButton* tog_add_head;
	ToggleButton* tog_add_tail;
	ToggleButton* tog_add_pos;

	Toggle_Group Toggle_Group_Add;

	int add_data_val = nothing, add_data_pos = nothing;

	//TEXT BOX & BTN for DELETE

	Button* btn_del_confirm;
	TextBox* box_del_pos;
	ToggleButton* tog_del_head;
	ToggleButton* tog_del_tail;
	ToggleButton* tog_del_pos;

	Toggle_Group Toggle_Group_Del;

	int del_data_pos = nothing;

	//TEXT BOX & BTN for UPDATE

	TextBox* box_upd_val;
	TextBox* box_upd_pos;

	int upd_data_val = nothing, upd_data_pos = nothing;

	//TEXT BOX & BTN for SEARCH

	TextBox* box_ser_val;

	int ser_data_val = nothing;

	// BTN for TIME TRAVEl

	ToggleButton* tog_speed;
	Button* btn_step_prev;
	Button* btn_step_next;
	ToggleButton* tog_play;

	Button* btn_change_size;
	ToggleButton* tog_change_color;

	//Slider

	Slider* Slide_Render_Speed;

	//Drawzie
	RenderWindow* window;
	Event* event;

	Texture tet;
	Sprite sprite;

	RectangleShape shape;

	// Mouse pos
	Vector2f mousePosWindowf;

	// stats

	//timer
	Clock clock;
	void stop(float i);

	float baseTime = 0.5;
	float StepTime = 0.5;
	float frame = 20;
	float FrameTime = StepTime / frame;
	float frameStep = 1 / frame;

	//intruc tion text;

	void loadInstruction();

	string Instruction[14];
	int curInsId = 13;

	Text text;

	Font font;
};

