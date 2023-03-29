#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>

using namespace sf;
using namespace std;

enum button_tog { TOGGLE_OFF = 0, TOGGLE_ON = 1 , HOVER = 2 ,PRESSING = 3 };

class ToggleButton
{
private:
    short unsigned buttonState;
    short unsigned isHover=0;

    bool canToggle = 1;

    //attribute

    Font font;
    Color idleColor;
    Color hoverColor;
    Color activeColor;
    Color textColor;
    Color borderColor;
    Texture texture;
    RenderTarget* target;
    RectangleShape shape;

    float height = 50;
    float width = 120;

    bool Toggle_stat=0;

public:


    // Button text

    Text text;

    string s = "";
    string s2 = "";

    //constructor

    ToggleButton(float x, float y, float width, float height, float thick,string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor,bool canToggle,Color borderColor);

    //Accessors
    const bool isPressed(Vector2f mousePos,Event* event) const;
    const bool Toggled() const;

    Event* event;

    //Function

    void press();

    void TurnOn();

    void disable();

    void update(const Vector2f mousePos, Event* event);

    void render(RenderTarget* target);

    // neighborhood

    short id=0;

    // position &size
    int pos_x, pos_y;
    int size_x, size_y;
};

