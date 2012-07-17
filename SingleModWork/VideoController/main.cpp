#include "LogController.hpp"
#include "VideoController.hpp"

bool programRunning = true;

LogController *logger = new LogController();

int main(){
	logger->info("Up and Running");

	if(VideoController::init()){
		logger->error("Failed to properly init the VideoController!!");
		return -1; //die
	}

	VideoController::Play("las.mp4", 1);


	while(programRunning == true){

	}



	return 0;
}
