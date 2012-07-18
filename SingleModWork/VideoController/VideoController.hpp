#ifndef VIDEOCONTROLLER_HPP_
#define VIDEOCONTROLLER_HPP_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <pthread.h>

#include "SDL/SDL.h"
#include "SDL/SDL_mutex.h"
#include "LogController.hpp"

#include <vlc/vlc.h>

//threads
static pthread_t videorefreshthread, videorenderingthread;

extern bool programRunning;

#define WIDTH 640
#define HEIGHT 480

#define VIDEOWIDTH 912
#define VIDEOHEIGHT 513

#define PLAYERSCOREWIDTH 250
#define PLAYERSCOREHEIGHT 75

#define PLAYER1X 100
#define PLAYER1Y 100

#define PLAYER2X 1370
#define PLAYER2Y 100

#define PLAYER3X 100
#define PLAYER3Y 820

#define PLAYER4X 1370
#define PLAYER4Y 820

enum videosize{
	small = 1,
	full = 2,
};


static SDL_Surface *screen, *background, *scorebackground;

struct players{
	SDL_Surface* surf;
	SDL_Rect rect;
	bool status;

};

struct ctx
{
    SDL_Surface *surf;
    SDL_mutex *mutex;
    SDL_Rect rect;
    bool status;
	int priority;
};

static struct ctx smallvideo, fullvideo;

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

		static void VideoController::PlayVideo(std::string filename, int priority, videosize vs);


	private:


		static void *lock(void *data, void **p_pixels);
		static void unlock(void *data, void *id, void *const *p_pixels);
		static void display(void *data, void *id);
		static void Play(std::string filename);

		//Logger has nothing until set
		//LogController* logger;
};


#endif /* VIDEOCONTROLLER_HPP_ */
