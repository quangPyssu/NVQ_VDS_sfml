#pragma once

#include <SFML/Graphics.hpp>
#include "ToggleButton.h"
#include "TextBox.h"

class Toggle_Group
{
public:
	ToggleButton* Toggle_Btn_Grp[5] = { nullptr };
	TextBox* Box_text_Grp[5] = { nullptr };
	ToggleButton* tog_Grp_Head=nullptr;

	short isOn=0;

	int n=0;

	bool stat[10] = { 0 };

	void filter(Vector2f mousePos,Event *event);

	void update(short id);

	void render(RenderTarget* window);

	void clearAll();

	bool checkEmpty();
};

