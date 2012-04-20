//Flag Definations
#define flag0	0x01	// 0000 0001
#define flag1	0x02	// 0000 0010
#define flag2	0x04	// 0000 0100
#define flag3	0x08	// 0000 1000
#define flag4	0x10	// 0001 0000
#define flag5	0x20	// 0010 0000
#define flag6	0x40	// 0100 0000
#define flag7	0x80	// 1000 0000

#define bit0(x) (x & flag0)
#define bit1(x)	(x & flag1)
#define bit2(x) (x & flag2)
#define bit3(x) (x & flag3)
#define bit4(x) (x & flag4)
#define bit5(x) (x & flag5)
#define bit6(x) (x & flag6)
#define bit7(x) (x & flag7)

//Standard Libraries
#include <iostream>

//My includes
#include "scon.h"
#include "audio.hpp"

//Library (SFML) includes
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//function prototypes
void videokiller(void);
void video_startup();
void switch_thread(void);

//global variables
sf::Window App(sf::VideoMode(800, 600, 32), "SFML Window");
unsigned char switches[8] = {(char)0};
unsigned char cabinet[2] = {(char)0};

int main (){
	int sPort = -1;
	sPort = open_port();
	sf::Sleep(2.0f);

	//video_startup(); // uncomment for FULL screen

	switch_thread();

	if (bit4(cabinet[0])){
		std::cout << "\ncabinet button hit\n" ;

	}
	else{
		std::cout << "\nfailed to see button hit\n";
	};

	switch_thread();

	while(App.IsOpened()){
		videokiller();
	};

	close(sPort);	//destroy serial connection on our way out.
	std::cout << "destroyed serial interface";
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
	};
};

void video_startup(void){
	//sets us full screen
	App.Create(sf::VideoMode(800, 600, 32), "SFML Window", sf::Style::Fullscreen);
};

void switch_thread(void){

	req_switches();

	read_switches(switches);

	req_cabinet();

	read_cabinet(cabinet);

	return;
};

