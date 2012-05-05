// I got this code from : http://www.easysw.com/~mike/serial/serial.html
//Also: http://www.cplusplus.com/doc/tutorial/files/

//Standard Libraries
#include <stdio.h>		//Standard input/output definitions
#include <string.h>		//String function definitions
#include <unistd.h>		//UNIX standard function definitions
#include <fcntl.h>		//File control definitions
#include <errno.h>		//Error number definitions
#include <termios.h>	//POSIX terminal control definitions
#include <iostream>		//Input-Output Streams

//SFML Libraries
#include <SFML/System.hpp> //SFML System header. For pause.

//My Libraries
#include "scon.h"		//WHY do i have to include what i've already included? who knows, i do.

//Local Variables
int fd;					//File descriptor for the port

//External Variables being Imported
extern unsigned char switches[8];
extern unsigned char cabinet[2];

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

//open_port() - Opens serial port and returns file descriptor on success or -1 on error
int open_port(void){
	struct termios options;

	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	//fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

	//sf::Sleep(3.0f);	// NO. Just NO. This was the only way it would work before but i think it was bc we were sending b4 the board was ready. delays were added to the thread.

	if (fd == -1){
		//Could not open the port.
		std::cout << "Port Failed to Open!!!";
		return false;
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

		options.c_cflag &= ~CRTSCTS;				//disable flow control

		tcsetattr(fd, TCSANOW, &options);			//Set the new options for the port "NOW"

		std::cout << "Serial Port OK!\n";
	};

	return true;
};

void kick_coil(int coil, int duration){
	int written = 0;
	unsigned char charConvert;
	unsigned char* sendingThis;

	if (coil >= 32){
		std::cout << "Coil out of Range\n";
		return;
	};

	if (duration >= 251){
		std::cout << "Duration out of Range\n";
		return;
	};

	coil |= OPC_COIL;

	charConvert = (char)coil;

	sendingThis = &charConvert;

	std::cout << "Kicking coil " <<  *sendingThis << " for " << duration << "\n";

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
	unsigned char charConvert;
	unsigned char* sendingThis;

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

void set_light(int light, int option, int level){
	int written = 0;
	unsigned char charConvert;
	unsigned char* sendingThis;

	if (light > 63 || light < 0){
		std::cout << "\nLight is outside range of 0 - 63\n";
	};

	if (option != 32 || option != 16 || option != 8){
		std::cout << "\nInvalid option light";
	};

	if (level > 7 || level < 0){
		std::cout << "\nLevel is Invalid\n";
	};

	light += OPC_LIGHT;
	level += option;	//Level and options are combined into a single byte

	charConvert = (char)light;
	sendingThis = &charConvert;
	written = write(fd, sendingThis, 1);

	charConvert = (char)level;
	sendingThis = &charConvert;
	written += write(fd, sendingThis, 1);

	if (written != 2 ){
		//Failed to write 2 bytes of data to serial port
		std::cout << "Failed to write to port \n" << std::endl ;
		return;
	};

};

void set_rgb(int lr, int lg, int lb, int rr, int rg, int rb){
	int argb[6];
	unsigned char rgbsend[6];
	int written = 0;
	unsigned char *sendingThis;
	unsigned char charTemp;

	argb[0] = lr;
	argb[1] = lg;
	argb[2] = lb;
	argb[3] = rr;
	argb[4] = rg;
	argb[5] = rb;

	for(int i=0; i < 6; i++){
		if(argb[i]> 255 || argb[i] < 0){
			std::cout << "RGB Value out of range\n";
			return;
		};

		rgbsend[i] = (char)argb[i];
	};

	charTemp = OPC_SENDRGB;	//how ugly, can't send constant's address.
	sendingThis = &charTemp;
	written = write(fd, sendingThis, 1);

	sendingThis = &rgbsend[0];
	written += write(fd, sendingThis, 6);

	charTemp = OPC_EOL;
	sendingThis = &charTemp;
	written += write(fd, sendingThis, 1);

	if (written != 8){
		std::cout << "Failed to write RGB colors\n";
		return;
	};

	return;
};

void req_switches(void){
	unsigned char reqCode = OPC_RQSWITCH;
	int written = 0;
	unsigned char* sendReq = &reqCode;

	written = write(fd, sendReq, 1);

	reqCode = OPC_EOL;
	sendReq = &reqCode;
	written += write(fd, sendReq, 1);

	if (written <= 0){
		//return 1;
		std::cout<< "Sending Request for Playfield Switches FAILED\n";
		return;
	};

	std::cout << "Sent Playfield Switch Request OK\n";
	return;
};

void req_cabinet(void){
	unsigned char reqCode = OPC_RQCABINET;
	int written = 0;
	unsigned char* sendReq = &reqCode;

	written = write(fd, sendReq, 1);

	reqCode = OPC_EOL;
	sendReq = &reqCode;
	written += write(fd, sendReq, 1);

	if (written <= 0){
		//return 1;
		std::cout<< "Sending request for Cabinet Switches FAILED\n";
	};

	std::cout << "Sent Cabinet Request ok\n";

	return;
};

void read_switches(){
	unsigned char opcode[1] = {(char)0};
	int bytesRead = 0;

	//Read from the buffer if we can for our opcodes
	read(fd,opcode, 1);

	//std::cout << "PF : " << (int)opcode[0] << std::endl;

	if(opcode[0]== (char)0){
		//Nothing for us to do i guess..
		return;
	}

	//Playfield Switches
	else if(opcode[0] == OPC_RQSWITCH){
		//Process Playfield Switch Bytes
		unsigned char buffer[8] = {(char)0};
		std::cout << "We heard our OPCODE for Playfield Switches\n";
		for(int i=0; i<8; i++){
			bytesRead = 0; //reset this value
			while(bytesRead <= 0){
				bytesRead = read(fd,&buffer[i], 1);
			};
		};
		read(fd,opcode, 1);

		if (opcode[0] == OPC_EOL){
			std::cout << "Success Read EOL For Playfield switches\n";
		};

		for(int j = 0; j < 8; j++){
				switches[j] = buffer[j];
		};
	}

	//Cabinet Switches
	else if(opcode[0] == OPC_RQCABINET){
		//process Cabinet Switch Bytes
		unsigned char buffer[2] = {(char)0, (char)0};
		std::cout << "We see our OPCODE for Cabinet Switches\n";

		read(fd,buffer, 2);

		read(fd,opcode, 1); //Eat end of line

		if (opcode[0] == OPC_EOL){
			std::cout << "Success Read EOL For Cabinet Switches\n";
		};

		for(int j=0; j<2; j++){
			cabinet[j] =  buffer[j];
		};
	}

	//Bad Things Happened
	else{
		//We got fucked up
	};
};
