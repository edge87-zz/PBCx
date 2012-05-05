// Switch.hpp

#ifndef SWITCH_HPP
#define SWITCH_HPP

#include <time.h>

class Switch
{
public:
	/// \brief Constructor
	Switch();
	
	/// \brief Constructor
	/// \param debounceTime - lenght of time in milli sec to debounce the
	/// input
	Switch(int debounceTime);
	
	/// \brief Destructor
	~Switch();
	
	/// \brief processes the switch data
	/// \param value - the switch value true = on false = off
	/// \note if the debounce time is greater than 0 this may not 
	/// neccessarily mean the switch will be treated as active
	void switchActive(bool value);
	
	/// \brief accessor for the debounced switch value
	/// \return the debounced switch value
	bool getSwitchValue();
	
private:
	/// the debounced switch value
	bool m_switchValue;
	
	/// the debounce time
	double m_debounceTime;
	
	/// indicates an initial state change
	bool m_active;	
	
	/// time m_active became true
	timespec m_lastActiveTime;
	
	/// this may be implemented later to be called when the switch 
	/// state (on to off, off to on)
	void (*m_callback)();
	
};
#endif //SWITCH_HPP

