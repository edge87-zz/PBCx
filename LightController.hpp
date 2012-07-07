#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <vector>

enum Light_Option{
	solid = 0,
	blink = 8,
	pulse = 16,
	rapid = 32
};

struct Lights{
	bool status;
	unsigned char level;
	Light_Option option;
};

class LightController {

public:
	///\brief Constructor
	LightController();

	///\brief Destructor
	~LightController();

	///\brief Resets the Light Vector back to its original construct
	void Reset();

	///\brief Set a light. Takes 4 args (arrrgs like a pirate)
  ///\param lightnum = light number you wish to change. Valid range is 0 - 63 with anything above or below given you a error.
  ///\param state    = Either true (on) or false (off)
  ///\param level	= Level of brightness. between 0 and 8. Should avoid 0, use the state to turn it off. anything above or below range throws a error.
  ///\param option   = using our enumeration, pick solid, blink pulse or rapid. Anything else won't comple.

	void Set(int lightnum, bool state, int level, Light_Option option);


	///\brief Set Range of Lights
  ///\param lightstart 	= light number you wish to start changing at. Valid range is 0 - 63 with anything above or below given you a error.
  ///\param lightend		= light number you wish to end at. Should be larger than lightstart or what are you doing?
  ///\param state    	= Either true (on) or false (off)
  ///\param level		= Level of brightness. between 0 and 8. Should avoid 0, use the state to turn it off. anything above or below range throws a error.
  ///\param option   	= using our enumeration, pick solid, blink pulse or rapid. Anything else won't comple.

	void SetRange(int lightstart, int lightend, bool state, int level, Light_Option option);

	///\brief Update Ben's Board
	bool Update(void);


private:
	std::vector<Lights> lights;

};



#endif /* LIGHT_HPP_ */
