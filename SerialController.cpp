#include "SerialController.hpp"
#include <iostream>

using namespace std;

SerialController::SerialController() : serialOut(100), p_switches(64), c_switches(2)
{
	// Setup our Mutexs
	serialqueue = PTHREAD_MUTEX_INITIALIZER;
	switch_lock = PTHREAD_MUTEX_INITIALIZER;

	// Setup our options
	struct termios options;

	//fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

	if (fd == -1){
		//Could not open the port.
		LogController::instance()->error("Serial Port Didn't Open.");
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

		LogController::instance()->info("Serial Port is open and configured. Waiting for Ben's Board..");
	};
	unsigned char *opcode = new unsigned char;
	int done = 1;

	while(done == 1){
		SDL_Delay(20);
		read(fd,opcode, 1);

		if(*opcode == OPC_OK){
			LogController::instance() -> info("Valid Serial Response 1 from Board.");

			while(done == 1){
				read(fd,opcode, 1);
				if(*opcode == OPC_OK2){
					LogController::instance()-> info("Valid Serial Response 2 from Board.");
					done = 0;
				}
			}
		}
	}
	delete opcode;
};

SerialController::~SerialController(){
	LogController::instance()->info("Closing Serial Port.");

	close(fd);
};

void SerialController::KickCoil(int number, int duration){
	unsigned char byte1;
	unsigned char byte2;
	std::ostringstream log;

	if (number >= 32){
		LogController::instance()->warn("KickCoil called with Invalid Coil Number. Coil Not Fired.");
		return;
	};

	if (duration >= 251){
		LogController::instance()->warn("KickCoil called with Invalid Duration. Coil Not Fired");
		return;
	};

	log << "Firing Coil " << number << " for " << duration;
	LogController::instance()->info(log.str());

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

void SerialController::SendData()
{
	if(serialOut.size() > 1)
	{
		std::vector<unsigned char>::iterator itr;
		//Lock Vector
		pthread_mutex_lock(&serialqueue);
		
		
		//Interate through the Vector till its empty sending that data to the serial
		for(itr=serialOut.begin(); itr < serialOut.end(); itr++){
			stringstream ss;
			ss << int(*itr);
			LogController::instance()->info(ss.str());
			if(write(fd,&itr, 1) == -1)
			{
				LogController::instance()->error("couldn't write serial");
			}
		}
		serialOut.clear();
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
				//p_switches[j] = buffer[j];
				switches[j] = buffer[j];
			};

		//c_switches[0] = buffer[8];
		//c_switches[1] = buffer[9];

		cabinet[0] = buffer[8];
		cabinet[1] = buffer[9];


		pthread_mutex_unlock(&switch_lock);
	}

	//Bad Things Happened
	else{
		//We got fucked up
	}
};

void SerialController::set_servo(int servo, int position){
	std::ostringstream log;
	unsigned char byte1;
	unsigned char byte2;

	if (servo >= 32){
		LogController::instance()->warn("Servo Out Of Range. Not Setting.");
		return;
	};

	if (position >= 181){
		LogController::instance()->warn("Servo Position Out of Range. Not Setting.");
		return;
	};

	//Log that we are moving servo # into a position
	log << "Setting Servo " << servo << " to " << position;
	LogController::instance() ->info(log.str());

	//OR our opcode into servo
	servo |= OPC_SERVO;

	//Convert our ints to bytes
	byte1 = (char)servo;
	byte2 = (char)position;

	//Lock Sending Thread
	pthread_mutex_lock(&serialqueue);

	//Put some data at the end of the vector
	serialOut.push_back(byte1);
	serialOut.push_back(byte2);

	//Let the Thread continue sending
	pthread_mutex_unlock(&serialqueue);

	return;
};

void SerialController::set_light(int light, int option, int level){
	std::ostringstream log;
	unsigned char byte1;
	unsigned char byte2;

	if (light > 63 || light < 0){
		LogController::instance() -> warn("Light is outside of valid 0 - 63 range");
		return;
	};

	if (option != 32 && option != 16 && option != 8){
		LogController::instance() -> warn("Light option is invalid");
		return;
	};

	if (level > 7 || level < 0){
		LogController::instance() -> warn("Light Level is invalid");
		return;
	};

	//Log that we are moving servo # into a position
	log << "Setting light " << light << " with option " << option << " to level " << level;
	LogController::instance() ->info(log.str());

	//OR our OPcode and options and level into the two bytes
	light |= OPC_LIGHT;
	level |= option;	//Level and options are combined into a single byte

	byte1 = (char)light;
	byte2 = (char)option;

	//Lock Sending Thread
	pthread_mutex_lock(&serialqueue);

	//Put some data at the end of the vector
	serialOut.push_back(byte1);
	serialOut.push_back(byte2);

	//Let the Thread continue sending
	pthread_mutex_unlock(&serialqueue);

	return;
};

void SerialController::set_rgb(int lred, int lgreen, int lblue, int rred, int rgreen, int rblue){
	std::ostringstream log;
	unsigned char bytes[6];

	int argb[6];

	argb[0]= lred;
	argb[1]= lgreen;
	argb[2]= lblue;
	argb[3]= rred;
	argb[4]= rgreen;
	argb[5]= rblue;

	log << "Sending RGB Values of ";
	for(int i=0; i < 6; i++){

		if(argb[i]> 255 || argb[i] < 0){
			//std::cout << "RGB Value out of range\n";
			LogController::instance()->warn("RGB Value out of range");
			return;
		};

		bytes[i] = (char)argb[i];
		log << argb[i] << " ";
	};

	//If we got this far the RGB values were good so we can write the info log
	LogController::instance() ->info(log.str());

	//Lock Sending Thread
	pthread_mutex_lock(&serialqueue);

	//Put some data at the end of the vector

	//Send RGB LED OPcode
	serialOut.push_back(OPC_SENDRGB);

	for(int i=0; i < 6; i++){
		serialOut.push_back(bytes[i]);
	}

	//Let the Thread continue sending
	pthread_mutex_unlock(&serialqueue);

	return;
};


