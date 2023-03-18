#include "Toggle_Group.h"
#include <iostream>

void Toggle_Group::filter(Vector2f mousePos,Event * event)
{
	for (int i = 0; i < n; i++) Toggle_Btn_Grp[i]->update(mousePos, event);

	for (int i = 0; i < n; i++)
		if (Toggle_Btn_Grp[i]->isPressed(mousePos, event))
		{
			update(i);
			break;
		}
}

void Toggle_Group::update(short id)
{
	for (short i = 0; i < n; i++) 
		Toggle_Btn_Grp[i]->disable();

	Toggle_Btn_Grp[id]->TurnOn();	
}

void Toggle_Group::clearAll()
{
	for (short i = 0; i < n; i++)
		Toggle_Btn_Grp[i]->disable();
}