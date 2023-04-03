#include "SliderBar.h"

SliderBar::SliderBar(Vector2f pos, float width, float height, float min_value, float max_value, float start_value)
{
    this->pos = pos;
    this->width = width;
    this->height = height;
    this->min_value = min_value;
    this->max_value = max_value;
    this->value = start_value;

    bar.setSize(Vector2f(width, height));
    bar.setFillColor(Color::White);
    bar.setPosition(pos);

    slider.setSize(Vector2f(height, height));
    slider.setFillColor(Color::Red);
    slider.setPosition(pos.x + (width - height) * (start_value - min_value) / (max_value - min_value), pos.y);

    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setString(std::to_string(start_value));
    text.setCharacterSize(width/2);
    text.setFillColor(Color::Black);
    text.setPosition(pos.x + width + 10, pos.y + height / 2 - 10);
}

void SliderBar::render(RenderWindow* window)
{
    window->draw(bar);
    window->draw(slider);
    window->draw(text);
}

void SliderBar::update(Vector2f mouse_pos)
{
    if (slider.getGlobalBounds().contains(static_cast<Vector2f>(mouse_pos)))
    {
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            float x = (float)mouse_pos.x - height / 2;
            if (x < pos.x) x = pos.x; else
                if (x > pos.x + width - height) x = pos.x + width - height;

            slider.setPosition(x, pos.y);
            value = min_value + (max_value - min_value) * (x - pos.x) / (width - height);
            text.setString(std::to_string(value));
        }
    }
}

float SliderBar::getValue() const
{
    return value;
}