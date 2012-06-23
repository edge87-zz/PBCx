#ifndef LOGCONTROLLER_HPP_
#define LOGCONTROLLER_HPP_

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>

class LogController{

	public:
		// \ Setups our file with a name and the UTC time.
		LogController();

		// \ Logs that we're closing the file and then closes it.
		~LogController();

		// \ Takes a string and appends the warning header to it and logs it.
		void warn(std::string warning);

		// \ Takes a string and appends the info header to it and logs it.
		void info(std::string info);

		// \ Takes a string and appends the error header to it and logs it.
		void error(std::string error);

	private:
		// \ Our Time type
		time_t seconds;

		// \ Our Filename for opening our file
		std::string filename;

		// \ A string stream for conversion
		std::stringstream ss;

		// \ A file handle io type for our file? or maybe its an object. Who the hell really knows?
		std::ofstream logfile;
};

#endif /* LOGCONTROLLER_HPP_ */
