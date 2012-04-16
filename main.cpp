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

	int coil = 0;
	int duration = 0;

	while (true){
		std::cout << "\nInput the coil number to fire and then duration\n";
		std::cout << "\nIf you put a negative number in i'll bail out and crash\n";

		if (coil == -1){
			break;
		};

		fire_coil(coil, duration);
	};

	close(sPort);	//destroy serial connection on our way out.

	return 0;
};




