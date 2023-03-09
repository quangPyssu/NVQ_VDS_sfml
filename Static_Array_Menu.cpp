#include "Static_Array_Menu.h"
#include <iostream>

Static_Array_Menu::Static_Array_Menu(Event* event)
{
	// make btn;
	this->tog_Initialize = new ToggleButton(50, 50, 0, 0, "Initialize", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue,1);
	this->tog_Add = new ToggleButton(50, 120, 0, 0, "Add", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue,1);
	this->tog_Delete = new ToggleButton(50, 190, 0, 0, "Delete", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue,1);
	this->tog_Update = new ToggleButton(50, 260, 0, 0, "Update", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue,1);
	this->tog_Search = new ToggleButton(50, 330, 0, 0, "Search", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue,1);
	this->btn_back = new Button(50, 400, 0, 0, "Back", Color::White, Color(10, 255, 50, 255), Color(246,190,0,255), Color::Blue);

	Toggle_Group_Static_Array.Toggle_Btn_Grp[0] = tog_Initialize;	Toggle_Group_Static_Array.Toggle_Btn_Grp[1] = tog_Add;	Toggle_Group_Static_Array.Toggle_Btn_Grp[2] = tog_Delete;
	Toggle_Group_Static_Array.Toggle_Btn_Grp[3] = tog_Update;	Toggle_Group_Static_Array.Toggle_Btn_Grp[4] = tog_Search;
	
	Toggle_Group_Static_Array.n = 5;

	// make TextBox&btn for ADD;
	this->box_add_val = new TextBox(240, tog_Add->pos_y, 0, 0, "Input Value", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue,200,0);
	this->box_add_pos = new TextBox(140, tog_Add->pos_y, 0, 0, "Input Position", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue, 300,0);

	this->tog_add_head = new ToggleButton(box_add_pos->pos_x, 85, 100, 0, "Head", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue,Type_Neighbor);
	this->tog_add_tail = new ToggleButton(box_add_pos->pos_x, 155, 100, 0, "Tail", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue,Type_Neighbor);
	this->tog_add_pos = new ToggleButton(box_add_pos->pos_x, box_add_pos->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor);

	Toggle_Group_Add.Toggle_Btn_Grp[0] = tog_add_head;	Toggle_Group_Add.Toggle_Btn_Grp[1] = tog_add_tail;	Toggle_Group_Add.Toggle_Btn_Grp[2] = tog_add_pos;
	Toggle_Group_Add.n = 3;

	// make TextBox&btn for DEL;
	this->box_del_pos = new TextBox(140, tog_Delete->pos_y, 0, 0, "Input Position", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue, 300, 0);

	this->tog_del_head = new ToggleButton(box_del_pos->pos_x, box_del_pos->pos_y-35, 100, 0, "Head", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue, Type_Neighbor);
	this->tog_del_tail = new ToggleButton(box_del_pos->pos_x, box_del_pos->pos_y+35, 100, 0, "Tail", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue, Type_Neighbor);
	this->tog_del_pos = new ToggleButton(box_del_pos->pos_x, box_del_pos->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor);

	Toggle_Group_Del.Toggle_Btn_Grp[0] = tog_del_head;	Toggle_Group_Del.Toggle_Btn_Grp[1] = tog_del_tail;	Toggle_Group_Del.Toggle_Btn_Grp[2] = tog_del_pos;
	Toggle_Group_Del.n = 3;

	// Back display

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
	delete tog_Initialize; delete tog_Add;
	delete tog_Delete; delete tog_Update;
	delete tog_Search; delete btn_back;

	delete tog_add_head; delete tog_add_tail;
	delete tog_add_pos;

	delete tog_del_head; delete tog_del_tail;
	delete tog_del_pos;

	//Box

	delete box_add_val; delete box_add_pos;

	delete box_del_pos;

	// Linked list

	l.delAll();
}

void Static_Array_Menu::Render(RenderTarget* target)
{
	target->clear(Color::Black);
	target->draw(sprite);
	this->tog_Initialize->render(target);
	this->tog_Add->render(target);
	this->tog_Delete->render(target);
	this->tog_Update->render(target);
	this->tog_Search->render(target);
	this->btn_back->render(target);

	if (tog_Add->Toggled())
	{
		this->tog_add_head->render(target);
		this->tog_add_tail->render(target);
		this->box_add_val->render(target);
		this->box_add_pos->render(target);
	}

	if (tog_Delete->Toggled())
	{
		this->tog_del_head->render(target);
		this->tog_del_tail->render(target);
		this->box_del_pos->render(target);
	}
}

void Static_Array_Menu::update_add()
{
	if (box_add_val->data != nothing && add_data_val == nothing) add_data_val = box_add_val->data, box_add_val->data = nothing;
	if (box_add_pos->data != nothing && add_data_pos == nothing) add_data_pos = box_add_pos->data, box_add_val->data = nothing;

	if (tog_add_head->Toggled()) add_data_pos = 0;  	if (tog_add_tail->Toggled()) add_data_pos = 21;

	if (add_data_val != nothing && add_data_pos != nothing)
	{
		l.addKth(New(add_data_val), add_data_pos);
		
		// Delete later
		{
			Node* tmp = l.Head;
			while (tmp != nullptr)
			{
				cout << tmp->data << " ";
				tmp = tmp->Next;
			}cout << endl;
		}
		
		add_data_val = add_data_pos = nothing;
	}
}

void Static_Array_Menu::update_del()
{
	if (box_del_pos->data != nothing && del_data_pos == nothing) del_data_pos = box_del_pos->data;

	if (tog_del_head->Toggled()) del_data_pos = 0; 	if (tog_del_tail->Toggled()) del_data_pos = 21;

	if (del_data_pos != nothing && box_del_pos->btn_cofirm->isPressed())
	{
		l.delKth(del_data_pos);

		// Delete later
		{
			Node* tmp = l.Head;
			while (tmp != nullptr)
			{
				cout << tmp->data << " ";
				tmp = tmp->Next;
			}cout << endl;
		}

		del_data_pos = nothing;
	}
}

void Static_Array_Menu::update(const Vector2f mousePos)
{
	this->mousePosWindowf = mousePos;
	this->tog_Initialize->update(mousePosWindowf,event);
	this->tog_Add->update(mousePosWindowf, event);
	this->tog_Delete->update(mousePosWindowf, event);
	this->tog_Update->update(mousePosWindowf, event);
	this->tog_Search->update(mousePosWindowf, event);
	this->btn_back->update(mousePosWindowf, event);

	// ADD

	if (tog_Add->Toggled())
	{
		this->box_add_val->update(mousePosWindowf, event);
		this->box_add_pos->update(mousePosWindowf, event);
		this->tog_add_head->update(mousePosWindowf, event);
		this->tog_add_tail->update(mousePosWindowf, event);
		this->tog_add_pos->update(mousePosWindowf, event);

		if (this->tog_add_head->isPressed(mousePosWindowf, event)) Toggle_Group_Add.update(0); 
		
		if (this->tog_add_tail->isPressed(mousePosWindowf, event)) Toggle_Group_Add.update(1); 

		if (this->tog_add_pos->isPressed(mousePosWindowf, event)) Toggle_Group_Add.update(2);

		update_add();
	}

	// DELETE

	if (tog_Delete->Toggled())
	{
		this->box_del_pos->update(mousePosWindowf, event);
		this->tog_del_head->update(mousePosWindowf, event);
		this->tog_del_tail->update(mousePosWindowf, event);
		this->tog_del_pos->update(mousePosWindowf, event);

		if (this->tog_del_head->isPressed(mousePosWindowf, event)) Toggle_Group_Del.update(0);

		if (this->tog_del_tail->isPressed(mousePosWindowf, event)) Toggle_Group_Del.update(1);

		if (this->tog_del_pos->isPressed(mousePosWindowf, event)) Toggle_Group_Del.update(2);

		update_del();
	}

	

	if (this->btn_back->isPressed()) stat = off; else
	{
		if (this->tog_Initialize->isPressed(mousePosWindowf, event)) Toggle_Group_Static_Array.update(0);
		
		if (this->tog_Add->isPressed(mousePosWindowf, event)) Toggle_Group_Static_Array.update(1); 
		
		if (this->tog_Delete->isPressed(mousePosWindowf, event)) Toggle_Group_Static_Array.update(2); 
		
		if (this->tog_Update->isPressed(mousePosWindowf, event)) Toggle_Group_Static_Array.update(3); 

		if (this->tog_Search->isPressed(mousePosWindowf, event)) Toggle_Group_Static_Array.update(4);
	}
}
