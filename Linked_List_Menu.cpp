#include "Linked_List_Menu.h"
#include <iostream>

Linked_List_Menu::Linked_List_Menu(Event* event, RenderWindow* window)
{
	// make btn;
	this->tog_Initialize = new ToggleButton(50, 50, 0, 0, "Initialize", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
	this->tog_Add = new ToggleButton(50, 90, 0, 0, "Add", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
	this->tog_Delete = new ToggleButton(50, 130, 0, 0, "Delete", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
	this->tog_Update = new ToggleButton(50, 170, 0, 0, "Update", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
	this->tog_Search = new ToggleButton(50, 210, 0, 0, "Search", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
	this->btn_back = new Button(50, 250, 0, 0, "Back", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Color::Black);

	Toggle_Group_Linked_List.Toggle_Btn_Grp[0] = tog_Initialize;	Toggle_Group_Linked_List.Toggle_Btn_Grp[1] = tog_Add;	Toggle_Group_Linked_List.Toggle_Btn_Grp[2] = tog_Delete;
	Toggle_Group_Linked_List.Toggle_Btn_Grp[3] = tog_Update;	Toggle_Group_Linked_List.Toggle_Btn_Grp[4] = tog_Search;

	Toggle_Group_Linked_List.n = 5;

	Toggle_Group_Linked_List.event = event;

	// make TextBox&btn for INITIALIZE;
	{
		this->box_init_read = new TextBox(tog_Initialize->pos_x + 340, tog_Initialize->pos_y, 0, 0, "Input Value", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), 200, 0, 50, Color::Black);
		this->box_init_fixed = new TextBox(tog_Initialize->pos_x + 240, tog_Initialize->pos_y, 0, 0, "Input Size", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), 300, 0, 9, Color::Black);

		this->tog_init_empty = new ToggleButton(tog_Initialize->pos_x + 100, tog_Initialize->pos_y, 70, 0, "Empty", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
		this->tog_init_random = new ToggleButton(tog_Initialize->pos_x + 170, tog_Initialize->pos_y, 70, 0, "Random", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
		this->tog_init_fixed = new ToggleButton(tog_Initialize->pos_x + 240, tog_Initialize->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor, Color::Black);
		this->tog_init_read = new ToggleButton(tog_Initialize->pos_x + 340, tog_Initialize->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor, Color::Black);
		this->tog_init_load = new ToggleButton(tog_Initialize->pos_x + 440, tog_Initialize->pos_y, 70, 0, "Load", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);

		Toggle_Group_Init.Toggle_Btn_Grp[0] = tog_init_empty;	Toggle_Group_Init.Toggle_Btn_Grp[1] = tog_init_random;	Toggle_Group_Init.Toggle_Btn_Grp[2] = tog_init_fixed;
		Toggle_Group_Init.Toggle_Btn_Grp[3] = tog_init_read;	Toggle_Group_Init.Toggle_Btn_Grp[4] = tog_init_load;
		Toggle_Group_Init.n = 5;

		Toggle_Group_Init.event = event;
	}

	// make TextBox&btn for ADD;
	{
		this->box_add_val = new TextBox(tog_Add->pos_x + 200, tog_Add->pos_y, 0, 0, "Input Value", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), 120, 0, 9, Color::Black);
		this->box_add_pos = new TextBox(tog_Add->pos_x + 100, tog_Add->pos_y, 0, 0, "Input Position", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), 220, 0, 9, Color::Black);

		this->tog_add_head = new ToggleButton(box_add_pos->pos_x, box_add_pos->pos_y - 35, 100, 0, "Head", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
		this->tog_add_tail = new ToggleButton(box_add_pos->pos_x, box_add_pos->pos_y + 35, 100, 0, "Tail", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
		this->tog_add_pos = new ToggleButton(box_add_pos->pos_x, box_add_pos->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor, Color::Black);

		Toggle_Group_Add.Toggle_Btn_Grp[0] = tog_add_head;	Toggle_Group_Add.Toggle_Btn_Grp[1] = tog_add_tail;	Toggle_Group_Add.Toggle_Btn_Grp[2] = tog_add_pos;
		Toggle_Group_Add.n = 3;
		Toggle_Group_Add.event = event;
	}

	// make TextBox&btn for DEL;
	{
		this->box_del_pos = new TextBox(tog_Delete->pos_x + 100, tog_Delete->pos_y, 0, 0, "Input Position", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), 120, 0, 9, Color::Black);

		this->tog_del_head = new ToggleButton(box_del_pos->pos_x, box_del_pos->pos_y - 35, 100, 0, "Head", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
		this->tog_del_tail = new ToggleButton(box_del_pos->pos_x, box_del_pos->pos_y + 35, 100, 0, "Tail", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
		this->tog_del_pos = new ToggleButton(box_del_pos->pos_x, box_del_pos->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor, Color::Black);

		Toggle_Group_Del.Toggle_Btn_Grp[0] = tog_del_head;	Toggle_Group_Del.Toggle_Btn_Grp[1] = tog_del_tail;	Toggle_Group_Del.Toggle_Btn_Grp[2] = tog_del_pos;
		Toggle_Group_Del.n = 3;
		Toggle_Group_Del.event = event;
	}

	// make TextBox&btn for UPDATE;
	{
		this->box_upd_val = new TextBox(tog_Update->pos_x + 200, tog_Update->pos_y, 0, 0, "Input Value", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), 120, 0, 9, Color::Black);
		this->box_upd_pos = new TextBox(tog_Update->pos_x + 100, tog_Update->pos_y, 0, 0, "Input Position", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), 220, 0, 9, Color::Black);

		this->tog_upd_head = new ToggleButton(box_upd_pos->pos_x, box_upd_pos->pos_y - 35, 100, 0, "Head", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
		this->tog_upd_tail = new ToggleButton(box_upd_pos->pos_x, box_upd_pos->pos_y + 35, 100, 0, "Tail", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Type_Neighbor, Color::Black);
		this->tog_upd_pos = new ToggleButton(box_upd_pos->pos_x, box_upd_pos->pos_y, 100, 0, "", Color::White, Color::Black, Color::Green, Color::Blue, Type_Neighbor, Color::Black);


		Toggle_Group_Upd.Toggle_Btn_Grp[0] = tog_upd_head;	Toggle_Group_Upd.Toggle_Btn_Grp[1] = tog_upd_tail;	Toggle_Group_Upd.Toggle_Btn_Grp[2] = tog_upd_pos;
		Toggle_Group_Upd.n = 3;
		Toggle_Group_Upd.event = event;
	}

	// make TextBox&btn for SEARCH;
	{
		this->box_ser_val = new TextBox(tog_Search->pos_x + 100, tog_Search->pos_y, 0, 0, "Input Value", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), 120, 0, 9, Color::Black);
	}

	// Back display

	tet.loadFromFile("asset/texture/cream.jpg");
	sprite.setTexture(tet);
	sprite.setScale(Vector2f(1350.f / tet.getSize().x, 800.f / tet.getSize().y));

	//set default
	this->window = window;
	stat = off;
	add_data_val = nothing;
	add_data_pos = nothing;

	this->event = event;

	anime = new Animation(event, &l, window);

	srand(time(NULL));
}

Linked_List_Menu::~Linked_List_Menu()
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

void Linked_List_Menu::drawFrom(int Current)
{
	cout << "Step " << anime->step << endl;
	isDrawing = 1;

	for (int i = Current; i < anime->step; i++)
	{
		Render();
		anime->drawOneStep(i);
		window->display();
		Sleep(500);
	}

	isDrawing = 0;
}

void Linked_List_Menu::Render()
{
	window->clear(Color::Black);
	window->draw(sprite);
	this->tog_Initialize->render(window);
	this->tog_Add->render(window);
	this->tog_Delete->render(window);
	this->tog_Update->render(window);
	this->tog_Search->render(window);
	this->btn_back->render(window);

	if (tog_Initialize->Toggled())
	{
		tog_init_empty->render(window);
		tog_init_random->render(window);
		tog_init_load->render(window);

		box_init_read->render(window);
		box_init_fixed->render(window);
	}

	if (tog_Add->Toggled())
	{
		this->tog_add_head->render(window);
		this->tog_add_tail->render(window);
		this->box_add_val->render(window);
		this->box_add_pos->render(window);
	}

	if (tog_Delete->Toggled())
	{
		this->tog_del_head->render(window);
		this->tog_del_tail->render(window);
		this->box_del_pos->render(window);
	}

	if (tog_Update->Toggled())
	{
		this->tog_upd_head->render(window);
		this->tog_upd_tail->render(window);
		this->box_upd_val->render(window);
		this->box_upd_pos->render(window);
	}

	if (tog_Search->Toggled())
	{
		this->box_ser_val->render(window);
	}

	if (!isDrawing) l.render(window);
}

void Linked_List_Menu::update_init()
{
	if (tog_init_empty->Toggled()) init_stat = init_empty;
	if (tog_init_random->Toggled()) init_stat = init_random;
	if (tog_init_fixed->Toggled()) init_stat = init_fixed;
	if (tog_init_read->Toggled()) init_stat = init_read;
	if (tog_init_load->Toggled()) init_stat = init_load;

	if (box_init_fixed->data != nothing && init_data_size == nothing) init_data_size = box_init_fixed->data, box_init_fixed->data = nothing;

	if (box_init_fixed->btn_cofirm->isPressed())
	{
		tog_Initialize->disable();
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
			if (init_data_size != nothing)
			{
				if (init_data_size <= 10)
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
			l.delAll();

			for (int i : init_get.init_data) l.addTail(New(i));

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

void Linked_List_Menu::update_add()
{
	if (tog_add_head->Toggled()) add_data_pos = 0;
	if (tog_add_tail->Toggled()) add_data_pos = 11;
	if (tog_add_pos->Toggled()) add_data_pos = nothing;

	if (box_add_val->data != nothing && add_data_val == nothing) add_data_val = box_add_val->data, box_add_val->data = nothing;
	if (box_add_pos->data != nothing && add_data_pos == nothing) add_data_pos = box_add_pos->data, box_add_val->data = nothing;

	if (add_data_val != nothing && add_data_pos != nothing && l.Size < 10)
	{
		tog_Add->disable();

		anime->clearAll();
		
		if (l.Size)
		{
			if (tog_add_tail->Toggled()) anime->MakeChoosenUpTo(l.Size - 1, l.Size - 1); else
				anime->MakeChoosenUpTo(0, min(add_data_pos, l.Size - 1));
		}

		l.addKth(New(add_data_val), add_data_pos);
		
		anime->Add_pos(add_data_pos, add_data_val);

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
		drawFrom(0);
	}
	else if (l.Size == 10) add_data_val = add_data_pos = nothing;
}

void Linked_List_Menu::update_del()
{
	if (tog_del_head->Toggled()) del_data_pos = 0;
	if (tog_del_tail->Toggled()) del_data_pos = 11;
	if (tog_del_pos->Toggled()) del_data_pos = nothing;

	if (box_del_pos->data != nothing && del_data_pos == nothing) del_data_pos = box_del_pos->data;

	if (del_data_pos != nothing && box_del_pos->btn_cofirm->isPressed())
	{
		tog_Delete->disable();

		anime->clearAll();
		if (l.Size)
		{
			anime->MakeChoosenUpTo(0, min(del_data_pos, l.Size - 1));
			anime->Del_pos(del_data_pos);
			drawFrom(0);
		}

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

void Linked_List_Menu::update_upd()
{
	if (tog_upd_head->Toggled()) upd_data_pos = 0;
	if (tog_upd_tail->Toggled()) upd_data_pos = 10;
	if (tog_upd_pos->Toggled()) upd_data_pos = nothing;

	if (box_upd_val->data != nothing && upd_data_val == nothing) upd_data_val = box_upd_val->data, box_upd_val->data = nothing;
	if (box_upd_pos->data != nothing && upd_data_pos == nothing) upd_data_pos = box_upd_pos->data, box_upd_val->data = nothing;

	if (upd_data_val != nothing && upd_data_pos != nothing)
	{
		tog_Update->disable();

		anime->clearAll();

		if (l.Size)
		{
			anime->MakeChoosenUpTo(0, min(upd_data_pos, l.Size - 1));
			anime->MakeFillIndex(min(upd_data_pos, l.Size - 1), Color::Yellow);
			drawFrom(0);
		}

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

		//draw
	
		
	}
}

void Linked_List_Menu::update_search()
{
	if (box_ser_val->data != nothing && ser_data_val == nothing) ser_data_val = box_ser_val->data, box_ser_val->data = nothing;

	if (box_ser_val->btn_cofirm->isPressed())
	{
		tog_Search->disable();
		if (ser_data_val != nothing)
		{
			Search_Result = l.find(ser_data_val);
			cout << ser_data_val << ": " << Search_Result << endl;
			ser_data_val = nothing;

			anime->clearAll();

			if (Search_Result != -1)
			{
				anime->MakeChoosenUpTo(0, Search_Result);
				anime->MakeFillIndex(Search_Result, Color::Cyan);
			}
			else
			{
				anime->MakeChoosenUpTo(0, l.Size);
			}

			drawFrom(0);
		}


	}
}

void Linked_List_Menu::update(const Vector2f mousePos)
{
	this->mousePosWindowf = mousePos;

	this->btn_back->update(mousePosWindowf, event);

	if (this->btn_back->isPressed())
	{
		//Sleep(10)
		stat = off;
		Toggle_Group_Linked_List.clearAll();
		l.delAll();
	}
	else Toggle_Group_Linked_List.filter(mousePos, event);

	// INITIALIZE

	if (tog_Initialize->Toggled())
	{
		Toggle_Group_Init.filter(mousePos, event);

		this->box_init_read->update(mousePosWindowf, event);
		this->box_init_fixed->update(mousePosWindowf, event);

		update_init();
	}

	// ADD

	if (tog_Add->Toggled())
	{
		Toggle_Group_Add.filter(mousePos, event);

		this->box_add_val->update(mousePosWindowf, event);
		this->box_add_pos->update(mousePosWindowf, event);

		update_add();
	}

	// DELETE

	if (tog_Delete->Toggled())
	{
		Toggle_Group_Del.filter(mousePos, event);

		this->box_del_pos->update(mousePosWindowf, event);

		update_del();
	}

	// UPDATE

	if (tog_Update->Toggled())
	{
		Toggle_Group_Upd.filter(mousePos, event);

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
}
