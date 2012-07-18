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


	VideoController::PlayVideo("video_0.mpg",1,small);


	while(programRunning == true){

	}



	return 0;
}
