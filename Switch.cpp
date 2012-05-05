/// Switch.cpp

#include "Switch.hpp"
#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

#define NANO 1000000000

Switch::Switch()
{
	clock_gettime(CLOCK_MONOTONIC, &m_lastActiveTime);
}

Switch::Switch(int debounceTime):m_switchValue(false),
m_debounceTime((double)debounceTime / 1000), m_active(false), m_callback(NULL)
{
	clock_gettime(CLOCK_MONOTONIC, &m_lastActiveTime);
}

Switch::~Switch()
{
}

void Switch::switchActive(bool value)
{
	if(value != m_switchValue)
	{
		timespec tempTime;
		clock_gettime(CLOCK_MONOTONIC, &tempTime);		
		if(m_active)
		{
			double difference = (( (double)tempTime.tv_sec + (double)tempTime.tv_nsec/NANO) - ((double)m_lastActiveTime.tv_sec + (double)m_lastActiveTime.tv_nsec/NANO));
			if(difference > m_debounceTime && difference < m_debounceTime * 2)
			{
				m_switchValue = value;
				m_active = false;
				// do something when switch is activated, advance score?
				// perhaps add the function to a stack/list to be called by 
				// a less time sensitive task
				if(value)
				{
					//m_callback();
				}
			}
			else if(difference > m_debounceTime * 2)
			{
				m_active = false;
			}
		}
		else
		{
			clock_gettime(CLOCK_MONOTONIC, &m_lastActiveTime);
			m_active = true;
		}
	}
}

bool Switch::getSwitchValue()
{
	return m_switchValue;
}

