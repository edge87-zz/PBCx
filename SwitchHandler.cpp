#include "SwitchHandler.hpp"
#include <string>

using namespace std;

namespace
{
  const int maxSwitches = 64;
}

SwitchHandler::SwitchHandler(Game *game)
{
	for(int i = 0; i < maxSwitches; i++)
	{
		switches.push_back(new Switch(i, 15));
	}
  for(int i = 0; i < switches.size(); i++)
  {
    registerObserver(i, game);
  }
}

SwitchHandler::~SwitchHandler()
{

}

void SwitchHandler::giveSwitchData(int subset, unsigned char switchInfo)
{
	for(int i = 0; i < 8; i++)
	{
		switches[(subset * 8) + i]->switchActive(1 && ((switchInfo >> i) & 1));
	}
}

void SwitchHandler::registerObserver(int number, SwitchObserver *observer)
{
  switches[number]->registerObserver(observer);
}

string SwitchHandler::getSwitchString()
{
  string switchString;
  for(int i = 0; i < maxSwitches; i++)
  {
    switchString += switches[i]->getSwitchValue()?'1':'0';
  }
  return switchString;
}
