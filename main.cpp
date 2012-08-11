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

#include </usr/include/SDL/SDL.h>
#include </usr/include/SDL/SDL_ttf.h>
#include </usr/include/SDL/SDL_mixer.h>


//My includes
//#include "scon.hpp"
#include "AudioController.hpp"
#include "LogController.hpp"
#include "WikiMode.hpp"
#include "SwitchHandler.hpp"
#include "Game.hpp"
#include "SerialController.hpp"
#include "LogController.hpp"
#include "AudioController.hpp"

//Wait for Marcus's Fix
//#include "VideoController.hpp"

extern pthread_mutex_t switch_lock;

//function prototypes
void* read_switches_thread(void* );
void * SerialOutThread(void *args);

//Global Threads
pthread_t readSwitchesThread;

//SerialSend() Thread
pthread_t sdthread;

//global variables
unsigned char switches[8] = {(char)0};
unsigned char cabinet[2] = {(char)0};
//unsigned char test[8] = {(ch	ar)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255};

//Video Stuff
bool programRunning = false;

SDL_Event event;

//Load Serial
//NEW Serial Object
SerialController *Serial = new SerialController();
	
int main (){
	VideoController::init();
	
	VideoController::PlayVideo("video_0.mpg",1);
	AudioController::instance()->addMusic("main", "metallica.wav");
	AudioController::instance()->playMusic("main");

	//Get our blank screen
	SDL_Surface *blank = SDL_CreateRGBSurface(SDL_HWSURFACE, SDL_GetVideoInfo()->current_w, SDL_GetVideoInfo()->current_h, 32, 0, 0, 0, 0);
	SDL_FillRect(blank, NULL, 0x5BB135);
	//Log that we can log. (so we know when we can't)
	LogController::instance()->info("Log Object Created");

	if(pthread_create(&sdthread, NULL, SerialOutThread, (void *)NULL)){
		LogController::instance()->error("SerialSend Thread failed to spawn. Fatal Error.");
	}
	else{
		LogController::instance()->info("SerialSend Thread was Successfully Created");
	}
	
	//Start our serial reading thread
	if(pthread_create( &readSwitchesThread, NULL, read_switches_thread, NULL)){
		LogController::instance()->error("readSwitchesThread Thread failed to spawn. Fatal Error.");
	}
	else{
		LogController::instance()->info("readSwitchesThread Thread was Successfully Created");
	}

  Game tehGame;
  SwitchHandler switchHandler(&tehGame);
  WikiMode wikiMode(&switchHandler);
  

  while(programRunning)
  { //game loop
	if(SDL_PollEvent(&event)) {
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						programRunning = false;
					default:
						break;
				}			
		}
	}
	cout << "in main loop." << endl;
    for(int i = 0; i < 8; i++)
    {
      //pthread_mutex_lock(&switch_lock);
      switchHandler.giveSwitchData(i, switches[i]);
      //pthread_mutex_unlock(&switch_lock);
    }

    //I Need this for example on how you got a string back for the switches.
	//switchText = TTF_RenderText_Solid(font,
	//switchHandler.getSwitchString().c_str(),
	//text_color);

    wikiMode.run();
  }

  //Shutdown Serial
  //Shutdown Logger
  SDL_Quit();
  //And die
  return 0;
};

void* read_switches_thread(void *){

	while(true){
		//old read
		//read_switches();

		//TODO Need a sleep function here
		Serial->RecieveData();
	}
};

void * SerialOutThread(void *args){
	//call SerialController.
	return NULL;
};
