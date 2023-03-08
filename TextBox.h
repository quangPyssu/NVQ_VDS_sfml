#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Button.h"

using namespace std;
using namespace sf;

enum box_states { IDLE = 0, ACTIVE = 1, nothing = -1000000000};

class TextBox
{    
       public:

        string input_text;
        string default_S,current_S;
        Text text;
        int data=nothing;
        
        short unsigned box_Stat;

        //constructor

        TextBox(float x, float y, float width, float height, string text, Color textColor, Color idleColor, Color hoverColor, Color activeColor,int btn_x,int btn_y);

        //destructor
        virtual~TextBox();

        //Function

        void update(const Vector2f mousePos,Event* event);

        void render(RenderTarget* target);

        void confirm(const string& s);

        // position &size
        int pos_x, pos_y;
        int size_x, size_y;
   private:
        

        //attribute

        Font font;
        Color idleColor;
        Color hoverColor;
        Color activeColor;
        Color textColor;
        float height = 30;
        float width = 100;

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

