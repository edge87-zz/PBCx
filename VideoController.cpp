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

	screen = SDL_SetVideoMode(SDL_GetVideoInfo()->current_w, SDL_GetVideoInfo()->current_h, 32, SDL_DOUBLEBUF|SDL_HWSURFACE);

	//Get our blank screen
	blank = SDL_CreateRGBSurface(SDL_HWSURFACE, SDL_GetVideoInfo()->current_w, SDL_GetVideoInfo()->current_h, 32, 0, 0, 0, 0);
	SDL_FillRect(blank, NULL, 0x5BB135);

	//init TTF Fonts
	if (TTF_Init() < 0) {
	    // Handle error...
		return false;
	}

	////Setup Video Libs
	char const *vlc_argv[] =
	    {
	        "--no-xlib",
	        "--no-video-title",
	    };

	int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);

	//Initialise libVLC

	libvlc = libvlc_new(vlc_argc, vlc_argv);

	mp = NULL;

	////Load Fonts

	//Font files
	scorefont = TTF_OpenFontIndex("nrkis.ttf", OTHERSCORESIZE, 0);
	largescorefont = TTF_OpenFontIndex("nrkis.ttf", CURRENTSCORESIZE, 0);

	//Font Colors
	scorefontcolor= {255,255,255};
	scoreshadowcolor = {0,0,0};

    fullvideo.rect.x = 0;
    fullvideo.rect.y = 0;
    fullvideo.width = SDL_GetVideoInfo()->current_w;
    fullvideo.height = SDL_GetVideoInfo()->current_h;
    fullvideo.status = false;
    fullvideo.priority = -1;
    fullvideo.mutex = SDL_CreateMutex();
    fullvideo.surf = SDL_CreateRGBSurface(SDL_SWSURFACE, SDL_GetVideoInfo()->current_w, SDL_GetVideoInfo()->current_h, 16, 0x001f, 0x07e0, 0xf800, 0);

	//Set Player Score board locations
	player[0].rect.x = PLAYER1X;
	player[0].rect.y = PLAYER1Y;
	player[1].rect.x = PLAYER2X;
	player[1].rect.y = PLAYER2Y;
	player[2].rect.x = PLAYER3X;
	player[2].rect.y = PLAYER3Y;
	player[3].rect.x = PLAYER4X;
	player[3].rect.y = PLAYER4Y;

	for(int i=0; i<4; i++){
		player[i].surf	 = VideoController::ShadowText("0");
		player[i].status = false;
		player[i].iscurrent = false;
	}

	//Current Player Score board
	currentplayersb.rect.x = 10;
	currentplayersb.rect.y = 720;

	//Debug FPS placement. We're going to try to be dynamic with where we put this based on the resolution. Might be better
	// To store this information in a variable and not keep calling the function.

	fpsr.x = SDL_GetVideoInfo()->current_w - 100;
	fpsr.y = SDL_GetVideoInfo()->current_h - 100;


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

    SDL_UnlockSurface(ctx->surf);
    SDL_UnlockMutex(ctx->mutex);

    assert(id == NULL); /* picture identifier, not needed here */
}

void VideoController::display(void *data, void *id){
    /* VLC wants to display the video */
    (void) data;
    assert(id == NULL);
}

void VideoController::PlayVideo(std::string filename, int priority){

	if (fullvideo.status && priority > fullvideo.priority){
		fullvideo.status = false;
	    libvlc_media_player_stop(mp);
	    libvlc_media_player_release(mp);

		 if(pthread_create(&videorenderingthread, NULL, Play, NULL)){
			 //Thread didn't launch
		 }

	    //Play thread
	}

	if (fullvideo.status){
		//Log we aren't playing this file because the priority was lower
		return;
	}

	fullvideo.status = true;

	fsname = filename;


	 if(pthread_create(&videorenderingthread, NULL, Play, NULL)){
		 //Thread didn't launch
	 }

	return;
}

void* VideoController::Play(void* data){
	m = libvlc_media_new_path(libvlc, fsname.c_str());
	mp = libvlc_media_player_new_from_media(m);

	libvlc_video_set_callbacks(mp, VideoController::lock, VideoController::unlock, VideoController::display, &fullvideo);
	libvlc_video_set_format(mp, "RV16", fullvideo.width, fullvideo.height, fullvideo.width*2);

	libvlc_media_player_play(mp);
	libvlc_media_release(m);

	SDL_Delay(1000);
	while(libvlc_media_player_is_playing(mp) > 0 ){

	}

	fullvideo.status = false;
	fullvideo.priority = 0;

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
				SDL_BlitSurface(player[i].surf, NULL, screen, &player[i].rect);
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
	foreground = TTF_RenderText_Solid(scorefont, score.c_str(), scorefontcolor);

	//Build our Black Shadow
	shadow = TTF_RenderText_Solid(scorefont, score.c_str(), scoreshadowcolor);

	//Find out offsets
	rforeground.x = (final->w - foreground->w) /2;
	rshadow.x = rforeground.x + 3;

	rforeground.y = (final->h - foreground->h) /2;
	rshadow.y = rforeground.y + 3;

	//Blit shadow with offset + center offset
	//SDL_SetAlpha(shadow,0,0);
	SDL_BlitSurface(shadow, NULL, final, &rshadow);

	//Blit forground with center offset
	//SDL_SetAlpha(foreground,0,0);
	SDL_BlitSurface(foreground, NULL, final, &rforeground);

	return final;

}

void VideoController::UpdateScore(int playernum, std::string score){
	//index offset
	playernum--;

	//Check inputs
	if(playernum > 4 || playernum <= 0){
		//Handle this error..
		return;
	}

	//disable the player's score
	VideoController::DisablePlayerScore(playernum +1);

	//Find a clever way of knowing how man characters we're expected to kick out.

	SDL_Surface * temp;

	//build our text
	temp = VideoController::ShadowText(score);

	//free surface
	SDL_FreeSurface(player[playernum].surf);

	//assign surface
	player[playernum].surf = temp;

	//reenable player's score
	VideoController::EnablePlayerScore(playernum +1);

	//leave
	return;
}
