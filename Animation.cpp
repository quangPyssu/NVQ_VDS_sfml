#include "Animation.h"

Animation::Animation(Event* event, LinkedList* l,RenderWindow* window)
{
	this->l = l;
	this->event = event;
	this->window = window;
}

Animation::~Animation()
{
}

void Animation::display_Del_Head()
{
}


