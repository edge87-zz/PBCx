/*
 * audio.cpp
 *
 *  Created on: Apr 14, 2012
 *      Author: edge87
 */

#include <iostream>
#include <SFML/Audio.hpp>

#include "audio.hpp"

sf::SoundBuffer Buffer1;
sf::SoundBuffer Buffer2;


sf::Sound Sound;

void playTest(){
	Sound.Stop();
    if (!Buffer1.LoadFromFile("/home/teamheck/exec/media/sound/effect/boomattack.oga"))
    {
       std::cout << "Sound failed to load\n";
    }


    Sound.SetBuffer(Buffer1); // Buffer is a sf::SoundBuffer

    Sound.Play();
};

void scream(){
	Sound.Stop();

    if (!Buffer2.LoadFromFile("/home/teamheck/exec/media/sound/effect/wilhelm.ogg"))
    {
       std::cout << "Sound failed to load\n";
    }


    Sound.SetBuffer(Buffer2); // Buffer is a sf::SoundBuffer

    Sound.Play();


};
