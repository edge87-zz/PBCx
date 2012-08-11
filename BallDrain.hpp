#ifndef BALLDRAIN_HPP
#define BALLDRAIN_HPP

#include "SwitchObserver.hpp"
#include "SwitchHandler.hpp"
#include "PlayerMonitor.hpp"

class BallDrain : public SwitchObserver
{
public:
	BallDrain(SwitchHandler *handler);
	
	~BallDrain();
	
	virtual void notify(int switchNumber);
};

#endif //BALLDRAIN_HPP
