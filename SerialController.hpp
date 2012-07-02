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
#include <vector>		//Vector Lib
#include <sstream>		//String Streams

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

		//Send data to microcontroller (thread from main calls this)
		void SendData();

		//Read Data from MicroController (thread from main calls this)
		void RecieveData();

		/* KickCoil() sends a two byte command / coil + duration.
		 *
		 * To use: first int is coil (0 - 31) you wish to kick. Second int is duration (0-254)
		 *
		 * Example: kick_coil(3, 120);
		 */
		void KickCoil(int number, int duration);

		/*set_servo sends a two byte command / servo + desired value.
		 *
		 * To use: first int is servo (0 - 31) you wish to set. Second int is position (0 - 128)
		 *
		 * Example: set_servo(2, 80);
		 */
		void set_servo(int, int);

		/* set_light sends a two byte command to changes lights. First byte is light number second byte is options and level.
		 *
		 * To use: First int is light valid values: 0 - 63
		 *
		 * Second int is option, valid values:
		 * * 8  = blink
		 * * 16 = Strobe +3
		 * * 32 = pulsate
		 *
		 * Third int is level, valid values: 0 - 8 (expect 0 does nothing)
		 *
		 * Example: set_light(13, 8, 3);
		 *
		 * Sets the 13th light to blink at a level of 3.
		 */
		void set_light(int, int, int);


		/* set_rgb sets the rbg left and right rgb lights. Sends 8 bytes (1 command , 1 EOL)
		 *
		 * To use: The first three ints are for the left side and second three ints are for the right. Each value is 0 - 254 RGB
		 *
		 * Example: set_rgb(0, 0, 200, 200, 0, 0);
		 *
		 * Sets the left side to blue and the right side to red.
		 */
		void set_rgb(int, int, int, int, int, int);

	private:
		//Logger has nothing until set
		LogController* logger;

		//File Descriptor
		int fd;

		//Vector Mutex for inserting or removing from queue
		pthread_mutex_t serialqueue;

		//Vector for Serial Out
		std::vector<unsigned char> serialOut;
};

#endif /* SERIALCONTROLLER_HPP_ */
