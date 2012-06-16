#include "LightController.hpp"

using namespace std;

LightController::LightController() : lights(64)
{

	for (int i=0; i++; i < lights.size()){
		lights[i].status = false;
		lights[i].level = 0;
		lights[i].option = solid;
	};
};

LightController::~LightController()
{

};


