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

	// make TextBox&btn for INITIALIZE;
	{

		this->box_init_read = new TextBox(tog_Initialize->pos_x + 340, tog_Initialize->pos_y, 0, 0, "Input Value", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue, 200, 0, 50);
		this->box_init_fixed = new TextBox(tog_Initialize->pos_x + 240, tog_Initialize->pos_y, 0, 0, "Input Size", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue, 300, 0, 9);

		this->tog_init_empty = new ToggleButton(tog_Initialize->pos_x + 100, tog_Initialize->pos_y, 70, 0, "Empty", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue, Type_Neighbor);
		this->tog_init_random = new ToggleButton(tog_Initialize->pos_x + 170, tog_Initialize->pos_y, 70, 0, "Random", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue, Type_Neighbor);
		this->tog_init_fixed = new ToggleButton(tog_Initialize->pos_x + 240, tog_Initialize->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor);
		this->tog_init_read = new ToggleButton(tog_Initialize->pos_x + 340, tog_Initialize->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor);
		this->tog_init_load = new ToggleButton(tog_Initialize->pos_x + 440, tog_Initialize->pos_y, 70, 0, "Load", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue, Type_Neighbor);

		Toggle_Group_Init.Toggle_Btn_Grp[0] = tog_init_empty;	Toggle_Group_Init.Toggle_Btn_Grp[1] = tog_init_random;	Toggle_Group_Init.Toggle_Btn_Grp[2] = tog_init_fixed;
		Toggle_Group_Init.Toggle_Btn_Grp[3] = tog_init_read;	Toggle_Group_Init.Toggle_Btn_Grp[4] = tog_init_load;
		Toggle_Group_Init.n = 5;
	}

	// make TextBox&btn for ADD;
	{
		this->box_add_val = new TextBox(240, tog_Add->pos_y, 0, 0, "Input Value", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue, 200, 0, 9);
		this->box_add_pos = new TextBox(140, tog_Add->pos_y, 0, 0, "Input Position", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue, 300, 0, 9);

		this->tog_add_head = new ToggleButton(box_add_pos->pos_x, 85, 100, 0, "Head", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue, Type_Neighbor);
		this->tog_add_tail = new ToggleButton(box_add_pos->pos_x, 155, 100, 0, "Tail", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue, Type_Neighbor);
		this->tog_add_pos = new ToggleButton(box_add_pos->pos_x, box_add_pos->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor);

		Toggle_Group_Add.Toggle_Btn_Grp[0] = tog_add_head;	Toggle_Group_Add.Toggle_Btn_Grp[1] = tog_add_tail;	Toggle_Group_Add.Toggle_Btn_Grp[2] = tog_add_pos;
		Toggle_Group_Add.n = 3;
	}

	// make TextBox&btn for DEL;
	{
		this->box_del_pos = new TextBox(140, tog_Delete->pos_y, 0, 0, "Input Position", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue, 300, 0, 9);

		this->tog_del_head = new ToggleButton(box_del_pos->pos_x, box_del_pos->pos_y - 35, 100, 0, "Head", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue, Type_Neighbor);
		this->tog_del_tail = new ToggleButton(box_del_pos->pos_x, box_del_pos->pos_y + 35, 100, 0, "Tail", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue, Type_Neighbor);
		this->tog_del_pos = new ToggleButton(box_del_pos->pos_x, box_del_pos->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor);

		Toggle_Group_Del.Toggle_Btn_Grp[0] = tog_del_head;	Toggle_Group_Del.Toggle_Btn_Grp[1] = tog_del_tail;	Toggle_Group_Del.Toggle_Btn_Grp[2] = tog_del_pos;
		Toggle_Group_Del.n = 3;
	}

	// make TextBox&btn for UPDATE;
	{
		this->box_upd_val = new TextBox(240, tog_Update->pos_y, 0, 0, "Input Value", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue, 200, 0, 9);
		this->box_upd_pos = new TextBox(140, tog_Update->pos_y, 0, 0, "Input Position", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue, 300, 0, 9);

		this->tog_upd_head = new ToggleButton(box_upd_pos->pos_x, box_upd_pos->pos_y - 35, 100, 0, "Head", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue, Type_Neighbor);
		this->tog_upd_tail = new ToggleButton(box_upd_pos->pos_x, box_upd_pos->pos_y + 35, 100, 0, "Tail", Color::White, Color(10, 255, 50, 255), Color(246, 190, 0, 255), Color::Blue, Type_Neighbor);
		this->tog_upd_pos = new ToggleButton(box_upd_pos->pos_x, box_upd_pos->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor);


		Toggle_Group_Upd.Toggle_Btn_Grp[0] = tog_upd_head;	Toggle_Group_Upd.Toggle_Btn_Grp[1] = tog_upd_tail;	Toggle_Group_Upd.Toggle_Btn_Grp[2] = tog_upd_pos;
		Toggle_Group_Upd.n = 3;
	}

	// make TextBox&btn for SEARCH;
	{
		this->box_ser_val = new TextBox(240, tog_Search->pos_y, 0, 0, "Input Value", Color::White, Color::Red, Color(246, 190, 0, 255), Color::Blue, 200, 0, 9);
	}

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
	srand(time(NULL));
}

Static_Array_Menu::~Static_Array_Menu()
{
	//Button
	delete tog_Initialize; delete tog_Add;
	delete tog_Delete; delete tog_Update;
	delete tog_Search; delete btn_back;

	delete tog_init_empty; delete tog_init_fixed;
	delete tog_init_load; delete tog_init_random;
	delete tog_init_read;

	delete tog_add_head; delete tog_add_tail;
	delete tog_add_pos;

	delete tog_del_head; delete tog_del_tail;
	delete tog_del_pos;

	delete tog_upd_head; delete tog_upd_tail;
	delete tog_upd_pos;

	//Box

	delete box_init_fixed; delete box_init_read;

	delete box_add_val; delete box_add_pos;

	delete box_del_pos;

	delete box_upd_pos; delete box_upd_val;

	delete box_ser_val;

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

	if (tog_Initialize->Toggled())
	{
		tog_init_empty->render(target);
		tog_init_random->render(target);
		tog_init_load->render(target);

		box_init_read->render(target);
		box_init_fixed->render(target);
	}

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

	if (tog_Update->Toggled())
	{
		this->tog_upd_head->render(target);
		this->tog_upd_tail->render(target);
		this->box_upd_val->render(target);
		this->box_upd_pos->render(target);
	}

	if (tog_Search->Toggled())
	{
		this->box_ser_val->render(target);
	}
}

void Static_Array_Menu::update_init()
{
	if (tog_init_empty->Toggled()) init_stat = init_empty;
	if (tog_init_random->Toggled()) init_stat = init_random;
	if (tog_init_fixed->Toggled()) init_stat = init_fixed;
	if (tog_init_read->Toggled()) init_stat = init_read;
	if (tog_init_load->Toggled()) init_stat = init_load;

	if (box_init_fixed->data != nothing && init_data_size == nothing) init_data_size = box_init_fixed->data, box_init_fixed->data = nothing;

	if (box_init_fixed->btn_cofirm->isPressed())
	{
		switch (this->init_stat)
		{
			case init_empty:
				l.delAll();
				break;

			case init_random:
				l.delAll();
				n = rand() % 11;
				for (int i = 0; i < n; i++) l.addHead((New(rand() % 100)));
				break;

			case init_fixed:
				if (init_data_size != nothing )
				{	
					if (init_data_size < 21)
					{
						n = init_data_size;
						l.delAll();
						for (int i = 0; i < n; i++) l.addHead((New(rand() % 100)));
					}
					init_data_size = nothing;
				}

				break;

			case init_read:
				init_get.StringFilter(box_init_read->input_text);
				
				if (!init_get.init_data.empty())
				{
					l.delAll();
					for (int i : init_get.init_data) l.addTail(New(i));
				}
				break;

			case init_load:

				break;

		}
		// Delete later
		{
			Node* tmp = l.Head;
			while (tmp != nullptr)
			{
				cout << tmp->data << " ";
				tmp = tmp->Next;
			}cout << endl;
		}
	}
}

void Static_Array_Menu::update_add()
{
	if (tog_add_head->Toggled()) add_data_pos = 0;  	
	if (tog_add_tail->Toggled()) add_data_pos = 21;
	if (tog_add_pos->Toggled()) add_data_pos = nothing;
	
	if (box_add_val->data != nothing && add_data_val == nothing) add_data_val = box_add_val->data, box_add_val->data = nothing;
	if (box_add_pos->data != nothing && add_data_pos == nothing) add_data_pos = box_add_pos->data, box_add_val->data = nothing;

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
	if (tog_del_head->Toggled()) del_data_pos = 0; 	
	if (tog_del_tail->Toggled()) del_data_pos = 21;
	if (tog_del_pos->Toggled()) del_data_pos = nothing;
	
	if (box_del_pos->data != nothing && del_data_pos == nothing) del_data_pos = box_del_pos->data;

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

void Static_Array_Menu::update_upd()
{
	if (tog_upd_head->Toggled()) upd_data_pos = 0;
	if (tog_upd_tail->Toggled()) upd_data_pos = 21;
	if (tog_upd_pos->Toggled()) upd_data_pos = nothing;

	if (box_upd_val->data != nothing && upd_data_val == nothing) upd_data_val = box_upd_val->data, box_upd_val->data = nothing;
	if (box_upd_pos->data != nothing && upd_data_pos == nothing) upd_data_pos = box_upd_pos->data, box_upd_val->data = nothing;

	if (upd_data_val != nothing && upd_data_pos != nothing)
	{
		l.UpdateKth(upd_data_pos, upd_data_val);

		// Delete later
		{
			Node* tmp = l.Head;
			while (tmp != nullptr)
			{
				cout << tmp->data << " ";
				tmp = tmp->Next;
			}cout << endl;
		}

		upd_data_val = upd_data_pos = nothing;
	}
}

void Static_Array_Menu::update_search()
{
	if (box_ser_val->data != nothing && ser_data_val == nothing) ser_data_val = box_ser_val->data, box_ser_val->data = nothing;

	if (box_ser_val->btn_cofirm->isPressed())
	{
		if (ser_data_val != nothing)
		{
			cout << ser_data_val << ": " << l.find(ser_data_val) << endl;
			ser_data_val = nothing;
		}
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

	// INITIALIZE

	if (tog_Initialize->Toggled())
	{
		this->tog_init_empty->update(mousePosWindowf, event);
		this->tog_init_random->update(mousePosWindowf,event);
		this->tog_init_fixed->update(mousePosWindowf, event);
		this->tog_init_read->update(mousePosWindowf, event);
		this->tog_init_load->update(mousePosWindowf, event);

		if (this->tog_init_empty->isPressed(mousePosWindowf, event)) Toggle_Group_Init.update(0);

		if (this->tog_init_random->isPressed(mousePosWindowf, event)) Toggle_Group_Init.update(1);

		if (this->tog_init_fixed->isPressed(mousePosWindowf, event)) Toggle_Group_Init.update(2);

		if (this->tog_init_read->isPressed(mousePosWindowf, event)) Toggle_Group_Init.update(3);

		if (this->tog_init_load->isPressed(mousePosWindowf, event)) Toggle_Group_Init.update(4);

		this->box_init_read->update(mousePosWindowf, event);
		this->box_init_fixed->update(mousePosWindowf, event);

		update_init();
	}

	// ADD

	if (tog_Add->Toggled())
	{
		this->tog_add_head->update(mousePosWindowf, event);
		this->tog_add_tail->update(mousePosWindowf, event);
		this->tog_add_pos->update(mousePosWindowf, event);

		if (this->tog_add_head->isPressed(mousePosWindowf, event)) Toggle_Group_Add.update(0); 
		
		if (this->tog_add_tail->isPressed(mousePosWindowf, event)) Toggle_Group_Add.update(1); 

		if (this->tog_add_pos->isPressed(mousePosWindowf, event)) Toggle_Group_Add.update(2);
		
		this->box_add_val->update(mousePosWindowf, event);
		this->box_add_pos->update(mousePosWindowf, event);

		update_add();
	}

	// DELETE

	if (tog_Delete->Toggled())
	{
		this->tog_del_head->update(mousePosWindowf, event);
		this->tog_del_tail->update(mousePosWindowf, event);
		this->tog_del_pos->update(mousePosWindowf, event);

		if (this->tog_del_head->isPressed(mousePosWindowf, event)) Toggle_Group_Del.update(0);

		if (this->tog_del_tail->isPressed(mousePosWindowf, event)) Toggle_Group_Del.update(1);

		if (this->tog_del_pos->isPressed(mousePosWindowf, event)) Toggle_Group_Del.update(2);
		
		this->box_del_pos->update(mousePosWindowf, event);

		update_del();
	}

	// UPDATE

	if (tog_Update->Toggled())
	{
		this->tog_upd_head->update(mousePosWindowf, event);
		this->tog_upd_tail->update(mousePosWindowf, event);
		this->tog_upd_pos->update(mousePosWindowf, event);

		if (this->tog_upd_head->isPressed(mousePosWindowf, event)) Toggle_Group_Upd.update(0);

		if (this->tog_upd_tail->isPressed(mousePosWindowf, event)) Toggle_Group_Upd.update(1);

		if (this->tog_upd_pos->isPressed(mousePosWindowf, event)) Toggle_Group_Upd.update(2);

		this->box_upd_val->update(mousePosWindowf, event);
		this->box_upd_pos->update(mousePosWindowf, event);

		update_upd();
	}

	// SEARCH

	if (tog_Search->Toggled())
	{
		this->box_ser_val->update(mousePosWindowf, event);

		update_search();
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
