#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

enum box_states { IDLE = 0, ACTIVE = 1};

class TextBox
{    
       public:

        string input_text;
        Text text;

        //constructor

        TextBox(float x, float y, float width, float height, string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor);

        //Function

        void update(const Vector2f mousePos,Event* event);

        void render(RenderTarget* target);
   private:
        short unsigned box_Stat;

        //attribute

        Font font;
        Color idleColor;
        Color hoverColor;
        Color activeColor;
        Color textColor;

        //event & clock
        RenderTarget* target;
        RectangleShape shape;

        Event* event;
        Clock clock;

        Time text_effect_time;
        bool show_cursor;
};

