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
	//Constructor
	LightController();

	//Destructor
	~LightController();

private:
	std::vector<Lights> lights;

};



#endif /* LIGHT_HPP_ */
