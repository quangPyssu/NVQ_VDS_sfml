#include "Stack_Menu.h"
#include <iostream>

Stack_Menu::Stack_Menu(Event* event, RenderWindow* window)
{
	// make btn;
	this->tog_Initialize = new ToggleButton(20, 20, 0, 0, 2, "Initialize", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), true, Color::Black);
	this->tog_Add = new ToggleButton(20, tog_Initialize->pos_y + tog_Initialize->size_y + 10, 0, 0, 2, "Push", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), true, Color::Black);
	this->tog_Delete = new ToggleButton(20, tog_Add->pos_y + tog_Add->size_y + 10, 0, 0, 2, "Pop", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), true, Color::Black);
	this->tog_Search = new ToggleButton(20, tog_Delete->pos_y + tog_Delete->size_y + 10, 0, 0, 2, "Peek", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), true, Color::Black);
	this->btn_back = new Button(20, tog_Search->pos_y + tog_Search->size_y + 10, 0, 0, "Back", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Color::Black);

	Toggle_Group_Stack.Toggle_Btn_Grp[0] = tog_Initialize;	Toggle_Group_Stack.Toggle_Btn_Grp[1] = tog_Add;	Toggle_Group_Stack.Toggle_Btn_Grp[2] = tog_Delete;
	Toggle_Group_Stack.Toggle_Btn_Grp[3] = tog_Search;	

	Toggle_Group_Stack.n = 4;

	shape.setPosition(Vector2f(0, 0)); shape.setFillColor(BGColor[theme] + Color::Color(25, 25, 25));
	shape.setSize(Vector2f(tog_Initialize->pos_x + tog_Initialize->size_x + 10, btn_back->pos_y + btn_back->size_y + 10));

	// make TextBox&btn for INITIALIZE;
	{
		this->tog_init_empty = new ToggleButton(tog_Initialize->pos_x + tog_Initialize->size_x + 20, tog_Initialize->pos_y, 0, 0, 2, "Empty", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), false, Color::Black);
		this->tog_init_random = new ToggleButton(tog_init_empty->pos_x + tog_init_empty->size_x + 5, tog_Initialize->pos_y, 0, 0, 2, "Random", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), false, Color::Black);
		this->tog_init_fixed = new ToggleButton(tog_init_random->pos_x + tog_init_random->size_x + 5, tog_Initialize->pos_y, 150, 0, 2, "", Color::White, Color::Black, Color::Green, Color::Blue, false, Color::Black);
		this->tog_init_read = new ToggleButton(tog_init_fixed->pos_x + tog_init_fixed->size_x + 5, tog_Initialize->pos_y, 150, 0, 2, "", Color::White, Color::Black, Color::Green, Color::Blue, false, Color::Black);
		this->tog_init_load = new ToggleButton(tog_init_read->pos_x + tog_init_read->size_x + 5, tog_Initialize->pos_y, 150, 0, 2, "Load", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), false, Color::Black);

		this->box_init_read = new TextBox(tog_init_read->pos_x, tog_init_read->pos_y, tog_init_read->size_x, tog_init_read->size_y, 2, "Input Value", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), tog_init_read->size_x * 2 + 20, 0, 50, Color::Black);
		this->box_init_fixed = new TextBox(tog_init_fixed->pos_x, tog_init_fixed->pos_y, tog_init_fixed->size_x, tog_init_fixed->size_y, 2, "Input Size", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), tog_init_read->size_x * 3 + 20 + 5, 0, 9, Color::Black);

		Toggle_Group_Init.Toggle_Btn_Grp[0] = tog_init_empty;	Toggle_Group_Init.Toggle_Btn_Grp[1] = tog_init_random;	Toggle_Group_Init.Toggle_Btn_Grp[2] = tog_init_fixed;
		Toggle_Group_Init.Toggle_Btn_Grp[3] = tog_init_read;	Toggle_Group_Init.Toggle_Btn_Grp[4] = tog_init_load;
		Toggle_Group_Init.n = 5;
	}

	// make TextBox&btn for ADD;
	{
		this->box_add_val = new TextBox(tog_Add->pos_x + tog_Add->size_x + 20, tog_Add->pos_y, 0, 0, 2, "Input Value", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), 150 + 20, 0, 9, Color::Black);
	}

	// make TextBox&btn for DEL;
	{
		this->btn_del_confirm = new Button(tog_Delete->pos_x + tog_Delete->size_x + 20, tog_Delete->pos_y, 0, 0, "CONFIRM", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Color::Black);
	}

	// make TextBox&btn for SEARCH;
	{
		this->btn_ser_confirm = new Button(tog_Search->pos_x + tog_Search->size_x + 20, tog_Search->pos_y, 0, 0, "CONFIRM", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Color::Black);
	}

	// make btn for Time travel;

	{
		this->tog_speed = new ToggleButton(1250, 20, 0, 0, 2, "Step by Step", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), true, Color::Black);
		this->btn_change_size = new Button(1250 + tog_speed->size_x + 5, tog_speed->pos_y, 0, 0, "Size Change", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Color::Black);
		this->tog_change_color = new ToggleButton(btn_change_size->pos_x + btn_change_size->size_x + 5, tog_speed->pos_y, 0, 0, 2, "Light Mode", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), true, Color::Black);

		this->btn_step_prev = new Button(window->getSize().x / 2 - tog_speed->size_x * 3 / 2 - 10, window->getSize().y - tog_speed->size_y * 2 - 10, 0, 0, "Step Back", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Color::Black);
		this->tog_play = new ToggleButton(btn_step_prev->pos_x + btn_step_prev->size_x + 5, btn_step_prev->pos_y, 0, 0, 2, "Play", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), true, Color::Black);
		this->btn_step_next = new Button(tog_play->pos_x + tog_play->size_x + 5, btn_step_prev->pos_y, 0, 0, "Step Forward", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Color::Black);

		this->tog_speed->s2 = "Instant speed";
		this->tog_change_color->s2 = "Dark Mode";
	}

	// Slider speed;
	{
		Slide_Render_Speed = new Slider({ (float)tog_change_color->pos_x + tog_change_color->size_x + 10, (float)tog_change_color->pos_y + tog_change_color->size_y / 2 - 5 }, { 100,20 }, Color::Black, Color::Color(200, 120, 10), Color::Color(139, 64, 0), "Render Speed: x", 1, 5);
	}

	// Back display
	sprite.setScale(Vector2f(1920.f / tet.getSize().x, 1080.f / tet.getSize().y));

	// Instruction
	{
		font.loadFromFile("asset/fonts/ArialTh.ttf");
		text.setFont(font);
		text.setPosition(Vector2f(btn_back->pos_x + btn_back->size_x, btn_back->pos_y + btn_back->size_y + 50));
		text.setFillColor(Color::Color(255, 50, 50));
		text.setOutlineColor(Color::Color(170, 51, 106));
		text.setOutlineThickness(0.2);
		text.setCharacterSize(30);

		Instruction[0] = "Make an Empty Stack";
		Instruction[1] = "Make an Stack with random size and values";
		Instruction[2] = "Make an Stack with inputed size and values";
		Instruction[3] = "Make an Stack with inputed values (for creating a Stack with size 1 please use Push function)";
		Instruction[4] = "Make an Stack with size and value imported from data file";

		Instruction[5] = "Add a Node to the Head of the Stack";

		Instruction[6] = "Delete the Node at the Head of the Stack";

		Instruction[7] = "Get the value of the Head of the stack and highlight it";

		Instruction[8] = "";
	}

	//set default
	this->window = window;
	stat = off;

	this->event = event;

	l.type = isRound;

	anime = new Animation_Stack(event, &l, window);

	srand(time(NULL));
}

Stack_Menu::~Stack_Menu()
{
	//Button
	delete tog_Initialize; delete tog_Add;
	delete tog_Delete; 
	delete tog_Search; delete btn_back;

	delete tog_init_empty; delete tog_init_fixed;
	delete tog_init_load; delete tog_init_random;
	delete tog_init_read;
	
	delete btn_del_confirm;

	delete btn_ser_confirm;

	delete btn_step_next; delete btn_step_prev;
	delete tog_speed; delete tog_play;

	delete btn_change_size; delete tog_change_color;

	//Box

	delete box_init_fixed; delete box_init_read;

	delete box_add_val; 

	//Slider

	delete Slide_Render_Speed;

	// Linked list

	l.delAll();
}

void Stack_Menu::TimeTravel()
{
	//Render();
	//anime->drawOneStep(anime->curStep);
}

void Stack_Menu::stop(float i)
{
	float total_time = 0.0f;

	while (total_time < i) {
		float elapsed_time = clock.restart().asSeconds();
		total_time += elapsed_time;
	}
}

void Stack_Menu::drawTrans(int start, int end, short CodeStatus)
{
	isDrawing = DrawAnimation;
	for (int j = 0; j < frame; j++)
	{
		Render();
		anime->drawSmoothTransition(start, end, j * frameStep, CodeStatus); 
		stop(FrameTime);
	}
	isDrawing = DrawStep;
}

void Stack_Menu::drawFrom(int Current, bool hasHead)
{
	cout << "Step " << anime->step << endl;
	isDrawing = DrawStep;

	if (!tog_speed->Toggled())
	{
		FrameTime = StepTime / frame;
		for (int i = Current; i < anime->step; i++)
		{
			
			short CodeStatus = 0;
			if (!i && !hasHead) CodeStatus = anime->Appear; else
				if (i == anime->step - 1)  CodeStatus = anime->Disappear;

			anime->curStep = i;

			if (i)
			{
				Render();
				window->display();
				stop(StepTime);
			}

			int start = i, end = i + 1;

			if (i == anime->step - 1) end = i;

			drawTrans(start, end, CodeStatus);
		}
	}

	anime->curStep = anime->step;

	isDrawing = DrawNormal;
}

void Stack_Menu::Render()
{
	window->clear(BGColor[theme]);
	window->draw(shape);
	window->draw(text);

	this->tog_Initialize->render(window);
	this->tog_Add->render(window);
	this->tog_Delete->render(window);
	this->tog_Search->render(window);
	this->btn_back->render(window);

	this->tog_speed->render(window);

	this->Slide_Render_Speed->render(window);

	if (anime->step)
	{
		this->btn_step_prev->render(window);
		this->btn_step_next->render(window);

		if (anime->step != anime->curStep) this->tog_play->render(window);
	}

	this->btn_change_size->render(window);
	this->tog_change_color->render(window);

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
		this->box_add_val->render(window);
	}

	if (tog_Delete->Toggled())
	{
		this->btn_del_confirm->render(window);
	}

	if (tog_Search->Toggled())
	{
		this->btn_ser_confirm->render(window);
	}

	if (isDrawing == DrawNormal) l.render(window); else	if (isDrawing == DrawStep) anime->drawOneStep(anime->curStep), anime->drawFakeCode(anime->curStep, 0);
}

void Stack_Menu::update_init()
{
	if (tog_init_empty->Toggled()) init_stat = init_empty, curInsId = 0;
	if (tog_init_random->Toggled()) init_stat = init_random, curInsId = 1;
	if (tog_init_fixed->Toggled()) init_stat = init_fixed, curInsId = 2;
	if (tog_init_read->Toggled()) init_stat = init_read, curInsId = 3;
	if (tog_init_load->Toggled()) init_stat = init_load, curInsId = 4;

	if (box_init_fixed->data != nothing && init_data_size == nothing) init_data_size = box_init_fixed->data, box_init_fixed->data = nothing;

	if (box_init_fixed->btn_cofirm->isPressed())
	{
		tog_Initialize->disable();
		switch (this->init_stat)
		{
		case init_empty:
			l.delAll();
			anime->clearAll();
			isDrawing = DrawNormal;

			break;

		case init_random:
			l.delAll();
			anime->clearAll();
			isDrawing = DrawNormal;

			n = 3 + (rand() % 3);
			for (int i = 0; i < n; i++) l.addHead((New(rand() % 100)));
			break;

		case init_fixed:
			if (init_data_size != nothing)
			{
				if (init_data_size <= 10)
				{
					n = init_data_size;
					l.delAll();
					anime->clearAll();
					isDrawing = DrawNormal;

					for (int i = 0; i < n; i++) l.addHead((New(rand() % 100)));
				}
				init_data_size = nothing;
			}

			break;

		case init_read:
			init_get.StringFilter(box_init_read->input_text);
			l.delAll();
			anime->clearAll();
			isDrawing = DrawNormal;

			for (int i : init_get.init_data) l.addTail(New(i));

			break;

		case init_load:
			string s = "data/data.inp";
			ifstream Fin(s);
			if (Fin.is_open())
			{
				l.delAll();
				anime->clearAll();
				isDrawing = DrawNormal;

				int n; Fin >> n;
				for (int i = 0; i < n; i++)
				{
					int j; Fin >> j;
					l.addTail(New(j));
				}
				Fin.close();
			}
			else cout << "There was no data!!" << endl;

			break;

		}

		l.change(sizeId, theme);

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

void Stack_Menu::update_add()
{
	curInsId = 5;
	if (box_add_val->data != nothing && add_data_val == nothing) add_data_val = box_add_val->data, box_add_val->data = nothing;

	if (add_data_val != nothing && l.Size < 10 && box_add_val->btn_cofirm->isPressed())
	{
		tog_Add->disable();

		anime->clearAll();

		if (l.Size)
		{
			anime->Add_pos(0, add_data_val);
			drawFrom(0, 0);
		}

		l.addKth(New(add_data_val), 0);

		l.change(sizeId, theme);

		// Delete later
		{
			Node* tmp = l.Head;
			while (tmp != nullptr)
			{
				cout << tmp->data << " ";
				tmp = tmp->Next;
			}cout << endl;
		}

		add_data_val = nothing;
		
	}
	else if (l.Size == 10) add_data_val = nothing;
}

void Stack_Menu::update_del()
{
	curInsId = 6;
	if (btn_del_confirm->isPressed())
	{
		tog_Delete->disable();

		anime->clearAll();

		if (l.Size)
		{
			anime->Del_pos(0);
			drawFrom(0, 0);
		}

		l.delKth(0);

		l.change(sizeId, theme);

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

void Stack_Menu::update_search()
{
	curInsId = 7;

	if (btn_ser_confirm->isPressed())
	{
		tog_Search->disable();

		if (l.Size)
		{
			anime->clearAll();

			anime->Ser_pos(0);

			drawFrom(0, 0);
		}
	}
}

void Stack_Menu::update(const Vector2f mousePos)
{
	this->mousePosWindowf = mousePos;

	this->btn_back->update(mousePosWindowf, event);

	if (this->btn_back->isPressed())
	{
		//Sleep(10)
		stat = off;
		Toggle_Group_Stack.clearAll();

		l.delAll();

		anime->clearAll();

		isDrawing = DrawNormal;
	}
	else Toggle_Group_Stack.filter(mousePos, event);

	Slide_Render_Speed->update(event, mousePos);
	StepTime = (1 - Slide_Render_Speed->value) * baseTime;

	//Time travel

	this->tog_speed->update(mousePosWindowf, event);
	this->btn_change_size->update(mousePosWindowf, event);
	this->tog_change_color->update(mousePosWindowf, event);

	if (theme) tog_change_color->TurnOn(); else tog_change_color->disable();

	if (btn_change_size->isPressed()) { sizeId = (sizeId + 1) % 3; l.change(sizeId, theme); }
	if (tog_change_color->isPressedBoth(mousePosWindowf, event)) { theme = (theme + 1) % 2; l.change(sizeId, theme); }

	shape.setFillColor(BGColor[theme] + Color::Color(25, 25, 25));

	if (anime->step)
	{
		this->btn_step_prev->update(mousePosWindowf, event);
		this->btn_step_next->update(mousePosWindowf, event);

		if (this->btn_step_prev->isPressed() && anime->curStep > 0)
		{
			if (anime->curStep == anime->step) drawTrans(anime->step - 1, anime->step - 1, anime->Appear);
			anime->curStep = anime->curStep - 1;
		}
		else if (this->btn_step_next->isPressed() && anime->curStep < anime->step)
		{
			anime->curStep = anime->curStep + 1;
			if (anime->curStep == anime->step) drawTrans(anime->step - 1, anime->step - 1, anime->Disappear);
		}

		if (anime->curStep != anime->step)
		{
			isDrawing = 1;
			this->tog_play->update(mousePosWindowf, event);
			if (tog_play->Toggled())
			{
				drawFrom(anime->curStep, 1);
				this->tog_play->disable();
			}
		}
		else isDrawing = 0;
	}

	// INITIALIZE

	if (tog_Initialize->Toggled())
	{
		Toggle_Group_Init.filter(mousePos, event);

		this->box_init_read->update(mousePosWindowf, event);
		this->box_init_fixed->update(mousePosWindowf, event);

		update_init();
	}
	else Toggle_Group_Init.clearAll();

	// ADD

	if (tog_Add->Toggled())
	{
		this->box_add_val->update(mousePosWindowf, event);

		update_add();
	}

	// DELETE

	if (tog_Delete->Toggled())
	{
		this->btn_del_confirm->update(mousePosWindowf, event);

		update_del();
	}

	// SEARCH

	if (tog_Search->Toggled())
	{
		this->btn_ser_confirm->update(mousePosWindowf, event);

		update_search();
	}

	if (Toggle_Group_Stack.checkEmpty()) curInsId = 8;

	loadInstruction();
}

void Stack_Menu::loadInstruction()
{
	text.setString(Instruction[curInsId]);
}
