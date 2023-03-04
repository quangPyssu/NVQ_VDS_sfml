#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

enum button_states { BTN_IDLE = 0, BTN_HOVER = 1, BTN_PRESSED = 2 };

class Button
{
private:
    short unsigned buttonState;

    //attribute

    Font font;
    Color idleColor;
    Color hoverColor;
    Color activeColor;
    Color textColor;
    Texture texture;
    RenderTarget* target;
    RectangleShape shape;

public:


    // Button text

    Text text;

    //constructor

    Button(float x, float y, float width, float height, string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor);

    //Accessors
    const bool isPressed() const;

    //Function

    void update(const Vector2f mousePos);

    void render(RenderTarget* target);
};

