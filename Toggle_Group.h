#pragma once

#include <SFML/Graphics.hpp>
#include "ToggleButton.h"

class Toggle_Group
{
public:
	ToggleButton* Toggle_Btn_Grp[10] = { nullptr };
	int n=0;

	bool stat[10] = { 0 };

	void update(short id);
};

