#include "BallDrain.hpp"
#include <iostream>
#include "AudioController.hpp"

using namespace std;

BallDrain::BallDrain(SwitchHandler *handler)
{
	ballOne = false;
	handler->registerObserver(63, this);	
	handler->registerObserver(62, this);
	handler->registerObserver(61, this);
	handler->registerObserver(60, this);
	handler->registerObserver(59, this);
}

BallDrain::~BallDrain()
{
	
}

bool BallDrain::getBallOne()
{
	return ballOne;
}

void BallDrain::notify(int switchNumber)
{
	switch(switchNumber)
	{
		case 63:
			AudioController::instance()->playSound("scream");
			PlayerMonitor::instance()->changePlayer();
			break;
		case 59:
			if(!ballOne)
			{
				clock_gettime(CLOCK_MONOTONIC, &endTimer);	
				endTimer.tv_sec += 2;
				ballOne = true;
			}	
			break;
		default:
			break;			
	}
}

void BallDrain::run()
{
  timespec tempTime;
  clock_gettime(CLOCK_MONOTONIC, &tempTime);	
  bool kicked = false;
  if(ballOne == true)
  {
    if(tempTime.tv_sec > endTimer.tv_sec && !kicked)
    {
		Serial->KickCoil(22, 250);	
		endTimer.tv_sec += 1;
		kicked = true;
    }
    else if(tempTime.tv_sec > endTimer.tv_sec)
    {
		ballOne = false;
	}
  }  
}
