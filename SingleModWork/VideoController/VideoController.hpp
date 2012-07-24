#ifndef VIDEOCONTROLLER_HPP_
#define VIDEOCONTROLLER_HPP_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <pthread.h>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mutex.h"
#include "LogController.hpp"

#include <vlc/vlc.h>

//threads
static pthread_t videorefreshthread, videorenderingthread;

//We set this to false when SDL receives a escape key, or the window is closed. This should STOP our application too
extern bool programRunning;

//Small Video WxH
#define VIDEOWIDTH 912
#define VIDEOHEIGHT 513

#define PLAYERSCOREWIDTH 470
#define PLAYERSCOREHEIGHT 110

#define SCOREBOARDWIDTH 1920
#define SCOREBOARDHEIGHT 480

#define CURRENTPLAYERWIDTH 1900
#define CURRENTPLAYERHEIGHT 270

//Play 1 - 4 (x,y) grid location on screen. Set top left corner where you want the square to start
#define PLAYER1X 10
#define PLAYER1Y 10

#define PLAYER2X 1440
#define PLAYER2Y 10

#define PLAYER3X 10
#define PLAYER3Y 360

#define PLAYER4X 1440
#define PLAYER4Y 360

//used for selecting a small screen to play a video on or full screen
enum videosize{
	small = 1,
	full = 2,
};

//Fonts
// Score Fonts =
static TTF_Font* scorefont, *largescorefont;
static SDL_Color scorefontcolor;

//Our surfaces.
// screen = main surface that we flip
// background = what is the first layer applied and over written with other surfaces.
// scorebackground = the background image applied to score zones each time around to remove text reminents

static SDL_Surface *screen, *background, *smallplayerscore, *currentplayerscore;

// Keep the players scores and locations and everything sane and stored here.
struct players{
	SDL_Surface* surf;
	SDL_Rect rect;
	bool status;
	bool iscurrent;
};

//Video rendindering surfaces.
struct ctx
{
    SDL_Surface *surf;
    SDL_mutex *mutex;
    SDL_Rect rect;
    bool status;
	int priority;
	pthread_t thread;
	int width;
	int height;
};

static struct ctx smallvideo, fullvideo, scoreboard, currentplayersb;

static struct players player[4];

class VideoController{
	public:

		// Setups up video and all its stuff.
		static bool init();

		// Destroys Video
		static bool destroy();

		//\ brief This will reset our thread static variables and call start afterwards.
		static void Reset();

		static void EnablePlayerScore(int player_number);
		static void DisablePlayerScore(int player_number);

		static void SetScore(int player_number);

		//\ Constantly refreshing our display. This is the threaded part
		static void* RefreshDisplay(void* args);

		static void PlayVideo(std::string filename, int priority, videosize vs);

		//Stops all threads, unloads all resources
		static void Stop();


	private:


		static void *lock(void *data, void **p_pixels);
		static void unlock(void *data, void *id, void *const *p_pixels);
		static void display(void *data, void *id);
		static void* Play(std::string filename, videosize vs);

		//Logger has nothing until set
		//LogController* logger;
};


#endif /* VIDEOCONTROLLER_HPP_ */
