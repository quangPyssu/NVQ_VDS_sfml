#include "Toggle_Group.h"
#include <iostream>

void Toggle_Group::filter(Vector2f mousePos,Event * event)
{
	if (tog_Grp_Head != nullptr)
	{
		tog_Grp_Head->update(mousePos, event);

		if (tog_Grp_Head->Toggled())
		{
			for (int i = 0; i < n; i++) if (Toggle_Btn_Grp[i]->Toggled())
			{
				Sleep(10);
				clearAll(); isOn = i;

				if (Box_text_Grp[i] != nullptr) Box_text_Grp[i]->box_Stat = ACTIVE;

				tog_Grp_Head->disable();
				tog_Grp_Head->text.setString(Toggle_Btn_Grp[i]->s);
				return;
			}

			isOn = n;

			tog_Grp_Head->text.setString(tog_Grp_Head->s);

			for (int i = 0; i < n; i++) Toggle_Btn_Grp[i]->update(mousePos, event);

			for (int i = 0; i < n; i++)
				if (Toggle_Btn_Grp[i]->isPressed(mousePos, event))
				{
					update(i);
					break;
				}
		}
	}
	else
	{
		for (int i = 0; i < n; i++) Toggle_Btn_Grp[i]->update(mousePos, event);

		for (int i = 0; i < n; i++)
			if (Toggle_Btn_Grp[i]->isPressed(mousePos, event))
			{
				update(i);
				break;
			}
	}
}

void Toggle_Group::update(short id)
{
	for (short i = 0; i < n; i++) 
		Toggle_Btn_Grp[i]->disable();

	Toggle_Btn_Grp[id]->TurnOn();	
}

void Toggle_Group::render(RenderTarget* window)
{
	if (tog_Grp_Head != nullptr)
	{
		tog_Grp_Head->render(window);

		if (tog_Grp_Head->Toggled())
			for (int i = 0; i < n; i++)
				Toggle_Btn_Grp[i]->render(window);
	}
	else
	{
		for (int i = 0; i < n; i++)
			Toggle_Btn_Grp[i]->render(window);
	}
}

void Toggle_Group::clearAll()
{
	for (short i = 0; i < n; i++)
		Toggle_Btn_Grp[i]->disable();
}