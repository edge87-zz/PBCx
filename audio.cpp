/*
 * audio.cpp
 *
 *  Created on: Apr 14, 2012
 *      Author: edge87
 */

#include <iostream>
#include <SFML/Audio.hpp>

#include "audio.hpp"

sf::SoundBuffer Buffer;
sf::Sound Sound;

void playTest(){

    if (!Buffer.LoadFromFile("/home/edge87/workspace/PBCx/media/sound/effect/heal.ogg"))
    {
       std::cout << "Sound failed to load\n";
    }


    Sound.SetBuffer(Buffer); // Buffer is a sf::SoundBuffer

    Sound.Play();
};
