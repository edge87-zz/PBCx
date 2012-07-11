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

#include <vlc/vlc.h>

#define WIDTH 640
#define HEIGHT 480

#define VIDEOWIDTH 320
#define VIDEOHEIGHT 240

class VideoController{
	public:
		VideoController();
		~VideoController();

		void Play(std::string filename, SDL_Surface *screen);

	private:
		struct ctx
		{
		    SDL_Surface *surf;
		    SDL_mutex *mutex;
		};

		static void *lock(void *data, void **p_pixels);
		static void unlock(void *data, void *id, void *const *p_pixels);
		static void display(void *data, void *id);



};


#endif /* VIDEOCONTROLLER_HPP_ */
