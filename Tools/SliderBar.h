#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class SliderBar
{
	public:
        SliderBar(Vector2f pos, float width, float height, float min_value, float max_value, float start_value);

        void render(RenderWindow* window);

        void update(Vector2f mouse_pos);

        float getValue() const;

private:
    Vector2f pos;
    float width;
    float height;
    float min_value;
    float max_value;
    float value;

    RectangleShape bar;
    RectangleShape slider;
    Font font;
    Text text;
};

