#ifndef AUDIOCONTROLLER_HPP_
#define AUDIOCONTROLLER_HPP_

#include </usr/include/SDL/SDL_mixer.h>
#include "LogController.hpp"
#include <string>
#include <map>

using namespace std;

class AudioController
{
  public:
	static AudioController* instance();
	
	void addMusic(string, string);
	
	void playMusic(string);
	
	void addSound(string, string);
	
	void playSound(string);
	
  private:
	AudioController();
	~AudioController();
	static AudioController* pinstance;
	
	map<string, Mix_Music*> music;
	
	map<string, Mix_Chunk*> sounds;
	
};


#endif /* AUDIOCONTROLLER_HPP_ */
