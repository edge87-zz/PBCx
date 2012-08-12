/// Switch.cpp

#include "Switch.hpp"
#include "Game.hpp"
#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

#define NANO 1000000000

Switch::Switch(int number, int debounceTime):m_switchValue(false),
m_debounceTime((double)debounceTime / 1000), m_active(false), m_switchNumber(number)
{
	clock_gettime(CLOCK_MONOTONIC, &m_lastActiveTime);
}

Switch::~Switch()
{
}

void Switch::switchActive(bool value)
{
	m_switchValue = value;
	/*if(value != m_switchValue)
	{
		timespec tempTime;
		clock_gettime(CLOCK_MONOTONIC, &tempTime);		
		double difference = (( (double)tempTime.tv_sec + (double)tempTime.tv_nsec/NANO) - ((double)m_lastActiveTime.tv_sec + (double)m_lastActiveTime.tv_nsec/NANO));
			
		if(m_active && (difference > m_debounceTime))
		{
			clock_gettime(CLOCK_MONOTONIC, &m_lastActiveTime);
			notifyObservers();
		}
	}*/
}

bool Switch::getSwitchValue()
{
	return m_switchValue;
}

void Switch::registerObserver(SwitchObserver *observer)
{
	m_observers.push_back(observer);
}

void Switch::notifyObservers()
{
	for(vector<SwitchObserver*>::iterator iter = m_observers.begin(); iter != m_observers.end(); iter++)
	{
		(*iter)->notify(m_switchNumber);
	}
}
