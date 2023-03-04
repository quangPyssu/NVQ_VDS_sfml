#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Button.h"

using namespace std;
using namespace sf;

class App
{
public:
	App();                     //Constructor

	virtual ~App();            // Destructor

	const bool running() const; //Accessor

	//Event & Window

	RenderWindow* window;
	VideoMode videoMode;
	Event ev;

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
	Button* btn_Static_Array; Button* btn_Dynamic_Array; Button* btn_Linked_List;
	Button* btn_Stack; Button* btn_Queue;
};

