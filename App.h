#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Button.h"
#include "Static_Array_Menu.h"
#include "Linked_List_Menu.h"

using namespace std;
using namespace sf;

enum app_states { app_main = 0, app_static_array = 1, app_dynamic_array= 2 , app_linked_list= 3, app_stack= 4,app_queue= 5 };

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

private:
	//States
	short unsigned AppState;


	Button* btn_Static_Array; Button* btn_Dynamic_Array; Button* btn_Linked_List;
	Button* btn_Stack; Button* btn_Queue;

	//Menus

	Static_Array_Menu* Mn_Static_Array;
	Linked_List_Menu* Mn_Linked_List;
};

