#ifndef SERIALCONTROLLER_HPP_
#define SERIALCONTROLLER_HPP_

//Includes
#include <stdio.h>		//Standard input/output definitions
#include <string.h>		//String function definitions
#include <unistd.h>		//UNIX standard function definitions
#include <fcntl.h>		//File control definitions
#include <errno.h>		//Error number definitions
#include <termios.h>	//POSIX terminal control definitions
#include <iostream>		//Input-Output Streams
#include <pthread.h>	//Threading

//Our files
#include "LogController.hpp"

///Constants
//OPCODE Constants
const int OPC_COIL = 160;
const int OPC_SERVO = 128;
const int OPC_LIGHT = 64;

const unsigned char OPC_EOL = (char)255;
const unsigned char OPC_RQLIGHT = (char)63;
const unsigned char OPC_RQSWITCH = (char)62;
const unsigned char OPC_RQCABINET = (char)61;
const unsigned char OPC_SENDRGB = (char)60;
const unsigned char OPC_AUTOCOIL = (char)59;

//Light Constant options
const int PULSATE = 32;
const int STROBE = 16;
const int BLINK = 8;

class SerialController{
	public:
		//Constructor
		SerialController(LogController *pnt);

		//Deconstructor
		~SerialController();

	private:
		//Logger has nothing until set
		LogController* logger = NULL;

		//File Descriptor
		int fd;


};



#endif /* SERIALCONTROLLER_HPP_ */
