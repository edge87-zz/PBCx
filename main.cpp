#include "scon.h"
#include "audio.hpp"
//#include "video.h"

#include <iostream>

int main (){
	int sPort = -1;
	sPort = open_port();

	if (sPort){
		std::cout << "Serial Port is Open and Ready";
	};

	char inputChar = 0;
	int tmpInt = 0;
	while (true){
		std::cout << "\nInput the number to be type casted to a char and sent\n";
		std::cout << "\nIf you put a negative number in i'll bail out and crash\n";
		std::cin >> tmpInt;

		if (tmpInt == -1){
			break;
		}

		if (tmpInt == 62){
			read_switches();
			playTest();

		};

		if (tmpInt >= 64 && tmpInt <= 127 ){
			//Light Command Beginning
			std::cout << "\nlight Command\n";

		};

		if (tmpInt >= 128 && tmpInt <= 159){
			//Servo Command Beginning
			std::cout << "\nServo Command\n";

		};

		if (tmpInt >= 160 && tmpInt <= 191){
			//Coil Command Beginning
			std::cout << "\nCoil Command\n";

		};



		//inputChar = (char)tmpInt;

		//fire_coil(inputChar);


	};

	close(sPort);	//destroy serial connection on our way out.

	return 0;
};




