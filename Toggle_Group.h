#pragma once

#include <SFML/Graphics.hpp>
#include "ToggleButton.h"

class Toggle_Group
{
public:
	ToggleButton* Toggle_Btn_Grp[10] = { nullptr };
	int n=0;

	Event* event; 

	bool stat[10] = { 0 };

	void filter(Vector2f mousePos,Event *event);

	void update(short id);

	void clearAll();
};

