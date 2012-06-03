// Switch.hpp

#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "SwitchObserver.hpp"
#include <time.h>
#include <vector>

using namespace std;

class Switch
{
public:
  /// \brief Constructor
  /// \param debounceTime - lenght of time in milli sec to debounce the
  /// input
  Switch(int number, int debounceTime);
	
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
	
	void registerObserver(SwitchObserver *observer);
	
private:
	/// registered observers
	vector<SwitchObserver*> m_observers;

	/// send notification with switch number
	void notifyObservers();
	
	/// switch number
	int m_switchNumber;
	
  /// the debounced switch value
  bool m_switchValue;
	
  /// the debounce time
  double m_debounceTime;
	
  /// indicates an initial state change
  bool m_active;	
	
  /// time m_active became true
  timespec m_lastActiveTime;	
};
#endif //SWITCH_HPP

