
#include "LogController.hpp"
#include "VideoController.hpp"



LogController *logger = new LogController();


int main(){
	logger->info("Up and Running");

	if(VideoController::init()){
		logger->error("Failed to properly init the VideoController!!");
		return -1; //die
	}

	VideoController::Play("demo.mkv", 1);

	return 0;
}
