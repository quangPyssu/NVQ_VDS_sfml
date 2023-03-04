#include "Button.h"

Button::Button(float x, float y, float width, float height, string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor)
{
	shape.setSize(Vector2f(width, height));
	shape.setPosition(Vector2f(x, y));

	font.loadFromFile("asset/fonts/ArialTh.ttf");
	this->text.setFont(font);
	this->text.setString(text);
	this->text.setCharacterSize(24);
	this->text.setFillColor(Color::White);
	this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width/2.f,
		this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height/2.f);

	buttonState = BTN_IDLE;
	shape.setFillColor(idleColor);

	target = NULL;
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED) return 1;
	return 0;
}

void Button::update(const Vector2f mousePos)
{
	// update BTN_STATEs

	this->buttonState = BTN_IDLE;
	int i = 1;
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;
		if (Mouse::isButtonPressed(Mouse::Left))
			this->buttonState = BTN_PRESSED;
	}

	switch (buttonState)
	{
	case BTN_IDLE:
		shape.setFillColor(Color::Blue);
		text.setFillColor(Color::White);
		break;

	case BTN_HOVER:
		shape.setFillColor(Color::Yellow);
		text.setFillColor(Color::Black);
		break;

	case BTN_PRESSED:
		shape.setFillColor(Color::Red);
		text.setFillColor(Color::White);
		break;
	}
}

void Button::render(RenderTarget* target)
{
	//draw shape
	target->draw(this->shape);
	target->draw(this->text);
}