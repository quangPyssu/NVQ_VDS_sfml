#include "App.h"

// Constructor

App::App()
{
	initVariables();
	initWindow();

	AppState = app_main;

	window->clear(Color::Color(230,208,159));
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

	window->setFramerateLimit(60);
	Render();
	window->display();

	shape.setFillColor(BGColor[0]+Color::Color(25,25,25));
	shape.setPosition(Vector2f(0,0));
	shape.setSize(Vector2f(btn_Static_Array->pos_x*2 + btn_Static_Array->size_x , window->getSize().y));
	
	srand(time(NULL));
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
	ContextSettings settings;
	settings.antialiasingLevel = 5.0;

	window = new RenderWindow(videoMode, "data Visual", Style::Titlebar | Style::Close, settings);
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

			if (this->btn_Static_Array->isPressed())
			{
				Mn_Static_Array->l.delAll();
				Mn_Static_Array->anime->clearAll();
				Mn_Static_Array->isDrawing = DrawNormal;

				Mn_Static_Array->n = 3 + (rand() % 3);
				for (int i = 0; i < Mn_Static_Array->n; i++) Mn_Static_Array->l.addHead((New(rand() % 100)));

				AppState = app_static_array, Mn_Static_Array->stat = on;
				Mn_Static_Array->theme = this->theme;
				Mn_Static_Array->sizeId = this->sizeId;

				Mn_Static_Array->l.change(sizeId, theme);
			}
			else
				if (this->btn_Dynamic_Array->isPressed())
				{
					Mn_Dynamic_Array->l.delAll();
					Mn_Dynamic_Array->anime->clearAll();
					Mn_Dynamic_Array->isDrawing = DrawNormal;

					Mn_Dynamic_Array->n = 3 + (rand() % 3);
					for (int i = 0; i < Mn_Dynamic_Array->n; i++) Mn_Dynamic_Array->l.addHead((New(rand() % 100)));

					AppState = app_dynamic_array, Mn_Dynamic_Array->stat = on;
					Mn_Dynamic_Array->theme = this->theme;
					Mn_Dynamic_Array->sizeId = this->sizeId;

					Mn_Dynamic_Array->l.change(sizeId, theme);
				}
				else
					if (this->btn_Linked_List_Singly->isPressed())
					{
						Mn_Linked_List->l.delAll();
						Mn_Linked_List->anime->clearAll();
						Mn_Linked_List->isDrawing = DrawNormal;

						Mn_Linked_List->n = 3 + (rand() % 3);
						for (int i = 0; i < Mn_Linked_List->n; i++) Mn_Linked_List->l.addHead((New(rand() % 100)));

						AppState = app_linked_list, Mn_Linked_List->stat = on;
						Mn_Linked_List->theme = this->theme;
						Mn_Linked_List->sizeId = this->sizeId;

						Mn_Linked_List->l.change(sizeId, theme);
					}
					else
				if (this->btn_Linked_List_Doubly->isPressed())
				{
					Mn_Linked_List_Doubly->l.delAll();
					Mn_Linked_List_Doubly->anime->clearAll();
					Mn_Linked_List_Doubly->isDrawing = DrawNormal;

					Mn_Linked_List_Doubly->n = 3 + (rand() % 3);
					for (int i = 0; i < Mn_Linked_List_Doubly->n; i++) Mn_Linked_List_Doubly->l.addHead((New(rand() % 100)));

					AppState = app_linked_list_D, Mn_Linked_List_Doubly->stat = on;
					Mn_Linked_List_Doubly->theme = this->theme;
					Mn_Linked_List_Doubly->sizeId = this->sizeId;

					Mn_Linked_List_Doubly->l.change(sizeId, theme);
				}
				else
					if (this->btn_Linked_List_Cirly->isPressed())
					{
						Mn_Linked_List_Cirly->l.delAll();
						Mn_Linked_List_Cirly->anime->clearAll();
						Mn_Linked_List_Cirly->isDrawing = DrawNormal;

						Mn_Linked_List_Cirly->n = 3 + (rand() % 3);
						for (int i = 0; i < Mn_Linked_List_Cirly->n; i++) Mn_Linked_List_Cirly->l.addHead((New(rand() % 100)));

						AppState = app_linked_list_C, Mn_Linked_List_Cirly->stat = on;
						Mn_Linked_List_Cirly->theme = this->theme;
						Mn_Linked_List_Cirly->sizeId = this->sizeId;

						Mn_Linked_List_Cirly->l.change(sizeId, theme);
					}
					else

				if (this->btn_Queue->isPressed())
				{
					Mn_Queue->l.delAll();
					Mn_Queue->anime->clearAll();
					Mn_Queue->isDrawing = DrawNormal;

					Mn_Queue->n = 3 + (rand() % 3);
					for (int i = 0; i < Mn_Queue->n; i++) Mn_Queue->l.addHead((New(rand() % 100)));

					AppState = app_queue, Mn_Queue->stat = on;
					Mn_Queue->theme = this->theme;
					Mn_Queue->sizeId = this->sizeId;

					Mn_Queue->l.change(sizeId, theme);
				}
				else
					if (this->btn_Stack->isPressed())
					{
						Mn_Stack->l.delAll();
						Mn_Stack->anime->clearAll();
						Mn_Stack->isDrawing = DrawNormal;

						Mn_Stack->n = 3 + (rand() % 3);
						for (int i = 0; i < Mn_Stack->n; i++) Mn_Stack->l.addHead((New(rand() % 100)));

						AppState = app_stack, Mn_Stack->stat = on;
						Mn_Stack->theme = this->theme;
						Mn_Stack->sizeId = this->sizeId;

						Mn_Stack->l.change(sizeId, theme);
					}
					else
			if (this->btn_Quit->isPressed()) AppState = app_quit;

			break;

		case app_static_array:
			Mn_Static_Array->update(mousePosWindowf);
			if (!Mn_Static_Array->stat) AppState = app_main;
			this->theme = Mn_Static_Array->theme;
			this->sizeId = Mn_Static_Array->sizeId;

			break;

		case app_dynamic_array:
			Mn_Dynamic_Array->update(mousePosWindowf);
			if (!Mn_Dynamic_Array->stat) AppState = app_main;
			this->theme = Mn_Dynamic_Array->theme;
			this->sizeId = Mn_Dynamic_Array->sizeId;
			break;

		case app_linked_list:
			Mn_Linked_List->update(mousePosWindowf);
			if (!Mn_Linked_List->stat) AppState = app_main;
			this->theme = Mn_Linked_List->theme;
			this->sizeId = Mn_Linked_List->sizeId;
			break;

		case app_linked_list_D:
			Mn_Linked_List_Doubly->update(mousePosWindowf);
			if (!Mn_Linked_List_Doubly->stat) AppState = app_main;
			this->theme = Mn_Linked_List_Doubly->theme;
			this->sizeId = Mn_Linked_List_Doubly->sizeId;
			break;

		case app_linked_list_C:
			Mn_Linked_List_Cirly->update(mousePosWindowf);
			if (!Mn_Linked_List_Cirly->stat) AppState = app_main;
			this->theme = Mn_Linked_List_Cirly->theme;
			this->sizeId = Mn_Linked_List_Cirly->sizeId;
			break;

		case app_queue:
			Mn_Queue->update(mousePosWindowf);
			if (!Mn_Queue->stat) AppState = app_main;
			this->theme = Mn_Queue->theme;
			this->sizeId = Mn_Queue->sizeId;
			break;

		case app_stack:
			Mn_Stack->update(mousePosWindowf);
			if (!Mn_Stack->stat) AppState = app_main;
			this->theme = Mn_Stack->theme;
			this->sizeId = Mn_Stack->sizeId;
			break;

		default:
		break;
	}
	
	shape.setFillColor(BGColor[theme] + Color::Color(25, 25, 25));
}

void App::Render()
{
	window->clear(BGColor[theme]);
	window->draw(shape);

	//window->draw(sprite);

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
