#include "App.h"

// Constructor

App::App()
{
	initVariables();
	initWindow();

	AppState = app_main;

	window->clear(Color::Black);
	tet.loadFromFile("asset/texture/cream.jpg");
	sprite.setTexture(tet);
	sprite.setScale(Vector2f(1920.f / tet.getSize().x, 1080.f / tet.getSize().y));

	//btn for main

	this->btn_Static_Array = new Button(100, 100, 170, 50, "Static Array", Color::Black, Color::White, Color::Color(90,90,90,180), Color::Color(90, 90, 90, 255), Color::Black);

	this->btn_Dynamic_Array = new Button(100, 200, 170, 50, "Dynamic Array", Color::Black, Color::White, Color::Color(90,90,90,180), Color::Color(90, 90, 90, 255), Color::Black);

	this->btn_Linked_List_Singly = new Button(100, 300, 170, 50, "Linked List Singly", Color::Black, Color::White, Color::Color(90,90,90,180), Color::Color(90, 90, 90, 255), Color::Black);

	this->btn_Linked_List_Doubly = new Button(100, 400, 170, 50, "Linked List Doubly", Color::Black, Color::White, Color::Color(90, 90, 90, 180), Color::Color(90, 90, 90, 255), Color::Black);

	this->btn_Linked_List_Cirly = new Button(100, 500, 170, 50, "Linked List Cirly", Color::Black, Color::White, Color::Color(90, 90, 90, 180), Color::Color(90, 90, 90, 255), Color::Black);

	this->btn_Stack = new Button(100, 600, 170, 50, "Stack", Color::Black, Color::White, Color::Color(90,90,90,180), Color::Color(90, 90, 90, 255), Color::Black);

	this->btn_Queue = new Button(100, 700, 170, 50, "Queue", Color::Black, Color::White, Color::Color(90,90,90,180), Color::Color(90, 90, 90, 255), Color::Black);

	this->btn_Quit = new Button(100, 800, 170, 50, "Quit", Color::Black, Color::White, Color::Color(90, 90, 90, 180), Color::Color(90, 90, 90, 255), Color::Black);

	// Menus

	Mn_Static_Array = new Static_Array_Menu(&event,window);
	Mn_Dynamic_Array = new Dynamic_Array_Menu(&event, window);
	Mn_Linked_List = new Linked_List_Menu(&event, window);
	Mn_Linked_List_Doubly = new Doubly_Linked_List_Menu(&event, window);
	Mn_Linked_List_Cirly = new Cirly_Linked_List_Menu(&event, window);
	Mn_Stack = new Stack_Menu(&event, window);
	Mn_Queue = new Queue_Menu(&event, window);

	window->setFramerateLimit(30);
	Render();
	window->display();
}

//Destructor

App::~App()
{
	delete window;

	delete this->btn_Static_Array; delete this->btn_Dynamic_Array; 

	delete this->btn_Linked_List_Singly; delete this->btn_Linked_List_Doubly; delete this->btn_Linked_List_Cirly;

	delete this->btn_Stack; delete this->btn_Queue;

	delete this->btn_Quit;

	delete this->Mn_Static_Array;
	delete this->Mn_Dynamic_Array;
	delete this->Mn_Linked_List;
	delete this->Mn_Linked_List_Doubly;
	delete this->Mn_Linked_List_Cirly;
	delete this->Mn_Queue;
	delete this->Mn_Stack;
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
	videoMode.height = 1080;
	videoMode.width = 1920;

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
			this->btn_Linked_List_Singly->update(mousePosWindowf, &event);
			this->btn_Linked_List_Doubly->update(mousePosWindowf, &event);
			this->btn_Linked_List_Cirly->update(mousePosWindowf, &event);
			this->btn_Stack->update(mousePosWindowf, &event);
			this->btn_Queue->update(mousePosWindowf, &event);
			this->btn_Quit->update(mousePosWindowf, &event);

			if (this->btn_Static_Array->isPressed()) AppState = app_static_array, Mn_Static_Array->stat=on; else
			if (this->btn_Dynamic_Array->isPressed()) AppState = app_dynamic_array, Mn_Dynamic_Array->stat = on; else
			if (this->btn_Linked_List_Singly->isPressed()) AppState = app_linked_list, Mn_Linked_List->stat = on; else
			if (this->btn_Linked_List_Doubly->isPressed()) AppState = app_linked_list_D, Mn_Linked_List_Doubly->stat = on; else
			if (this->btn_Linked_List_Cirly->isPressed()) AppState = app_linked_list_C, Mn_Linked_List_Cirly->stat = on; else
			if (this->btn_Queue->isPressed()) AppState = app_queue, Mn_Queue->stat=on; else
			if (this->btn_Stack->isPressed()) AppState = app_stack,Mn_Stack->stat=on; else
			if (this->btn_Quit->isPressed()) AppState = app_quit;

			break;

		case app_static_array:
			Mn_Static_Array->update(mousePosWindowf);
			if (!Mn_Static_Array->stat) AppState = app_main;
			break;

		case app_dynamic_array:
			Mn_Dynamic_Array->update(mousePosWindowf);
			if (!Mn_Dynamic_Array->stat) AppState = app_main;
			break;

		case app_linked_list:
			Mn_Linked_List->update(mousePosWindowf);
			if (!Mn_Linked_List->stat) AppState = app_main;
			break;

		case app_linked_list_D:
			Mn_Linked_List_Doubly->update(mousePosWindowf);
			if (!Mn_Linked_List_Doubly->stat) AppState = app_main;
			break;

		case app_linked_list_C:
			Mn_Linked_List_Cirly->update(mousePosWindowf);
			if (!Mn_Linked_List_Cirly->stat) AppState = app_main;
			break;

		case app_queue:
			Mn_Queue->update(mousePosWindowf);
			if (!Mn_Queue->stat) AppState = app_main;
			break;

		case app_stack:
			Mn_Stack->update(mousePosWindowf);
			if (!Mn_Stack->stat) AppState = app_main;
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
	this->btn_Linked_List_Singly->render(window);
	this->btn_Linked_List_Doubly->render(window);
	this->btn_Linked_List_Cirly->render(window);
	this->btn_Stack->render(window);
	this->btn_Queue->render(window);

	this->btn_Quit->render(window);
}


//Main Loop

void App::pollEvents()
{
	while (running()) {

		while (window->pollEvent(event)) {

			update();

			if (event.type == Event::Closed || AppState==app_quit) {
				window->close();
			}

		}

		switch (AppState)
		{
		case app_main:

			Render();

			break;

		case app_static_array:

			Mn_Static_Array->Render();

			break;

		case app_dynamic_array:
			Mn_Dynamic_Array->Render();

			break;

		case app_linked_list:

			Mn_Linked_List->Render();

			break;

		case app_linked_list_D:

			Mn_Linked_List_Doubly->Render();

			break;

		case app_linked_list_C:

			Mn_Linked_List_Cirly->Render();

			break;

		case app_queue:
			Mn_Queue->Render();

			break;

		case app_stack:

			Mn_Stack->Render();

			break;
		}

		window->display();
	}
}
