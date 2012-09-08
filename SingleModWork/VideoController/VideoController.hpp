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
#include <sstream>

#define TICK_INTERVAL 500 // half a second

//threads
static pthread_t videorefreshthread, videorenderingthread;

//We set this to false when SDL receives a escape key, or the window is closed. This should STOP our application too
extern bool programRunning;

//Small Video WxH
#define VIDEOWIDTH 912
#define VIDEOHEIGHT 513

#define PLAYERSCOREWIDTH 470
#define PLAYERSCOREHEIGHT 110

//Defines where the current player score goes
#define SCOREBOARDWIDTH 1200
#define SCOREBOARDHEIGHT 1400

//helps define where the other player scores go
#define CURRENTPLAYERWIDTH 1900
#define CURRENTPLAYERHEIGHT 270

//Play 1 - 4 (x,y) grid location on screen. Set top left corner where you want the square to start
#define PLAYER1X 10
#define PLAYER1Y 600

#define PLAYER2X 700
#define PLAYER2Y 600

#define PLAYER3X 10
#define PLAYER3Y 700

#define PLAYER4X 700
#define PLAYER4Y 700

//For our bigger screen
//#define OTHERSCORESIZE 100
//#define CURRENTSCORESIZE 300

//Development laptop
#define OTHERSCORESIZE 50
#define CURRENTSCORESIZE 90

//Fonts
// Score Fonts =
static TTF_Font* scorefont, *largescorefont;
static SDL_Color scorefontcolor, scoreshadowcolor;

//Our surfaces.
// screen = main surface that we flip
// background = what is the first layer applied and over written with other surfaces.
// scorebackground = the background image applied to score zones each time around to remove text reminents

static SDL_Surface *screen, *background, *currentplayerscore, *FPS_SURF, *blank;

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

static SDL_Rect fpsr;

static struct ctx fullvideo, scoreboard, currentplayersb;

static struct players player[4];

//Video Player Libs
static libvlc_instance_t *libvlc;
static libvlc_media_t *m;
static 	libvlc_media_player_t *mp;

class VideoController{
	public:

		// Setups up video and all its stuff.
		static bool init();

		// Destroys Video
		static bool destroy();

		static void UpdateScore(int player, std::string score);

		static void EnablePlayerScore(int player_number);
		static void DisablePlayerScore(int player_number);

		static void SetScore(int player_number);

		//\ Constantly refreshing our display. This is the threaded part
		static void RefreshDisplay();

		static void PlayVideo(std::string filename, int priority);

		//Stops all threads, unloads all resources
		static void Stop();

		//\ Render us some shadowed text. Return SDL_Surface* and ask for nothing but a string
		static SDL_Surface* ShadowText(std::string);

	private:
		static void *lock(void *data, void **p_pixels);
		static void unlock(void *data, void *id, void *const *p_pixels);
		static void display(void *data, void *id);
		static void* Play(std::string filename, ctx* ctx);
};


#endif /* VIDEOCONTROLLER_HPP_ */
