#include "LightController.hpp"

using namespace std;

LightController::LightController() : lights(64)
{

	for (int i=0; i++; i < lights.size()){
		lights[i].status = false;
		lights[i].level = 0;
		lights[i].option = solid;
	};

	LightController::Update();
};

LightController::~LightController()
{
//Destroy Lights Vector
};

void LightController::Reset(){
	for (int i=0; i++; i < lights.size()){
			lights[i].status = false;
			lights[i].level = 0;
			lights[i].option = solid;
		};

	LightController::Update();
};

void LightController::Set(int lightnum, bool state, int level, Light_Option option){
	if (lightnum > 63 || lightnum < 0){
		//Bad Log here
		//Complain that we've been lied to about the cake
		return;
	}

	if (level > 8 || level < 0){
		//Bad Log Here
		//Complain about level
		return;
	}

	lights[lightnum].status = state;
	lights[lightnum].level = level;
	lights[lightnum].option = option;

	LightController::Update();

	return;
};

void LightController::SetRange(int lightstart, int lightend, bool state, int level, Light_Option option){
		if (lightstart > 63 || lightstart < 0 || lightstart >= lightend){
			//Bad Log here
			//Complain that we've been lied to about the cake
			return;
		}

		if(lightend > 63 || lightend < 0 || lightend <= lightstart){
			//Bad Log Here
			//Complain about lightend
			return;
		}

		if (level > 8 || level < 0){
			//Bad Log Here
			//Complain about level
			return;
		}

		for (int i=lightstart; i <= lightend; i++){
			lights[i].status = false;
			lights[i].level = 0;
			lights[i].option = solid;
		}

		LightController::Update();
}

bool LightController::Update(void){
	// Send the whole Vector to ben's Board... easier said than done.


	return true;
}


