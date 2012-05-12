//Connects us to Disk Storage.

//Use for Logging of errors, events, debugging

//Use to log HIGH scores.

#ifndef STORAGE_HPP_
#define STORAGE_HPP_

//Includes
#include <string>
#include <fstream>

//Constants
const std::string logFileName= "log.txt";
const std::string highScoreFileName = "highscore.txt";

class Storage {
public:
	// \ Constructor
	// \ Mount all our file system files
	Storage();

	// \ Destructor
	// \ Unmount all our file system files
	~Storage();

	// \ log writes an event and a description in the [EVENT] - Description. (Should create a list to pull from that isn't type string).
	// \ first string is event, second is description
	// \ example: log("ERROR", "Missing a ball");
	// \ Will write "epoch time - [EVENT] - Description" to the log

	bool log(std::string, std::string);

private:
	// \Handle for our Log File
	std::ofstream logFile;
	// \Handle for our High Score File
	std::ofstream highScoreFile;


};
#endif /* STORAGE_HPP_ */
