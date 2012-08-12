#include "SwitchHandler.hpp"
#include <string>

using namespace std;

namespace
{
  const int maxSwitches = 64;
  const int maxCabinet = 2;
}

SwitchHandler::SwitchHandler()
{
	for(int i = 0; i < maxSwitches; i++)
	{
		switches.push_back(new Switch(i, 15));
	}  
}

SwitchHandler::~SwitchHandler()
{

}

void SwitchHandler::giveSwitchData(int subset, unsigned char switchInfo)
{
	for(int i = 0; i < 8; i++)
	{
		switches[(subset * 8) + i]->switchActive((switchInfo >> i) & 1);
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

    if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39 || i == 47 || i == 55 || i == 63){
    	switchString += " ";
    }
  }
  return switchString;
}

string SwitchHandler::getCabinetString(){
	string switchString = "a";

	//for (int i =0; i < maxCabinet; i++){
	//	switchString += (cabinet[i] == 1)? '1' : '0';
	//}

	return switchString;
}
