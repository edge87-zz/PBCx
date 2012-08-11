#include "BallDrain.hpp"

BallDrain::BallDrain(SwitchHandler *handler)
{
	handler->registerObserver(63, this);	
}

BallDrain::~BallDrain()
{
	
}

void BallDrain::notify(int switchNumber)
{
	PlayerMonitor::instance()->changePlayer();
}
