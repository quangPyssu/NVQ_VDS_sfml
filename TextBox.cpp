#include "TextBox.h"

TextBox::TextBox(float x, float y, float width, float height,float thick, string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor,int btn_x,int btn_y,int size, Color borderColor)
// btn_x and btn_y is for displacement of btn compare to TextBox
{
	this->height = height ? height : this->height;
	this->width = width ? width : this->width;

	shape.setSize(Vector2f(this->width, this->height));
	shape.setPosition(Vector2f(x, y));

	size_x = (int) this->width; size_y = (int) this->height;
	pos_x = (int) x; pos_y = (int) y;

	font.loadFromFile("asset/fonts/ArialTh.ttf");
	this->text.setFont(font);
	default_S = text;
	this->text.setString(text);
	this->text.setCharacterSize((int) this->height/2);
	this->text.setFillColor(Color::White);
	this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f);

	this->btn_cofirm = new Button(x+btn_x, y+btn_y, 0, 0, "CONFIRM", Color::Black, Color::White, Color::Color(90, 90, 90, 155), Color::Color(90, 90, 90, 255), Color::Black);

	box_Stat = IDLE;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->textColor = activeColor;

	shape.setFillColor(idleColor);
	shape.setOutlineColor(borderColor);
	shape.setOutlineThickness(thick);

	target = nullptr;
	event = nullptr;
	data = 0;
	this->size = size;
}

TextBox::~TextBox()
{
	delete btn_cofirm;
}

void TextBox::update(const Vector2f mousePos,Event* event)
{
	// update Box_STATEs

	btn_cofirm->update(mousePos,event);
	data = 0;

	/*if (this->shape.getGlobalBounds().contains(mousePos))
	{
		if (event->type == Event::MouseButtonPressed && event->mouseButton.button == Mouse::Left)
		{
			if (box_Stat == ACTIVE) box_Stat = IDLE; else box_Stat = ACTIVE;
		}
		else if (!isToggle || event->mouseButton.button == Event::MouseButtonReleased) isHover = 1;
	}
	else
	{
		if (!isToggle || event->mouseButton.button == Event::MouseButtonReleased) isHover = 0;

		if (event->type == Event::MouseButtonPressed && event->mouseButton.button == Mouse::Left) box_Stat = IDLE;
	}*/

	if (event->type == Event::MouseButtonPressed && event->mouseButton.button == Mouse::Left)
	{
		isHover = 0;
		if (this->shape.getGlobalBounds().contains(mousePos))box_Stat = ACTIVE;
		else box_Stat = IDLE;
	}
	else if (this->shape.getGlobalBounds().contains(mousePos)) isHover = 1; else isHover = 0;

	//if (tog_ghost!= nullptr && tog_ghost->Toggled()) isToggle = true; else isToggle = false;

	if (box_Stat == ACTIVE || isToggle)
	{
		shape.setFillColor(activeColor);
		text.setFillColor(idleColor);
		
		if (box_Stat == ACTIVE)
		{
			if (event->type == Event::TextEntered)
			{
				if (isprint(event->text.unicode) && input_text.size() < this->size)
					input_text += event->text.unicode;
			}
			else
				if (event->type == Event::KeyPressed)
				{
					if (event->key.code == Keyboard::BackSpace)
					{
						if (!input_text.empty())
							input_text.pop_back();
					}
				}
		}
	}
	else
	{
		shape.setFillColor(idleColor);
		text.setFillColor(activeColor);
		text.setString(default_S);
		if (isHover) shape.setFillColor(hoverColor);
	}

	
	if (btn_cofirm->isPressed() || (event->type == Event::KeyPressed && event->key.code == Keyboard::Enter)) confirm(input_text),cout << "data " << data << endl; else data = nothing;
}

void TextBox::render(RenderTarget* target)
{
	if (input_text.size() > 9)
	{
		output_text = "";
		for (int i = 1; i <= 9; i++)
			output_text = input_text[input_text.size() - i] + output_text;
		output_text = "..." + output_text;
	}
	else output_text = input_text;

	if (input_text != "" || box_Stat == ACTIVE)
	{
		if (box_Stat == ACTIVE)
		{
			static sf::Time text_effect_time;
			static bool show_cursor;

			text_effect_time += clock.restart();

			if (text_effect_time >= sf::seconds(0.5f))
			{
				show_cursor = !show_cursor;
				text_effect_time = sf::Time::Zero;
			}
			text.setString(output_text + (show_cursor ? '_' : ' '));
		} 
		else text.setString(output_text);
	}
	else text.setString(default_S);

	target->draw(shape);
	target->draw(text);
	btn_cofirm->render(target);
}

bool TextBox::is_number(const string& s)
{
	return !s.empty() && find_if(s.begin(),	s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

void TextBox::confirm(const string& s)
{
	data = nothing;
	if (is_number(s))
	{
		data = stoi(s);
		
		input_text = "";
	}
}

