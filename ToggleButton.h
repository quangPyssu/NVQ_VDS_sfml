#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>

using namespace sf;
using namespace std;

enum button_tog { TOGGLE_OFF = 0, TOGGLE_ON = 1 ,Type_Toggle = 0, Type_Neighbor =1 };

class ToggleButton
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

    float height = 30;
    float width = 70;

    bool Toggle_stat=0;

public:


    // Button text

    Text text;

    //constructor

    ToggleButton(float x, float y, float width, float height, string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor,bool type);

    //Accessors
    const bool isPressed() const;
    Event* event;

    //Function

    void press();

    void disable();

    void update(const Vector2f mousePos, Event* event);

    void render(RenderTarget* target);
};

