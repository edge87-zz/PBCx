#include "BallDrain.hpp"
#include <iostream>

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
	cout << "You are dead!" << endl;
	PlayerMonitor::instance()->changePlayer();
}
