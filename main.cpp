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

		std::cin >> tmpInt;

		if (tmpInt == -1){
			break;
		}

		inputChar = (char)tmpInt;

		fire_coil(inputChar);
	};

	close(sPort);	//destroy serial connection on our way out.

	return 0;
};




