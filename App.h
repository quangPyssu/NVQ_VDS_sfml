#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Tools/Button.h"
#include "Static_Array_Menu.h"
#include "Dynamic_Array_Menu.h"
#include "Linked_List_Menu.h"
#include "Doubly_Linked_List_Menu.h"
#include "Cirly_Linked_List_Menu.h"
#include "Stack_Menu.h"
#include "Queue_Menu.h"

using namespace std;
using namespace sf;

enum app_states { app_main = 0, app_static_array = 1, app_dynamic_array= 2 , app_linked_list= 3, app_stack= 4,app_queue= 5 , app_linked_list_D= 6, app_linked_list_C = 7,app_quit=8};

class App
{
public:
	App();                     //Constructor

	virtual ~App();            // Destructor

	const bool running() const; //Accessor

	//Event & Window

	RenderWindow* window;
	VideoMode videoMode;
	Event event;

	void initVariables();
	void initWindow();

	void pollEvents();

	void Render();

	// Mouse pos
	Vector2f mousePosWindowf;
	Vector2i mousePosWindowi;

	void updateMousePositions();

	//Funtion
	void update();

	//display
	Sprite sprite;
	Texture tet;
	RectangleShape shape;

	int sizeId = 3; bool theme = 0;

	Color BGColor[2] = { Color::Color(230, 208, 159), Color::Color(91, 101, 101, 255) };

private:
	//States
	short unsigned AppState;

	Button* btn_Static_Array;		Button* btn_Dynamic_Array; 

	Button* btn_Linked_List_Singly; Button* btn_Linked_List_Doubly; Button* btn_Linked_List_Cirly;

	Button* btn_Stack; Button* btn_Queue;

	Button* btn_Quit;

	//Menus

	Static_Array_Menu* Mn_Static_Array;
	Dynamic_Array_Menu* Mn_Dynamic_Array;
	Linked_List_Menu* Mn_Linked_List;
	Doubly_Linked_List_Menu* Mn_Linked_List_Doubly;
	Cirly_Linked_List_Menu* Mn_Linked_List_Cirly;
	Queue_Menu* Mn_Queue;
	Stack_Menu* Mn_Stack;
};

