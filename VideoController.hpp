
#ifndef VIDEOCONTROLLER_HPP_
#define VIDEOCONTROLLER_HPP_

//STD Libs
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string>

//Libs
#include <SDL/SDL.h>
#include <SDL/SDL_mutex.h>
#include <vlc/vlc.h>

//Define
#define VIDEOWIDTH 320
#define VIDEOHEIGHT 240
#define HEIGHT 1080
#define WIDTH 1920

class VideoController{
	public:
		VideoController();
		~VideoController();

		void PlayVideo(std::string filename, SDL_Surface *screen);

	private:
		struct ctx
		{
		    SDL_Surface *surf;
		    SDL_mutex *mutex;
		};

		void lock(void *data, void **p_pixels);

		void unlock(void *data, void *id, void *const *p_pixels);

		void display(void *data, void *id);




};




#endif /* VIDEOCONTROLLER_HPP_ */
