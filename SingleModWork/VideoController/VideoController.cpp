/*
 * currenly working on getting PlayVideo() to determin if it should play video. Then it should clean up thread if it has to. Then it should start the thread again only this time with new perameters.
 *
 * Play() will need a refit to know which (fullvideo, smallvideo) it should be playing on. Perhaps we'll pass the pointer it needs.
 *
 * Check to make sure we have to keep rebuilding the libs for VLC. Maybe we only need to re-create the player and can destroy it only.
 */

#include "VideoController.hpp"

bool VideoController::init(){
	//init SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	};

	//Setup our main screen
//	if((screen = SDL_SetVideoMode(1920, 1080, 16, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN)) == NULL) {
//		return false;
//	};

	screen = SDL_SetVideoMode(SDL_GetVideoInfo()->current_w, SDL_GetVideoInfo()->current_h, 32, SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_FULLSCREEN);

	//Get our blank screen
	blank = SDL_CreateRGBSurface(SDL_HWSURFACE, SDL_GetVideoInfo()->current_w, SDL_GetVideoInfo()->current_h, 32, 0, 0, 0, 0);
	SDL_FillRect(blank, NULL, 0x5BB135);

	//init TTF Fonts
	if (TTF_Init() < 0) {
	    // Handle error...
		return false;
	}

	////Load Fonts

	//Font files
	scorefont = TTF_OpenFontIndex("nrkis.ttf", OTHERSCORESIZE, 0);
	largescorefont = TTF_OpenFontIndex("nrkis.ttf", CURRENTSCORESIZE, 0);

	//Font Colors
	scorefontcolor= {255,255,255};
	scoreshadowcolor = {0,0,0};

	//setup  video - location, status, and build the surfaces
    smallvideo.rect.x = 504;
    smallvideo.rect.y = 283;
    smallvideo.width = 912;
    smallvideo.height = 513;
    smallvideo.status = false;
    smallvideo.priority = -1;
    smallvideo.mutex = SDL_CreateMutex();
    smallvideo.surf = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOWIDTH, VIDEOHEIGHT, 32, 0, 0, 0, 0);

    fullvideo.rect.x = 0;
    fullvideo.rect.y = 0;
    fullvideo.width = SDL_GetVideoInfo()->current_w;
    fullvideo.height = SDL_GetVideoInfo()->current_h;
    fullvideo.status = false;
    fullvideo.priority = -1;
    fullvideo.mutex = SDL_CreateMutex();
    fullvideo.surf = SDL_CreateRGBSurface(SDL_SWSURFACE, SDL_GetVideoInfo()->current_w, SDL_GetVideoInfo()->current_h, 16, 0x001f, 0x07e0, 0xf800, 0);

    //Setup our background
    //TODO Background

    scorefontcolor= {255,255,255};

	//Set Player Score board locations
	player[0].rect.x = PLAYER1X;
	player[0].rect.y = PLAYER1Y;
	player[0].surf	 = TTF_RenderText_Blended(scorefont, "999,999,999", scorefontcolor);
	player[0].status = true;
	player[0].iscurrent = false;

	player[1].rect.x = PLAYER2X;
	player[1].rect.y = PLAYER2Y;
	player[1].surf	 = TTF_RenderText_Blended(scorefont, "999,999,999", scorefontcolor);
	player[1].status = true;
	player[1].iscurrent = false;

	player[2].rect.x = PLAYER3X;
	player[2].rect.y = PLAYER3Y;
	player[2].surf	 = TTF_RenderText_Blended(scorefont, "999,999,999", scorefontcolor);
	player[2].status = true;
	player[2].iscurrent = true;

	player[3].rect.x = PLAYER4X;
	player[3].rect.y = PLAYER4Y;
	player[3].surf	 = TTF_RenderText_Blended(scorefont, "999,999,999", scorefontcolor);
	player[3].status = true;
	player[3].iscurrent = false;

	//Current Player Score board
	currentplayersb.rect.x = 10;
	currentplayersb.rect.y = 720;

	//Debug FPS placement. We're going to try to be dynamic with where we put this based on the resolution. Might be better
	// To store this information in a variable and not keep calling the function.

	fpsr.x = SDL_GetVideoInfo()->current_w - 100;
	fpsr.y = SDL_GetVideoInfo()->current_h - 100;

	SDL_Flip(screen);

	 //kick off display thread and go back
	 if(pthread_create(&videorefreshthread, NULL, RefreshDisplay, NULL)){
		 //Thread didn't launch
	 }

	 return 0;
};

void VideoController::EnablePlayerScore(int player_number){
	player[player_number - 1].status = true;
}

void VideoController::DisablePlayerScore(int player_number){
	player[player_number - 1].status = false;
}

void *VideoController::lock(void *data, void **p_pixels){
    struct ctx *ctx = static_cast<struct ctx*>(data);

    SDL_LockMutex(ctx->mutex);
    SDL_LockSurface(ctx->surf);
    *p_pixels = ctx->surf->pixels;
    return NULL; /* picture identifier, not needed here */
}

void VideoController::unlock(void *data, void *id, void *const *p_pixels){
    struct ctx *ctx = static_cast<struct ctx*>(data);

    /* VLC just rendered the video, but we can also render stuff */
    uint16_t *pixels = static_cast<uint16_t*>(*p_pixels);
    int x, y;

    for(y = 10; y < 40; y++)
        for(x = 10; x < 40; x++)
            if(x < 13 || y < 13 || x > 36 || y > 36)
                pixels[y * VIDEOWIDTH + x] = 0xffff;
            else
                pixels[y * VIDEOWIDTH + x] = 0x0;

    SDL_UnlockSurface(ctx->surf);
    SDL_UnlockMutex(ctx->mutex);

    assert(id == NULL); /* picture identifier, not needed here */
}

void VideoController::display(void *data, void *id){
    /* VLC wants to display the video */
    (void) data;
    assert(id == NULL);
}

void VideoController::PlayVideo(std::string filename, int priority, videosize vs){
	if(smallvideo.status && vs == small){
		if(priority > smallvideo.priority){
			//Kill current thread
			smallvideo.status = false;

			//reset our thread
			smallvideo.status = true;

			//Play video
			Play(filename,&smallvideo);
		}
		else{
			//Log Rejected to play small video as video with higher priority was in progress.
			return;
		}

	}

	if(smallvideo.status && vs == full){
		//kills thread
		smallvideo.status = false;

		//get ready for ours
		fullvideo.status = true;

		Play(filename, &fullvideo);

		return;
	}

	if(vs == small){
		smallvideo.status = true;
		Play(filename, &smallvideo);
		return;
	}

	fullvideo.status = true;
	Play(filename, &fullvideo);

	return;
}

void* VideoController::Play(std::string filename, ctx* ctx){
	// TODO If we're already playing and a lower priority wants to play. No.

	libvlc_instance_t *libvlc;
	libvlc_media_t *m;
	libvlc_media_player_t *mp;

	char const *vlc_argv[] =
	    {
	        "--no-xlib",
	        "--no-video-title",
	    };

	    int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);

	    //Initialise libVLC

	    libvlc = libvlc_new(vlc_argc, vlc_argv);
	    m = libvlc_media_new_path(libvlc, filename.c_str());
	    mp = libvlc_media_player_new_from_media(m);
	    libvlc_media_release(m);

	    libvlc_video_set_callbacks(mp, VideoController::lock, VideoController::unlock, VideoController::display, ctx);
	    libvlc_video_set_format(mp, "RV16", ctx->width, ctx->height, ctx->width*2);
	    //libvlc_video_set_format(mp, "RV16", VIDEOWIDTH, VIDEOHEIGHT, VIDEOWIDTH*2);
	    libvlc_media_player_play(mp);

		//Main loop

	    //Takes the player a bit of time to get "up and running" so that it reports a "1" thats its playing. So we wait till it does.
	    while(libvlc_media_player_is_playing(mp) == 0){
	    	SDL_Delay(10);
	    }

	    std::cout << "video started";
	    bool videoplaying = true;
	    while(videoplaying && ctx->status){
	    	if(libvlc_media_player_is_playing(mp) == 0){
	    		videoplaying = false;
	    	}
	    }

	    std::cout << "Video dead";
	   //Stop stream and clean up libVLC

	    libvlc_media_player_stop(mp);
	    libvlc_media_player_release(mp);
	    libvlc_release(libvlc);


	    ctx->status = false;

	    return NULL;
}

void VideoController::Reset(){

}

void *VideoController::RefreshDisplay(void* args){
	//Init
	SDL_Event event;

	SDL_Rect temprec;

	Uint32 target = SDL_GetTicks() + TICK_INTERVAL;
	int framerate, action = 0;
	std::string sframerate, ranscore;
	std::stringstream out;

	ranscore = "90,000";

//Main Looping
	while(true){
		//Blit Our background
		SDL_BlitSurface(blank, NULL, screen, NULL);

		if(fullvideo.status){
			SDL_LockMutex(fullvideo.mutex);
			SDL_BlitSurface(fullvideo.surf, NULL, screen, &fullvideo.rect);
			SDL_UnlockMutex(fullvideo.mutex);
		}

		//increment our FPS
		framerate++;

		if(target < SDL_GetTicks()){
			//display text
			//Convert Int to SS
			out.str(std::string());
			framerate *= 120;

			out << framerate;
			//Convert SS to String
			sframerate = out.str();

			FPS_SURF = TTF_RenderText_Solid(scorefont, sframerate.c_str(), scorefontcolor);

			//SDL_BlitSurface(FPS_SURF, NULL, screen, &fpsr);

			//reset frame rate and string stream
			framerate = 0;
			out.str(std::string());

			//Jump another X ms in the future
			target = SDL_GetTicks() + TICK_INTERVAL;
		}

		for(int i=0; i<4; i++){
			if(player[i].status){
				if(player[i].iscurrent == true){
					currentplayerscore = TTF_RenderText_Blended(largescorefont, "50,000", scorefontcolor);

					if (SCOREBOARDWIDTH > currentplayerscore->w){
						temprec.x = ((SCOREBOARDWIDTH - currentplayerscore->w)/2);
					}

					if (SCOREBOARDHEIGHT > currentplayerscore->h){
						temprec.y = ((SCOREBOARDHEIGHT - currentplayerscore->h)/2);
										}
					SDL_BlitSurface(currentplayerscore, NULL, screen, &temprec);
				}

				else{
					currentplayerscore = ShadowText("90,000");

					if (i == 3){
						currentplayerscore = TTF_RenderText_Solid(scorefont, "99,999", scorefontcolor);
					}

					if (PLAYERSCOREWIDTH > currentplayerscore->w){
						temprec.x = ((PLAYERSCOREWIDTH - currentplayerscore->w)/2) + player[i].rect.x;
					}

					if (PLAYERSCOREHEIGHT > currentplayerscore->h){
						temprec.y = ((PLAYERSCOREHEIGHT - currentplayerscore->h)/2) + player[i].rect.y;
					}

					SDL_BlitSurface(currentplayerscore, NULL, screen, &temprec);
				}
			}
		}

		while( SDL_PollEvent( &event ) ){
			switch(event.type){
				case SDL_QUIT:
					programRunning = false;
			        break;
				case SDL_KEYDOWN:
					action = event.key.keysym.sym;

			        if(action == SDLK_ESCAPE){
			        	programRunning = false;
			        }
			        break;
			}
		}

		//if our small video is enabled
		//render our scores to the screen
		SDL_BlitSurface(scoreboard.surf, NULL, screen, &scoreboard.rect);

		//put current player up to screen
		SDL_BlitSurface(currentplayersb.surf, NULL, screen, &currentplayersb.rect);


		SDL_BlitSurface(FPS_SURF, NULL, screen, &fpsr);
		SDL_Flip(screen);
		SDL_Delay(10);
	}
	return NULL;//Shuts the editor up. "oh you didn't return anything, you must be an ahole"
}

void VideoController::Stop(){
	void TTF_Quit();
	SDL_Quit();
};

SDL_Surface* VideoController::ShadowText(std::string score){
	SDL_Surface *final, *foreground, *shadow;
	SDL_Rect rshadow, rforeground;

	//Build our surface that we'll return. Needs Alpha
	final = SDL_AllocSurface(SDL_HWSURFACE|SDL_SRCALPHA, 200, 100, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	//Build our White Text
	foreground = TTF_RenderText_Blended(scorefont, score.c_str(), scorefontcolor);

	//Build our Black Shadow
	shadow = TTF_RenderText_Blended(scorefont, score.c_str(), scoreshadowcolor);

	//Find out offsets
	rforeground.x = (final->w - foreground->w) /2;
	rshadow.x = rforeground.x + 3;

	rforeground.y = (final->h - foreground->h) /2;
	rshadow.y = rforeground.y + 3;

	//Blit shadow with offset + center offset
	SDL_SetAlpha(shadow,0,0);
	SDL_BlitSurface(shadow, NULL, final, &rshadow);

	//Blit forground with center offset
	SDL_SetAlpha(foreground,0,0);
	SDL_BlitSurface(foreground, NULL, final, &rforeground);

	return final;

}
