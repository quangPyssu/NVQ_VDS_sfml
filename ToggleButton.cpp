#include "ToggleButton.h"
#include <iostream>

ToggleButton::ToggleButton(float x, float y, float width, float height, string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor,bool type)
{
	this->height = height ? height : this->height;
	this->width = width ? width : this->width;

	shape.setSize(Vector2f(this->width, this->height));
	shape.setPosition(Vector2f(x, y));

	font.loadFromFile("asset/fonts/ArialTh.ttf");
	this->text.setFont(font);
	this->text.setString(text);
	this->text.setCharacterSize((int)this->height / 2);
	this->text.setFillColor(activeColor);
	this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f);

	this->buttonState = TOGGLE_OFF;

	this->idleColor = idleColor;
	this->activeColor = activeColor;
	this->textColor = textColor;
	this->hoverColor = hoverColor;

	shape.setFillColor(idleColor);
	shape.setOutlineColor(hoverColor);
	shape.setOutlineThickness(5);

	target = NULL;
	this->event = event;
}

void ToggleButton::disable()
{
	buttonState = TOGGLE_OFF;
	shape.setFillColor(idleColor);
	text.setFillColor(activeColor);
	shape.setOutlineColor(hoverColor);
	Toggle_stat = 0;
}

void ToggleButton::press()
{
	if (Type_Toggle)  //self dependent
	{
		Toggle_stat = (Toggle_stat + 1) % 2;
		if (Toggle_stat) this->buttonState = TOGGLE_ON;
		else this->buttonState = TOGGLE_OFF;
	}
	else this->buttonState = TOGGLE_ON; // neighbor dependent
}

const bool ToggleButton::isPressed() const
{
	if (this->buttonState == TOGGLE_ON)	return 1;
	return 0;
}

void ToggleButton::update(const Vector2f mousePos, Event* event)
{
	// update BTN_STATEs

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		if (event->type == Event::MouseButtonPressed && event->mouseButton.button == Mouse::Left)
			press();
	}

	switch (buttonState)
	{
	case TOGGLE_OFF:
		shape.setFillColor(idleColor);
		text.setFillColor(activeColor);
		shape.setOutlineColor(hoverColor);
		break;

	case TOGGLE_ON:
		shape.setFillColor(activeColor);
		text.setFillColor(hoverColor);
		shape.setOutlineColor(idleColor);
		break;
	}
}

void ToggleButton::render(RenderTarget* target)
{
	//draw shape
	target->draw(this->shape);
	target->draw(this->text);
}