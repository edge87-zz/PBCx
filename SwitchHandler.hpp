/// \class SwitchHandler

#ifndef SWITCHHANDLER_HPP
#define SWITCHHANDLER_HPP

#include <vector>
#include "Switch.hpp"
#include "Game.hpp"

using namespace std;

class SwitchHandler
{
public:
	SwitchHandler(Game *game);
	
	~SwitchHandler();
  
  void giveSwitchData(int subset, unsigned char switchInfo);
	
  void registerObserver(int switchNumber, SwitchObserver *observer);
  
private:
	vector<Switch*> switches;
};

#endif //SWITCHHANDLER_HPP
