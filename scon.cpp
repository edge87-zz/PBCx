// I got this code from : http://www.easysw.com/~mike/serial/serial.html
//Also: http://www.cplusplus.com/doc/tutorial/files/


#include <stdio.h>		//Standard input/output definitions
#include <string.h>		//String function definitions
#include <unistd.h>		//UNIX standard function definitions
#include <fcntl.h>		//File control definitions
#include <errno.h>		//Error number definitions
#include <termios.h>	//POSIX terminal control definitions
#include <iostream>		//Input-Output Streams
#include <SFML/System.hpp> //SFML System header. For pause.

#include "scon.h"		//WHY do i have to include what i've already include? who knows, i do.

int fd;					//File descriptor for the port

//OPCODE Constants
const int OPC_COIL = 160;
const int OPC_SERVO = 128;
const int OPC_LIGHT = 64;
const char OPC_RQSWITCH = (char)62;
const char OPC_RQCABINET = (char)61;
const char OPC_SENDRGB = (char)60;
const char OPC_AUTOCOIL = (char)59;

//open_port() - Opens serial port and returns file descriptor on success or -1 on error
int open_port(void){
	struct termios options;

	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);

	if (fd == -1){
		//Could not open the port.
		std::cout << "Port Failed to Open";
	}
	else{
		fcntl(fd, F_SETFL, FNDELAY); // Sets the read() function to return NOW and not wait for data to enter buffer if there isn't anything there.

		//Configure port for 8N1 transmission
		tcgetattr(fd, &options);					//Gets the current options for the port
		cfsetispeed(&options, B115200);				//Sets the Input Baud Rate
		cfsetospeed(&options, B115200);				//Sets the Output Baud Rate
		options.c_cflag |= (CLOCAL | CREAD);		//Enable the receiver and set local mode
		options.c_cflag &= ~PARENB;					//Mask Parody bits
		options.c_cflag &= ~CSTOPB;					//Mask Parody bits

		options.c_cflag &= ~CSIZE;					//8 bits
		options.c_cflag |= CS8;						//8 bits

		options.c_cflag &= ~CRTSCTS;			//disable flow control

		tcsetattr(fd, TCSANOW, &options);			//Set the new options for the port "NOW"

		std::cout << "seems like everything is ok, keep going\n";
	};

	return true;
};

void fire_coil(int coil, int duration){
	int written = 0;
	char charConvert;
	char* sendingThis;

	if (coil >= 32){
		std::cout << "Coil out of Range\n";
		return;
	};

	if (duration >= 256){
		std::cout << "Duration out of Range\n";
		return;
	};

	coil += OPC_COIL;

	charConvert = (char)coil;

	sendingThis = &charConvert;

	std::cout << "Firing coil " <<  *sendingThis << " for " << duration << "\n";

	written = write(fd, sendingThis, 1);

	charConvert = (char)duration;
	sendingThis = &charConvert;

	written += write(fd,sendingThis, 1);

	if (written != 2 ){
				//Failed to write 2 bytes of data to serial port
				std::cout << "Failed to write to port \n";
				return;
	};
};

void set_servo(int servo, int position){
	int written = 0;
	char charConvert;
	char* sendingThis;

	if (servo >= 32){
		std::cout << "Servo out of Range\n";
		return;
	};

	if (position >= 181){
		std::cout << "Position out of Range\n";
		return;
	};

	servo += OPC_SERVO;

	charConvert = (char)servo;

	sendingThis = &charConvert;

	std::cout << "Setting servo " <<  *sendingThis << " to " << position << "\n";

	written = write(fd, sendingThis, 1);

	charConvert = (char)position;
	sendingThis = &charConvert;

	written += write(fd,sendingThis, 1);

	if (written != 2 ){
		//Failed to write 2 bytes of data to serial port
		std::cout << "Failed to write to port \n";
		return;
	};
};

void req_switches(void){
	char reqCode = 62;
	int written = 0;
	char* sendReq = &reqCode;

	written = write(fd, sendReq, 1);

	if (written == 0){
		//return 1;
		std::cout<< "Sending request for switches failed";
	};

	//return 0;
};

void read_switches(void){
	char switches[9] = {'a','a','a','a','a','a','a','a','a'};

	char* pSwitches = switches;
	int allOk = 0;
	req_switches();

	sf::Sleep(0.2f);

	while(allOk == 0){
		allOk = read(fd,pSwitches, 9);
	};

	std::cout << "\n";
	for (int i=0; i < 9; i++){
		std::cout << switches[i];
	};

};



