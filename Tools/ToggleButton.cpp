#include "ToggleButton.h"
#include <iostream>

ToggleButton::ToggleButton(float x, float y, float width, float height, float thick, string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor,bool canToggle,Color borderColor)
{
	this->height = height ? height : this->height;
	this->width = width ? width : this->width;

	shape.setSize(Vector2f(this->width, this->height));
	shape.setPosition(Vector2f(x, y));

	size_x = this->width; size_y = this->height;
	pos_x = x; pos_y = y;

	font.loadFromFile("asset/fonts/ArialTh.ttf");
	this->text.setFont(font);
	this->text.setString(text);
	this->s = text;
	this->s2 = text;
	this->text.setCharacterSize((int)this->height / 2);
	this->text.setFillColor(activeColor);
	this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f);

	this->buttonState = TOGGLE_OFF;
	this->canToggle = canToggle;

	this->idleColor = idleColor;
	this->activeColor = activeColor;
	this->textColor = textColor;
	this->hoverColor = hoverColor;
	this->borderColor = borderColor;

	shape.setFillColor(idleColor);
	shape.setOutlineColor(borderColor);
	shape.setOutlineThickness(thick);

	target = NULL;
	this->event = event;
}

void ToggleButton::disable()
{
	this->buttonState = TOGGLE_OFF;
	shape.setFillColor(idleColor);
	text.setFillColor(activeColor);
	Toggle_stat = 0;
}

void ToggleButton::TurnOn()
{
	this->buttonState = TOGGLE_ON;
	shape.setFillColor(activeColor);
	text.setFillColor(idleColor);
	Toggle_stat = 1;
}

void ToggleButton::press()
{
	Toggle_stat = (Toggle_stat + 1) % 2;
	if (Toggle_stat) this->buttonState = TOGGLE_ON;
	else this->buttonState = TOGGLE_OFF;
}


const bool ToggleButton::Toggled() const
{
	if (this->buttonState == TOGGLE_ON) return 1; 
	return 0;
}

const bool ToggleButton::isPressed(Vector2f mousePos,Event* event) const
{
	if (this->shape.getGlobalBounds().contains(mousePos) && buttonState== TOGGLE_ON)
		if (event->type == Event::MouseButtonPressed && event->mouseButton.button == Mouse::Left)
		{
			//Sleep(5);
			return 1;
		}
	return 0;
}

const bool ToggleButton::isPressedBoth(Vector2f mousePos, Event* event) const
{
	if (this->shape.getGlobalBounds().contains(mousePos))
		if (event->type == Event::MouseButtonPressed && event->mouseButton.button == Mouse::Left)
		{
			//Sleep(5);
			return 1;
		}
	return 0;
}

void ToggleButton::update(const Vector2f mousePos, Event* event)
{
	// update BTN_STATEs

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		if (event->type == Event::MouseButtonPressed && event->mouseButton.button == Mouse::Left)
		{
			if (canToggle) press();
			else TurnOn();
		}
		else if (this->buttonState != TOGGLE_ON || event->mouseButton.button == Event::MouseButtonReleased) isHover=1;
	}
	else if (this->buttonState != TOGGLE_ON || event->mouseButton.button == Event::MouseButtonReleased) isHover = 0;

	switch (buttonState)
	{
	case TOGGLE_OFF:
		if (s2 != "") text.setString(s);
		shape.setFillColor(idleColor);
		text.setFillColor(activeColor);
		if (isHover) shape.setFillColor(hoverColor),text.setFillColor(idleColor);
		break;

	case TOGGLE_ON:
		if (s2!="") text.setString(s2);
		shape.setFillColor(activeColor);
		text.setFillColor(idleColor); 
		break;
	}
}

void ToggleButton::render(RenderTarget* target)
{
	//draw shape
	this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f);

	target->draw(this->shape);
	target->draw(this->text);
}