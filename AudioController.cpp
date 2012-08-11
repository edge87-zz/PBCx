#include "AudioController.hpp"
#include </usr/include/SDL/SDL_mixer.h>
#include <stddef.h>

AudioController* AudioController::pinstance = NULL;

AudioController* AudioController::instance()
{
	if(pinstance == NULL)
	{
		pinstance = new AudioController();
	}
	return pinstance;
}
	
void AudioController::addMusic(string name, string filename)
{
	music[name] = Mix_LoadMUS(filename.c_str());
}

void AudioController::playMusic(string name)
{
	Mix_HaltMusic();
	Mix_PlayMusic(music[name], -1);
}

void AudioController::addSound(string name, string filename)
{
	sounds[name] = Mix_LoadWAV(filename.c_str());
}

void AudioController::playSound(string name)
{
	Mix_PlayChannel(-1, sounds[name], 0);
}

AudioController::AudioController()
{
	int audio_rate = 32000;
	Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	int audio_channels = 2;
	int audio_buffers = 4096;	
		
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
		LogController::instance()->info("Audio Not Initialized");		
	}
}

AudioController::~AudioController()
{
	Mix_CloseAudio();
}

