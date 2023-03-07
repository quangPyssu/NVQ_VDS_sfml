#include "Static_Array_Menu.h"
#include <iostream>

Static_Array_Menu::Static_Array_Menu(Event* event)
{
	// make btn;
	this->btn_Initialize = new Button(50, 50, 0, 0, "Initialize", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue);
	this->btn_Add = new Button(50, 120, 0, 0, "Add", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue);
	this->btn_Delete = new Button(50, 190, 0, 0, "Delete", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue);
	this->btn_Update = new Button(50, 260, 0, 0, "Update", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue);
	this->btn_Search = new Button(50, 330, 0, 0, "Search", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue);
	this->btn_back = new Button(50, 400, 0, 0, "Back", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue);

	// make TextBox&btn for ADD;
	this->box_add_val = new TextBox(240, 120, 0, 0, "Input Value", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue,200,0);
	this->box_add_pos = new TextBox(140, 120, 0, 0, "Input Position", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue, 300,0);

	this->tog_add_head = new ToggleButton(140, 160, 100, 0, "Head", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue,Type_Neighbor);
	this->tog_add_tail = new ToggleButton(140, 200, 100, 0, "Tail", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue,Type_Neighbor);

	tet.loadFromFile("asset/texture/condauvoi.jpg");
	sprite.setTexture(tet);
	sprite.setScale(Vector2f(1000.f / tet.getSize().x, 800.f / tet.getSize().y));

	//set default
	target = nullptr;
	stat = off; 
	add_data_val = nothing;
	add_data_pos = nothing;

	this->event = event;

	l.addHead(New(10));
	l.addTail(New(11));
}

Static_Array_Menu::~Static_Array_Menu()
{
	//Button
	delete btn_Initialize; delete btn_Add;
	delete btn_Delete; delete btn_Update;
	delete btn_Search; delete btn_back;

	delete tog_add_head; delete tog_add_tail;

	//Box

	delete box_add_val; delete box_add_pos;

	// Linked list

	l.delAll();
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

	if (add_stat)
	{
		this->box_add_val->render(target);
		this->box_add_pos->render(target);
		this->tog_add_head->render(target);
		this->tog_add_tail->render(target);
	}
}

void Static_Array_Menu::update_add()
{
	if (box_add_val->data != nothing && add_data_val == nothing) add_data_val = box_add_val->data, box_add_val->data = nothing;
	if (box_add_pos->data != nothing && add_data_pos==nothing) add_data_pos = box_add_pos->data, box_add_val->data = nothing;

	if (add_data_val != nothing && add_data_pos != nothing)
	{
		l.addKth(New(add_data_val), add_data_pos);
		
		add_data_val = add_data_pos = nothing;
	}
	//cout << add_data_pos << endl;
}

void Static_Array_Menu::update(const Vector2f mousePos)
{
	this->mousePosWindowf = mousePos;
	this->btn_Initialize->update(mousePosWindowf,event);
	this->btn_Add->update(mousePosWindowf, event);
	this->btn_Delete->update(mousePosWindowf, event);
	this->btn_Update->update(mousePosWindowf, event);
	this->btn_Search->update(mousePosWindowf, event);
	this->btn_back->update(mousePosWindowf, event);

	if (add_stat)
	{
		this->box_add_val->update(mousePosWindowf, event);
		this->box_add_pos->update(mousePosWindowf, event);
		if (box_add_pos->box_Stat == ACTIVE)
		{
			add_data_pos = nothing;
			tog_add_head->disable();
			tog_add_tail->disable();
		}
		this->tog_add_head->update(mousePosWindowf, event);
		if (tog_add_head->isPressed()) add_data_pos = 0, tog_add_tail->disable(); 
		this->tog_add_tail->update(mousePosWindowf, event);
		if (tog_add_tail->isPressed()) add_data_pos = 21, tog_add_head->disable(); 

		update_add();
	}

	//data getting
	

	if (this->btn_back->isPressed()) stat = off; else
	{
		if (this->btn_Initialize->isPressed()); else
			if (this->btn_Add->isPressed())
			{
				add_stat = !add_stat;
			}
			else
				if (this->btn_Delete->isPressed())
					l.delHead(); else
					if (this->btn_Update->isPressed())
					{
						l.addKth(New(10),5);
					} else
						if (this->btn_Search->isPressed())
						{
							Node* tmp = l.Head;
							while (tmp)
							{
								cout << tmp->data << " ";
								tmp = tmp->Next;
							}
							cout << endl;
						}
		;
	}
}
