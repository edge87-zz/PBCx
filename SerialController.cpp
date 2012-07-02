#include "SerialController.hpp"

SerialController::SerialController(LogController *pnt) : serialOut(100)
{
	// Link up our serial logger to our pointer.
	logger = pnt;

	// Setup our Mutex
	serialqueue = PTHREAD_MUTEX_INITIALIZER;

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
	std::ostringstream log;

	if (number >= 32){
		logger->warn("KickCoil called with Invalid Coil Number. Coil Not Fired.");
		return;
	};

	if (duration >= 251){
		logger->warn("KickCoil called with Invalid Duration. Coil Not Fired");
		return;
	};

	log << "Firing Coil " << number << " for " << duration;
	logger ->info(log.str());

	//Add our opcode to the coil
	number |= OPC_COIL;

	//Convert our ints to bytes
	byte1 = (char)number;
	byte2 = (char)duration;

	pthread_mutex_lock(&serialqueue);

	serialOut.push_back(byte1);
	serialOut.push_back(byte2);

	pthread_mutex_unlock(&serialqueue);

	return;
};

void SerialController::SendData(){
	std::vector<unsigned char>::iterator itr;

	if(serialOut.size() > 1){
		//Lock Vector
		pthread_mutex_lock(&serialqueue);

		//Interate through the Vector till its empty sending that data to the serial
		for(itr=serialOut.begin(); itr < serialOut.end(); itr++){
			write(fd,&itr, 1);
		}
		//Unlock Vector
		pthread_mutex_unlock(&serialqueue);
	}
};

void SerialController::RecieveData(){
	unsigned char opcode[1] = {(char)0};
	int bytesRead = 0;

	//Read from the buffer if we can for our opcodes
	read(fd,opcode, 1);

	if(opcode[0]== (char)0){
		//Nothing for us to do i guess..
		return;
	}

	//Playfield Switches and cabinet switches
	else if(opcode[0] == OPC_RQSWITCH){
		//Process Playfield Switch Bytes
		unsigned char buffer[10] = {(char)0};

		for(int i=0; i<10; i++){
			bytesRead = 0; //reset this value
			while(bytesRead <= 0){
				bytesRead = read(fd,&buffer[i], 1);
			};
		};

		read(fd,opcode, 1);

	    pthread_mutex_lock(&switch_lock);
			for(int j = 0; j < 8; j++){
				switches[j] = buffer[j];
			};

		cabinet[0] = buffer[8];
		cabinet[1] = buffer[9];

		pthread_mutex_unlock(&switch_lock);
	}

	//Bad Things Happened
	else{
		//We got fucked up
	}
};


