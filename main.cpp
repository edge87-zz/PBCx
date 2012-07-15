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
//#include "scon.hpp"
#include "audio.hpp"
#include "LogController.hpp"
#include "WikiMode.hpp"
#include "SwitchHandler.hpp"
#include "Game.hpp"
#include "SerialController.hpp"
#include "VideoController.hpp"

extern pthread_mutex_t switch_lock;
extern int fd;

//function prototypes
void* read_switches_thread(void* );
std::string char_to_bin_string(unsigned char*, int);
SDL_Surface* OnLoad(char* File);
bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
void OnEvent(SDL_Event* Event);
void * SerialOutThread(void *args);

//SUPER TEMP sorry
std::string cabinetString();

//Global Threads
pthread_t readSwitchesThread;

//SerialSend() Thread
pthread_t sdthread;

//global variables
unsigned char switches[8] = {(char)0};
unsigned char cabinet[2] = {(char)0};
//unsigned char test[8] = {(ch	ar)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255};

//Video Stuff
bool displayRunning = false;

//MAIN Screen
SDL_Surface*	Surf_Display;

//Drawing Surface
SDL_Surface*	Surf_Background;

//Events needed for development so we can kill the screen.
SDL_Event Event;

//Load Logger
	LogController *logger = new LogController();

//load VideoController
	VideoController *Video = new VideoController(logger, Surf_Display);

//Load Serial
	//NEW Serial Object
	SerialController *Serial = new SerialController(logger);

int main (){
	//Log that we can log. (so we know when we can't)
	logger->info("Log Object Created");

	//Open our Serial Port
	//open_port(logger);
	
	//Wait for Ben's board to "restart" because of the serial connection being opened
	//** NOT NEEDED with new SerialController
	//SDL_Delay(5000);

	if(pthread_create(&sdthread, NULL, SerialOutThread, (void *)NULL)){
			logger ->error("SerialSend Thread failed to spawn. Fatal Error.");
		}

		else{
			logger ->info("SerialSend Thread was Successfully Created");
	}

	//Start our serial reading thread
	if(pthread_create( &readSwitchesThread, NULL, read_switches_thread, NULL)){
			logger ->error("readSwitchesThread Thread failed to spawn. Fatal Error.");
		}
		else{
			logger ->info("readSwitchesThread Thread was Successfully Created");

	}

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
  SDL_Surface *switchText, *cabinetText;
  SDL_Color text_color = {255, 255, 255};

  Game tehGame;
  SwitchHandler switchHandler(&tehGame);
  WikiMode wikiMode(&switchHandler, Video);
  

  while(displayRunning)
  { //game loop
    OnDraw(Surf_Display, Surf_Background, 0, 0);

    for(int i = 0; i < 8; i++)
    {
      //pthread_mutex_lock(&switch_lock);
      switchHandler.giveSwitchData(i, switches[i]);
      //pthread_mutex_unlock(&switch_lock);
    }

    switchText = TTF_RenderText_Solid(font,
      switchHandler.getSwitchString().c_str(),
      text_color);

    cabinetText = TTF_RenderText_Solid(font,
    		cabinetString().c_str(),
    	      text_color);

    SDL_Rect DestR;

    DestR.x = 0;
    DestR.y = 30;

    SDL_BlitSurface(switchText, NULL, Surf_Display, NULL);
    SDL_BlitSurface(cabinetText, NULL, Surf_Display, &DestR);

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
	//delete Serial;

	//Release the TTF fonts and their resources
	TTF_Quit;

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
    	logger->error("SDL failed to draw. Function OnDraw.");
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

void * SerialOutThread(void *args){
	//call SerialController.
	return NULL;
};

std::string cabinetString(){
	std::string rstring;
	for (int i = 0; i < 2; i++){

			if(bit0(cabinet[i])) {
				rstring += '1';
			}

			else{
				rstring += '0';
			}

			if(bit1(cabinet[i])) {
				rstring += '1';
			}

			else{
				rstring += '0';
			}

			if(bit2(cabinet[i])) {
				rstring += '1';
				}

			else{
				rstring += '0';
			}

			if(bit3(cabinet[i])) {
				rstring += '1';
			}

			else{
				rstring += '0';
			}

			if(bit4(cabinet[i])) {
				rstring += '1';
			}

			else{
				rstring += '0';
			}

			if(bit5(cabinet[i])) {
				rstring += '1';
			}

			else{
				rstring += '0';
			}

			if(bit6(cabinet[i])) {
				rstring += '1';
			}

			else{
				rstring += '0';
			}

			if(bit7(cabinet[i])) {
				rstring += '1';
			}

			else{
				rstring += '0';
			}
		rstring += " ";
	}
	return rstring;
}




