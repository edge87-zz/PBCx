#ifndef BALLDRAIN_HPP
#define BALLDRAIN_HPP

#include "SwitchObserver.hpp"
#include "SwitchHandler.hpp"
#include "PlayerMonitor.hpp"
#include "SerialController.hpp"

extern SerialController *Serial;

class BallDrain : public SwitchObserver
{
public:
	BallDrain(SwitchHandler *handler);
	
	~BallDrain();
	
	bool getBallOne();
	
	void run();
	
	virtual void notify(int switchNumber);
	
private:
	bool ballOne;
	
	timespec endTimer;
	
	bool coilKicked;
	
};

#endif //BALLDRAIN_HPP
