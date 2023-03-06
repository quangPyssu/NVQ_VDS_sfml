#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class DisplayNode

{
public:
	DisplayNode();              //Constructor

	//virtual ~DisplayNode();     // Destructor
	
	Text text;
	CircleShape shape;
	RectangleShape line;

};

