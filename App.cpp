#include "App.h"
#include <iostream>

// Constructor

App::App()
{
	initVariables();
	initWindow();

	AppState = app_main;

	window->clear(Color::Black);
	tet.loadFromFile("asset/texture/condauvoi.jpg");
	sprite.setTexture(tet);
	sprite.setScale(Vector2f(1000.f / tet.getSize().x, 800.f / tet.getSize().y));

	//btn for main

	this->btn_Static_Array = new Button(100, 100, 150, 50, "Static Array", Color::Black, Color::White, Color::Color(90,90,90,180), Color::Color(90, 90, 90, 255), Color::Black);

	this->btn_Dynamic_Array = new Button(100, 200, 150, 50, "Dynamic Array", Color::Black, Color::White, Color::Color(90,90,90,180), Color::Color(90, 90, 90, 255), Color::Black);

	this->btn_Linked_List = new Button(100, 300, 150, 50, "Linked List", Color::Black, Color::White, Color::Color(90,90,90,180), Color::Color(90, 90, 90, 255), Color::Black);

	this->btn_Stack = new Button(100, 400, 150, 50, "Stack", Color::Black, Color::White, Color::Color(90,90,90,180), Color::Color(90, 90, 90, 255), Color::Black);

	this->btn_Queue = new Button(100, 500, 150, 50, "Queue", Color::Black, Color::White, Color::Color(90,90,90,180), Color::Color(90, 90, 90, 255), Color::Black);

	// Menus

	Mn_Static_Array = new Static_Array_Menu(&event);

	window->setFramerateLimit(30);
	Render();
	window->display();
}

//Destructor

App::~App()
{
	delete window;
	delete this->btn_Static_Array; delete this->btn_Dynamic_Array; delete this->btn_Linked_List;
	delete this->btn_Stack; delete this->btn_Queue;
}

//Accesscor

const bool App::running() const
{
	return window->isOpen();
}

//mouse POSITION

void App::updateMousePositions()
{
	//  update  mousePosWindow(Vector2f and Vector2i)
	mousePosWindowf = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
	mousePosWindowi = Mouse::getPosition(*this->window);
}

// setup window

void App::initVariables()
{
	window = NULL;
}

void App::initWindow()
{
	videoMode.height = 800;
	videoMode.width = 1000;

	window = new RenderWindow(videoMode, "data Visual", Style::Titlebar | Style::Close);;
}

// Update & Draw

void App::update()
{
	updateMousePositions();

	switch (AppState)
	{
		case app_main:
			this->btn_Static_Array->update(mousePosWindowf, &event);
			this->btn_Dynamic_Array->update(mousePosWindowf, &event);
			this->btn_Linked_List->update(mousePosWindowf, &event);
			this->btn_Stack->update(mousePosWindowf, &event);
			this->btn_Queue->update(mousePosWindowf, &event);

			if (this->btn_Static_Array->isPressed()) AppState = app_static_array, Mn_Static_Array->stat = on; else
			if (this->btn_Dynamic_Array->isPressed()) AppState = app_dynamic_array; else
				if (this->btn_Linked_List->isPressed()) AppState = app_linked_list; else
					if (this->btn_Queue->isPressed()) AppState = app_queue; else
						if (this->btn_Stack->isPressed()) AppState = app_stack;
			break;

		case app_static_array:
			Mn_Static_Array->update(mousePosWindowf);
			if (!Mn_Static_Array->stat) AppState = app_main;
			break;

		case app_dynamic_array:

			break;

		case app_linked_list:

			break;

		case app_queue:

			break;

		case app_stack:

			break;

		default:
		break;
	}
	
}

void App::Render()
{
	window->clear(Color::Black);

	window->draw(sprite);

	this->btn_Static_Array->render(window);
	this->btn_Dynamic_Array->render(window);
	this->btn_Linked_List->render(window);
	this->btn_Stack->render(window);
	this->btn_Queue->render(window);
}


//Main Loop

void App::pollEvents()
{
	while (running()) {

		while (window->pollEvent(event)) {

			update();
			//cout << mousePosWindowi.x << " " << mousePosWindowi.y << endl;

			if (event.type == Event::Closed) {
				window->close();
			}

		switch (AppState)
		{
			case app_main:
				Render();
				break;

			case app_static_array:
				Mn_Static_Array->Render(window);
				break;

			case app_dynamic_array:

				break;

			case app_linked_list:

				break;

			case app_queue:

				break;

			case app_stack:

				break;
		}window->display();
		}

	}
}
