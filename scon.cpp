// I got this code from : http://www.easysw.com/~mike/serial/serial.html
//Also: http://www.cplusplus.com/doc/tutorial/files/


#include <stdio.h>		//Standard input/output definitions
#include <string.h>		//String function definitions
#include <unistd.h>		//UNIX standard function definitions
#include <fcntl.h>		//File control definitions
#include <errno.h>		//Error number definitions
#include <termios.h>	//POSIX terminal control definitions
#include <iostream>		//Input-Output Streams

#include "scon.h"		//WHY do i have to include what i've already include? who knows, i do.

int fd;					//File descriptor for the port

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

int fire_coil(char coil){
	//Coil should be between char 160 (for 0 coil) and 191 (coil 31)
	if (coil > (char)192 || coil < (char)159){
		std::cout << "Not a valid coil - Not Firing\n";
		return 1;
	}

	int written = 0;
	char* sendingThis;

	sendingThis = &coil;

	std::cout << "Firing coil " <<  *sendingThis << "\n";

	written = write(fd, sendingThis, 1);

	if (written < 0 ){
				//Failed to write data to serial port
				std::cout << "Failed to write to port \n";
				return 1;
	};
	return 0;
};

int set_servo(char servo){
	//Servo should be between char 128 (for servo 0) and 159 (servo 31)
	if (servo > (char)159 || servo < (char)127){
		std::cout << "Not a vaild servo - Not setting\n" ;
	}
	return 0;
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
	char switches[4] = {'a','a','a','a'};

	char* pSwitches = switches;
	int allOk = 0;
	req_switches();

	while(allOk == 0){
		allOk = read(fd,pSwitches, 4);
	};

	std::cout << "\n";
	for (int i=0; i < 4; i++){
		std::cout << switches[i];
	};

};



