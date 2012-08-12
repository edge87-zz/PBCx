#include "BallDrain.hpp"
#include <iostream>
#include "AudioController.hpp"

using namespace std;

BallDrain::BallDrain(SwitchHandler *handler)
{
	handler->registerObserver(63, this);	
}

BallDrain::~BallDrain()
{
	
}

void BallDrain::notify(int switchNumber)
{
	AudioController::instance()->playSound("scream");
	PlayerMonitor::instance()->changePlayer();
}
