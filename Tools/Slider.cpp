#include "Slider.h"

Slider::Slider(Vector2f pos, Vector2f size, Color SlideColor, Color KnobColor,Color OutColor,string name,int start,int end)
{
    slider.setPosition(pos);
    slider.setSize(size);
    slider.setFillColor(SlideColor);

    slider.setOutlineThickness(2);
    slider.setOutlineColor(OutColor);


    knob.setRadius(size.y / 2); // Create the slider knob
    knob.setOrigin(Vector2f(knob.getRadius(), knob.getRadius()));
    knob.setFillColor(KnobColor);
    knob.setPosition(pos + Vector2f(knob.getRadius(), knob.getRadius()));

    font.loadFromFile("asset/fonts/ArialTh.ttf");

    text.setFont(font);
    text.setCharacterSize(knob.getRadius() + 10);
    text.setFillColor(KnobColor);
    text.setPosition(pos+Vector2f(10+size.x,-5));

    this->name = name;

    this->start = start;
    this->end = end;

    cur = start;
    between = end - start;

    maxPos = { pos.x+ knob.getRadius(),pos.x + size.x - knob.getRadius() };

}

void Slider::update(Event* event, Vector2f MousePos)
{
    if (event->type == Event::MouseButtonPressed)
    {
        // Check if the mouse is inside the knob
        if (slider.getGlobalBounds().contains(MousePos.x, MousePos.y)) dragging = true;
    }
    else if (event->type == Event::MouseButtonReleased) dragging = false;

    // Move the knob to the mouse position
    if (dragging) knob.setPosition(max(maxPos.x,min(maxPos.y,MousePos.x)), knob.getPosition().y);

    // Update the slider value based on the position of the knob
    // value between 0 and 1
    value = (knob.getPosition().x - maxPos.x) / (slider.getSize().x - knob.getRadius() * 2);
    value = max(0.f, std::min(1.f, value));
}

void Slider::render(RenderTarget* window)
{
    window->draw(slider);
    window->draw(knob);

    cur = start+(value*between);

    s = to_string(cur); 

    text.setString(name+s);
    window->draw(text);    
}
