#include "Button.h"
#include <iostream>

Button::Button(float x, float y, float width, float height, string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor)
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
	this->text.setCharacterSize((int) this->height/2);
	this->text.setFillColor(activeColor);
	this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width/2.f,
		this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height/2.f);

	buttonState = BTN_IDLE;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->textColor = activeColor;

	shape.setFillColor(idleColor);
	shape.setOutlineColor(hoverColor);
	shape.setOutlineThickness(5);

	target = NULL;
	this->event = event;
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED)
	{
		Sleep(0);
		return 1;
	}
	return 0;
}

void Button::update(const Vector2f mousePos, Event* event)
{
	// update BTN_STATEs

	this->buttonState = BTN_IDLE;
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		if (event->type == Event::MouseButtonPressed && event->mouseButton.button == Mouse::Left) this->buttonState = BTN_PRESSED;
		else if (this->buttonState != BTN_PRESSED || event->mouseButton.button == Event::MouseButtonReleased) this->buttonState = BTN_HOVER;
	} else 
		if (this->buttonState != BTN_PRESSED || event->mouseButton.button == Event::MouseButtonReleased) this->buttonState = BTN_IDLE;

	switch (buttonState)
	{
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		text.setFillColor(activeColor);
		shape.setOutlineColor(hoverColor);
		break;

	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		text.setFillColor(idleColor);
		shape.setOutlineColor(activeColor);
		break;

	case BTN_PRESSED:
		shape.setFillColor(activeColor);
		text.setFillColor(hoverColor);
		shape.setOutlineColor(idleColor);
		break;
	}
}

void Button::render(RenderTarget* target)
{
	//draw shape
	target->draw(this->shape);
	target->draw(this->text);
}