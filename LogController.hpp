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

		LogController();

		~LogController();

		void warn(std::string warning);

		void info(std::string info);

		void error(std::string error);


	private:
		time_t seconds;
		std::string filename;
		std::stringstream ss;


		std::ofstream logfile;
};





#endif /* LOGCONTROLLER_HPP_ */
