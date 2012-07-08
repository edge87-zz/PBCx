#include "LightController.hpp"

using namespace std;

LightController::LightController()
{
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
		//Bad Log here
		//Complain that we've been lied to about the cake
		return;
	}

  if(option == Strobe)
  {
    //use strobe function
    return;
  }
  
	if (level > 8 || level < 0)
  {
		//Bad Log Here
		//Complain about level
		return;
	}	
  
  set_light(lightnum, option, level);
};

void LightController::SetRange(int lightstart, int lightend, bool state, int level, Light_Option option){
		if (lightstart > 63 || lightstart < 0 || lightstart >= lightend)
    {
			//Bad Log here
			//Complain that we've been lied to about the cake
			return;
		}

		if(lightend > 63 || lightend < 0 || lightend <= lightstart)
    {
			//Bad Log Here
			//Complain about lightend
			return;
		}

    if(option == Strobe)
    {
      //use set strobe function for strobe
      return;
    }
    
		if (level > 8 || level < 0)
    {
			//Bad Log Here
			//Complain about level
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
    //shits fucked
    return;
  }
  set_light(lightnum, Strobe, numberAfter);
}


