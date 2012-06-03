/*
* We need a delay after we open the serial port. I originally had it at the beginning of the threaded function just before the infinate loop.
* the delay was about one second.
*
*/

//Flag Definations
#define flag0	0x01	// 0000 0001
#define flag1	0x02	// 0000 0010
#define flag2	0x04	// 0000 0100
#define flag3	0x08	// 0000 1000
#define flag4	0x10	// 0001 0000
#define flag5	0x20	// 0010 0000
#define flag6	0x40	// 0100 0000
#define flag7	0x80	// 1000 0000

#define bit0(x) (x & flag0)
#define bit1(x)	(x & flag1)
#define bit2(x) (x & flag2)
#define bit3(x) (x & flag3)
#define bit4(x) (x & flag4)
#define bit5(x) (x & flag5)
#define bit6(x) (x & flag6)
#define bit7(x) (x & flag7)

//Standard Libraries
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#include "SwitchHandler.hpp"
#include "Game.hpp"

//My includes
#include "scon.hpp"
#include "audio.hpp"

//function prototypes
void* read_switches_thread(void* );
std::string char_to_bin_string(unsigned char*, int);

//Global Threads
pthread_t readSwitchesThread;

//global variables
unsigned char switches[8] = {(char)0};
unsigned char cabinet[2] = {(char)0};
//unsigned char test[8] = {(ch	ar)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255};


//Video Stuff

int main (){
	int threadStatus = 0;
	
	int sPort = -1;
	sPort = open_port();
	
	//Start our serial reading thread
	threadStatus = pthread_create( &readSwitchesThread, NULL, read_switches_thread, NULL);
  
  Game tehGame;
  SwitchHandler switchHandler(&tehGame);
  
	std::string sswitches;
	std::string scabinet;

	while(true){ //game loop

		sswitches = "Switch bits: " + char_to_bin_string(switches, 8);
		scabinet = "Cabinet bits: "  + char_to_bin_string(cabinet, 2);
    
    for(int i = 0; i < 8; i++)
    {
      switchHandler.giveSwitchData(i, switches[i]);
    }
    
	

	};

	//Destroy our Threads


	//Destroy serial connection on our way out.
	close(sPort);

	return 0;
};



void* read_switches_thread(void* ){
	//Need a sleep function here
	while(true){
		//need a MUTEX lock here
		read_switches();
		//need a MUTEX unlock here
	}

	//return void*; //Compiler is pissed off i'm not returning anything but i didn't know a void* could return?
};


//This function need an array to avoid rebuilding the string every single time.
std::string char_to_bin_string(unsigned char* charbytes, int nofbytes){
	std::string rstring;

	for(int i=(nofbytes -1); i >= 0; i--){
		if(bit7(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit6(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit5(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit4(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit3(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit2(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit1(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit0(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		rstring += " ";
	};

	return rstring;
};



