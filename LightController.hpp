#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <vector>
#include "SerialController.hpp"

enum Light_Option{
	Solid = 0,
	Blink = 8,
	Pulse = 16,
	Strobe = 32
};

struct Lights{
	bool status;
	unsigned char level;
	Light_Option option;
};

class LightController {

public:
	///\brief Constructor
	LightController(LogController *pnt);

	///\brief Destructor
	~LightController();

	///\brief turns off all lights
  ///\note this is time costly method as alot of serial data is sent
	static void Reset();

	///\brief Set a light. Takes 4 args (arrrgs like a pirate)
  ///\param lightnum = light number you wish to change. Valid range is 0 - 63 with anything above or below given you a error.
  ///\param state    = Either true (on) or false (off)
  ///\param level	= Level of brightness. between 0 and 8. Should avoid 0, use the state to turn it off. anything above or below range throws a error.
  ///\param option   = using our enumeration, pick solid, blink pulse or rapid. Anything else won't comple.
	static void Set(int lightnum, int level, Light_Option option);


	///\brief Set Range of Lights
  ///\param lightstart 	= light number you wish to start changing at. Valid range is 0 - 63 with anything above or below given you a error.
  ///\param lightend		= light number you wish to end at. Should be larger than lightstart or what are you doing?
  ///\param state    	= Either true (on) or false (off)
  ///\param level		= Level of brightness. between 0 and 8. Should avoid 0, use the state to turn it off. anything above or below range throws a error.
  ///\param option   	= using our enumeration, pick solid, blink pulse or rapid. Anything else won't comple.
	static void SetRange(int lightstart, int lightend, bool state, int level, Light_Option option);
  
  static void SetStrobe(int lightnum, int numberAfter);

private:
  //Logger has nothing until set
  LogController* logger;

};



#endif /* LIGHT_HPP_ */
