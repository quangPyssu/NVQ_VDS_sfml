#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Button.h"

using namespace std;
using namespace sf;

enum box_states { IDLE = 0, ACTIVE = 1};

class TextBox
{    
       public:

        string input_text;
        string default_S,current_S;
        Text text;
        int data;

        //constructor

        TextBox(float x, float y, float width, float height, string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor);

        //destructor
        virtual~TextBox();

        //Function

        void update(const Vector2f mousePos,Event* event);

        void render(RenderTarget* target);

        void confirm(const string& s);
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

        // input accept?

        bool is_number(const string& s);
        Button* btn_cofirm;
};

