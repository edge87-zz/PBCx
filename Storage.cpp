#include "Storage.hpp"
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>

Storage::Storage(){
	// \ Connect the Logging File Up
		// \ Check if exists, else create

	// \ Connect the High Score File up
		// \ Check if exists, else create

};

Storage::~Storage(){
	// \ Disconnect the Logging File

	// \ Disconnect the High Score File

};

bool log(std::string event, std::string log){
	std::string toWrite;
	time_t current_time = time(NULL);

	toWrite = current_time + " - [" + event + "] - " + log;

	//if we have a problem writting this file we need to throw false back
	return false;

	//else we return all ok of true

	return true;
};



