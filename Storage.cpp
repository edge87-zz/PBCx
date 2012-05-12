#include "Storage.hpp"
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>

Storage::Storage(){
	// \ Connect the Logging File Up
	logFile.open(logFileName.c_str());

	// \ Checking for error. Perhaps it doesn't exist and we should create it.
	if(logFile.fail()){
		//Create The file. idk how.
	};

	// \ Connect the High Score File up
	highScoreFile.open(highScoreFileName.c_str());

	// \ Checking for error. Perhaps it doesn't exist and we should create it.
	if(highScoreFile.fail()){
		//Create the file. idk how.
	};

};

Storage::~Storage(){
	// \ Disconnect the Logging File
	logFile.close();
	// \ Disconnect the High Score File
	highScoreFile.close();
};

bool log(std::string event, std::string log){
	std::string toWrite;
	time_t current_time = time(NULL);

	toWrite =  current_time + " - [" + event + "] - " + log ;

	//logFile.write(toWrite);

	//if we have a problem writting this file we need to throw false back
	return false;

	//else we return all ok of true

	return true;
};



