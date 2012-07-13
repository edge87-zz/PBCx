#include "LightController.hpp"

using namespace std;

LightController::LightController(LogController *pnt)
{
	// Link up our serial logger to our pointer.
	logger = pnt;

	//Rest our light state
	Reset();
};

LightController::~LightController()
{

};

void LightController::Reset()
{  
  for(int i = 0; i < 64; i++)
  {
    set_light(i, Solid, 0);
  }
};

void LightController::Set(int lightnum, int level, Light_Option option)
{
	if (lightnum > 63 || lightnum < 0)
  {
		logger->warn("LightController::Set - Invalid Light to set. ");
		return;
	}

  if(option == Strobe)
  {
    //use strobe function
    return;
  }
  
	if (level > 8 || level < 0)
  {
		logger->warn("LightController::Set - Invalid Light Level");
		return;
	}	
  
  set_light(lightnum, option, level);
};

void LightController::SetRange(int lightstart, int lightend, bool state, int level, Light_Option option){
		if (lightstart > 63 || lightstart < 0 || lightstart >= lightend)
    {
			logger->warn("LightController::SetRange - Invalid LightStart Range. Not Setting.");
			return;
		}

		if(lightend > 63 || lightend < 0 || lightend <= lightstart)
    {
			logger->warn("LightController::SetRange - Invalid LightEnd Range. Not Setting.");
			return;
		}

    if(option == Strobe)
    {
      //use set strobe function for strobe
      return;
    }
    
		if (level > 8 || level < 0)
    {
			logger->warn("LightController::SetRange - Invalid Level");
			return;
		}
		
    for(int i = lightstart; i <= lightend; i++)
    {
      set_light(i, option, level);
    }
}

void LightController::SetStrobe(int lightnum, int numberAfter)
{
  if(lightnum + numberAfter > 63)
  {
    logger->warn("LightController::SetStrobe - Invalid Range. Went Over 63");
    return;
  }
  set_light(lightnum, Strobe, numberAfter);
}


