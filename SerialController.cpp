#include "SerialController.hpp"

SerialController::SerialController(LogController *pnt){
	// Link up our serial logger to our pointer.
	logger = pnt;

	// Setup our options
	struct termios options;

	//fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

	if (fd == -1){
		//Could not open the port.
		logger->error("Serial Port Didn't Open.");
		return;
	}
	else{
		fcntl(fd, F_SETFL);
		//Configure port for 8N1 transmission
		tcgetattr(fd, &options);					//Gets the current options for the port
		cfsetispeed(&options, B115200);				//Sets the Input Baud Rate
		cfsetospeed(&options, B115200);				//Sets the Output Baud Rate
		options.c_cflag |= (CLOCAL | CREAD);		//Enable the receiver and set local mode
		options.c_cflag &= ~PARENB;					//Mask Parody bits
		options.c_cflag &= ~CSTOPB;					//Mask Parody bits

		options.c_cflag &= ~CSIZE;					//8 bits
		options.c_cflag |= CS8;						//8 bits

		options.c_cc[VTIME] = 0;					//Lengh of time in " "  to wait for 12 bytes
		options.c_cc[VMIN] =  12;					//Sets serial options to wait for 12 bytes

		options.c_cflag &= ~CRTSCTS;				//disable flow control

		tcsetattr(fd, TCSANOW, &options);			//Set the new options for the port "NOW"

		logger->info("Serial Port is open and configured.");
	};
};


SerialController::~SerialController(){
	logger->info("Closing Serial Port.");

	close(fd);
};

void SerialController::KickCoil(int number, int duration){
	unsigned char byte1;
	unsigned char byte2;

	if (number >= 32){
		logger->warn("KickCoil called with Invalid Coil Number. Coil Not Fired.");
		return;
	};

	if (duration >= 251){
		logger->warn("KickCoil called with Invalid Duration. Coil Not Fired");
		return;
	};

	logger ->info("Firing Coil " + number +" for " + duration);

	//Add our opcode to the coil
	number |= OPC_COIL;

	//Convert our ints to bytes
	byte1 = (char)number;
	byte2 = (char)duration;

	pthread_mutex_lock(&serialqueue);

	//Put our two bytes into the Stack

	pthread_mutex_unlock(&serialqueue);

	return;
};

