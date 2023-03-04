#include "App.h"
#include <iostream>

// Constructor

App::App()
{
	initVariables();
	initWindow();

	window->clear(Color::Black);
	tet.loadFromFile("asset/texture/condauvoi.jpg");
	sprite.setTexture(tet);
	sprite.setScale(Vector2f(1000.f / tet.getSize().x, 800.f / tet.getSize().y));
	window->draw(sprite);

	this->btn_Static_Array = new Button(100, 100, 150, 50, "Static Array", Color::White, Color(10, 255, 50, 255), Color::Yellow, Color::Blue);

	this->btn_Dynamic_Array = new Button(100, 200, 150, 50, "Dynamic Array", Color::White, Color::Green, Color::Yellow, Color::Blue);

	this->btn_Linked_List = new Button(100, 300, 150, 50, "Linked List", Color::White, Color::Green, Color::Yellow, Color::Blue);

	this->btn_Stack = new Button(100, 400, 150, 50, "Stack", Color::White, Color::Green, Color::Yellow, Color::Blue);

	this->btn_Queue = new Button(100, 500, 150, 50, "Queue", Color::White, Color::Green, Color::Yellow, Color::Blue);

	window->setFramerateLimit(60);
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
	this->btn_Static_Array->update(mousePosWindowf);
	this->btn_Dynamic_Array->update(mousePosWindowf);
	this->btn_Linked_List->update(mousePosWindowf);
	this->btn_Stack->update(mousePosWindowf);
	this->btn_Queue->update(mousePosWindowf);
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

	window->display();
}


//Main Loop

void App::pollEvents()
{
	while (running()) {

		while (window->pollEvent(ev)) {

			update();

			if (ev.type == Event::Closed) {
				window->close();
			}
		}

		Render();

	}
}
