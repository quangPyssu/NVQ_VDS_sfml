#include "Toggle_Group.h"
#include <iostream>

void Toggle_Group::update(short id)
{
	//cout << &Toggle_Btn_Grp[id] << endl;
	for (short i = 0; i < n; i++) 
		Toggle_Btn_Grp[i]->disable();

	Toggle_Btn_Grp[id]->TurnOn();	
	//std::cout << Toggle_Btn_Grp[id] << std::endl;
}