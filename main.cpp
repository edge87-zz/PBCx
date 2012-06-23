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
#include </usr/include/SDL/SDL.h>
#include </usr/include/SDL/SDL_ttf.h>

//My includes
#include "scon.hpp"
#include "audio.hpp"
#include "LogController.hpp"
#include "WikiMode.hpp"
#include "SwitchHandler.hpp"
#include "Game.hpp"

extern pthread_mutex_t switch_lock;

//function prototypes
void* read_switches_thread(void* );
std::string char_to_bin_string(unsigned char*, int);
SDL_Surface* OnLoad(char* File);
bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
void OnEvent(SDL_Event* Event);

//Global Threads
pthread_t readSwitchesThread;

//global variables
unsigned char switches[8] = {(char)0};
unsigned char cabinet[2] = {(char)0};
//unsigned char test[8] = {(ch	ar)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255};

//Video Stuff
bool displayRunning = false;
SDL_Surface*	Surf_Display;
SDL_Surface*	Surf_Background;
SDL_Event Event;

//Load Logger
LogController *logger = new LogController();

int main (){
	//Log that we can log. (so we know when we can't)
	logger->info("Log Object Created");

	int threadStatus = 0;
	
	//Open our Serial Port
	open_port(logger);
	
	//Wait for Ben's board to "restart" because of the serial connection being opened
	SDL_Delay(200);

	//Start our serial reading thread
	threadStatus = pthread_create( &readSwitchesThread, NULL, read_switches_thread, NULL);

	//Bring SDL up
	displayRunning = true;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		logger->error("Failed to load and initialize SDL. This is fatal.");
		return false;
	};

	if((Surf_Display = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		logger->warn("Couldn't Set video Mode to 1920x1080.");
	};

	if((Surf_Background = OnLoad("./media/images/background.bmp")) == NULL) {
		 logger->warn("Background Failed to Load");
	};

	OnDraw(Surf_Display, Surf_Background, 0, 0);

	SDL_Flip(Surf_Display);
  
	if (TTF_Init() < 0) {
	    logger->error("SDL TTF Failed to Initalize. Fatal Error");
	}
  
  TTF_Font *font;
  font = TTF_OpenFont("FreeMono.ttf", 24);

  if (font){
	  logger->info("Font FreeMono Loaded.");
  }
  else {
	  logger->error("Font FreeMono Failed to load.");
  }

  // Write text to surface
  SDL_Surface *text;
  SDL_Color text_color = {255, 255, 255};

  Game tehGame;
  SwitchHandler switchHandler(&tehGame);
  WikiMode wikiMode(&switchHandler);
  
	std::string sswitches;
	std::string scabinet;

	while(displayRunning)
  { //game loop
    OnDraw(Surf_Display, Surf_Background, 0, 0);

    for(int i = 0; i < 8; i++)
    {
      //pthread_mutex_lock(&switch_lock);
      switchHandler.giveSwitchData(i, switches[i]);
      //pthread_mutex_unlock(&switch_lock);
    }

    text = TTF_RenderText_Solid(font,
      switchHandler.getSwitchString().c_str(),
      text_color);
    SDL_BlitSurface(text, NULL, Surf_Display, NULL);

    wikiMode.run();
    
    while(SDL_PollEvent(&Event)) {
    	OnEvent(&Event);
    }

    SDL_Flip(Surf_Display);
	

	}

	//Destroy serial connection on our way out.
	close_port(logger);

	//Call the destructor of our object and close the file.
	delete logger;

	//Release the TTF fonts and their resources
	TTF_Quit;

	//And die
	return 0;
};

void* read_switches_thread(void *){
	//Need a sleep function here
	while(true){
		//need a MUTEX lock here
		read_switches();
		//need a MUTEX unlock here
	}

	//return void*; //Compiler is pissed off i'm not returning anything but i didn't know a void* could return?
};

SDL_Surface* OnLoad(char* File){
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;

	if((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
	        return NULL;
	};

	Surf_Return = SDL_DisplayFormat(Surf_Temp);
	SDL_FreeSurface(Surf_Temp);

	return Surf_Return;
};

bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    };

    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

    return true;
};

void OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        displayRunning = false;
    };

    if(Event->key.keysym.sym ==  SDLK_ESCAPE){
    	displayRunning = false;
    };
};





