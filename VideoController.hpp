#ifndef VIDEOCONTROLLER_HPP_
#define VIDEOCONTROLLER_HPP_

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_mutex.h"
#include "LogController.hpp"

#include <vlc/vlc.h>

#define WIDTH 640
#define HEIGHT 480

#define VIDEOWIDTH 320
#define VIDEOHEIGHT 240

class VideoController{
	public:
		VideoController(LogController *pnt, SDL_Surface *scr);
		~VideoController();

		void Play(std::string filename);

	private:
		struct ctx
		{
		    SDL_Surface *surf;
		    SDL_mutex *mutex;
		};

		static void *lock(void *data, void **p_pixels);
		static void unlock(void *data, void *id, void *const *p_pixels);
		static void display(void *data, void *id);

		//Logger has nothing until set
		LogController* logger;

		//Our GOOD surface
		SDL_Surface * screen;


};


#endif /* VIDEOCONTROLLER_HPP_ */
