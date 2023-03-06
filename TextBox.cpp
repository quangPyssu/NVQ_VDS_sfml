#include "TextBox.h"

TextBox::TextBox(float x, float y, float width, float height, string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor)
{
	shape.setSize(Vector2f(width, height));
	shape.setPosition(Vector2f(x, y));

	font.loadFromFile("asset/fonts/ArialTh.ttf");
	this->text.setFont(font);
	default_S = text;
	this->text.setString(text);
	this->text.setCharacterSize(30);
	this->text.setFillColor(Color::White);
	this->text.setPosition(this->shape.getPosition().x + 5,this->shape.getPosition().y + 10);

	this->btn_cofirm = new Button(500, 200, 100, 50, "CONFIRM", Color::White, Color::Green, Color::Color(246, 190, 0, 255), Color::Blue);

	box_Stat = IDLE;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->textColor = activeColor;

	shape.setFillColor(idleColor);
	shape.setOutlineColor(hoverColor);
	shape.setOutlineThickness(5);

	target = nullptr;
	event = nullptr;
	show_cursor = 0;
	data = 0;
}

TextBox::~TextBox()
{
	delete btn_cofirm;
}

void TextBox::update(const Vector2f mousePos,Event* event)
{
	// update Box_STATEs

	btn_cofirm->update(mousePos);
	data = 0;

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (shape.getGlobalBounds().contains(mousePos)) box_Stat = ACTIVE;
		else box_Stat = IDLE;
	}

	if (box_Stat == ACTIVE)
	{
		text.setString("");
		shape.setFillColor(activeColor);
		if (event->type == Event::TextEntered)
		{
			if (isprint(event->text.unicode) && input_text.size()<9)
				input_text += event->text.unicode;
		}

		else if (event->type == Event::KeyPressed) {
			if (event->key.code == Keyboard::BackSpace) {
				if (!input_text.empty())
					input_text.pop_back();
			}
		}
	}
	else
	{
		shape.setFillColor(Color::Green);
		text.setString(default_S);
	}
	
	if (btn_cofirm->isPressed()) confirm(input_text);
}

void TextBox::render(RenderTarget* target)
{
	text_effect_time += clock.restart();

	if (text_effect_time >= sf::seconds(0.5f))
	{
		show_cursor = !show_cursor;
		text_effect_time = sf::Time::Zero;
	}

	if (box_Stat == IDLE) show_cursor = 0;

	if (input_text != "" || box_Stat==ACTIVE)	text.setString(input_text + (show_cursor ? '_' : ' '));
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
	if (is_number(s))
	{
		data = stoi(s);
		input_text = "";
	}
}

