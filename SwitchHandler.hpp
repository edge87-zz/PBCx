/// \class SwitchHandler

#ifndef SWITCHHANDLER_HPP
#define SWITCHHANDLER_HPP

#include <vector>
#include <string>
#include "Switch.hpp"
#include "Game.hpp"

class SwitchHandler
{
public:
	SwitchHandler(Game *game);
	
	~SwitchHandler();
  
  void giveSwitchData(int subset, unsigned char switchInfo);
	
  void registerObserver(int switchNumber, SwitchObserver *observer);
  
  std::string getSwitchString();
  
  std::string getCabinetString();

private:
	vector<Switch*> switches;
};

#endif //SWITCHHANDLER_HPP
