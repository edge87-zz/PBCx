#include "SwitchHandler.hpp"

SwitchHandler::SwitchHandler()
{
	for(int i = 0; i < 64; i++)
	{
		switches.append(new Switch(i, 15));
	}
}

SwitchHandler::~SwitchHandler()
{

}

void SwitchHandler::giveSwitchData(int subset, char* switchInfo)
{
	for(i = 0; i < 8; i++)
	{
		switches[(subset * 8) + i].switchActive(1 && ((switchInfo >> i) & 1));
	}
}

void
