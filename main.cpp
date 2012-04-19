#include "scon.h"
#include "audio.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


//function prototypes
void videokiller(void);


sf::Window App(sf::VideoMode(800, 600, 32), "SFML Window");

void video_startup(void){
	//sets us full screen
	App.Create(sf::VideoMode(800, 600, 32), "SFML Window", sf::Style::Fullscreen);
};

int main (){
	int sPort = -1;
	sPort = open_port();

	if (sPort){
		std::cout << "Serial Port is Open and Ready";
	};

	video_startup();


	while(App.IsOpened()){
		videokiller();
	};

	close(sPort);	//destroy serial connection on our way out.

	return 0;
};

void videokiller(void){
	App.Display();
	sf::Event Event;
	while (App.GetEvent(Event))
	{
	    // Window closed
	    if (Event.Type == sf::Event::Closed){
	        App.Close();
	    };
	    // Escape key pressed
	    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)){
	    	App.Close();
	    };
	}
};


