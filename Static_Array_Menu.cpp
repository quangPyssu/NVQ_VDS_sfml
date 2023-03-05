#include "Static_Array_Menu.h"
#include <iostream>

Static_Array_Menu::Static_Array_Menu()
{
	this->btn_Initialize = new Button(100, 100, 150, 50, "Initialize", Color::White, Color(10, 255, 50, 255), Color::Yellow, Color::Blue);
	this->btn_Add = new Button(100, 200, 150, 50, "Add", Color::White, Color(10, 255, 50, 255), Color::Yellow, Color::Blue);
	this->btn_Delete = new Button(100, 300, 150, 50, "Delete", Color::White, Color(10, 255, 50, 255), Color::Yellow, Color::Blue);
	this->btn_Update = new Button(100, 400, 150, 50, "Update", Color::White, Color(10, 255, 50, 255), Color::Yellow, Color::Blue);
	this->btn_Search = new Button(100, 500, 150, 50, "Search", Color::White, Color(10, 255, 50, 255), Color::Yellow, Color::Blue);
	this->btn_back = new Button(100, 600, 150, 50, "Back", Color::White, Color(10, 255, 50, 255), Color::Yellow, Color::Blue);

	tet.loadFromFile("asset/texture/condauvoi.jpg");
	sprite.setTexture(tet);
	sprite.setScale(Vector2f(1000.f / tet.getSize().x, 800.f / tet.getSize().y));
	target = nullptr;
	stat = off;
}

Static_Array_Menu::~Static_Array_Menu()
{
	delete btn_Initialize; delete btn_Add;
	delete btn_Delete; delete btn_Update;
	delete btn_Search; delete btn_back;
}

void Static_Array_Menu::Render(RenderTarget* target)
{
	target->clear(Color::Black);
	target->draw(sprite);
	this->btn_Initialize->render(target);
	this->btn_Add->render(target);
	this->btn_Delete->render(target);
	this->btn_Update->render(target);
	this->btn_Search->render(target);
	this->btn_back->render(target);
}

void Static_Array_Menu::update(const Vector2f mousePos)
{
	this->mousePosWindowf = mousePos;
	this->btn_Initialize->update(mousePosWindowf);
	this->btn_Add->update(mousePosWindowf);
	this->btn_Delete->update(mousePosWindowf);
	this->btn_Update->update(mousePosWindowf);
	this->btn_Search->update(mousePosWindowf);
	this->btn_back->update(mousePosWindowf);

	if (this->btn_back->isPressed()) stat=off; else
		if (this->btn_Initialize->isPressed()) ; else
			if (this->btn_Add->isPressed()) ; else
				if (this->btn_Delete->isPressed()) ; else
					if (this->btn_Update->isPressed()) ; else
						if (this->btn_Search->isPressed()); 
}
