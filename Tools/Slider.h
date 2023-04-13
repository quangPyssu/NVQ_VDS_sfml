#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Slider
{
private:

        RectangleShape slider;

        CircleShape knob; 

        string s,name;

        Text text;

        Font font;

        bool dragging = false; // Track if the knob is being dragged

        int start,end;
        int cur,between;

        Vector2f maxPos;
public:
    Slider(Vector2f pos,Vector2f size,Color SlideColor, Color KnobColor,Color OutColor,string name,int start,int end);

    float value = 1;

    void update(Event* event, Vector2f MousePos);

    void render(RenderTarget* window);

};

