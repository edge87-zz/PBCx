#include "LogController.hpp"

LogController::LogController(){
	//Setup our time
	seconds = time(NULL);

	//Cast our time to a string stream because ? who fucking knows.
	ss << seconds;

	//Build our Filename
	filename = "PBCxlog-" + ss.str() + ".txt";

	//Open our log
	logfile.open(filename.c_str());

};

LogController::~LogController(){
	logfile << "[INFO] Log File Destructor Called" << std::endl;
	logfile.close();
};

void LogController::warn(std::string warning){
	logfile << "[WARNING] " << warning << std::endl;
}

void LogController::info(std::string info){
	logfile << "[INFO] " << info << std::endl;
}

void LogController::error(std::string error){
	logfile << "[ERROR] " << error << std::endl;
}



