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
#include <string>
#include <cstdlib>
#include <cstdio>
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
void load_fonts(void);
std::string char_to_bin_string(unsigned char*, int);

//global variables
sf::RenderWindow App(sf::VideoMode(1920, 1080, 32), "SFML Window");
unsigned char switches[8] = {(char)0};
unsigned char cabinet[2] = {(char)0};

//unsigned char test[8] = {(ch	ar)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255};

//globals but shouldn't be
sf::Font MyFont;

int main (){
	int sPort = -1;
	sPort = open_port();
	sf::Sleep(3.0f);

	switch_thread();



	video_startup(); // uncomment for FULL screen
	load_fonts();

	sf::String playfieldText("a", MyFont, 18);
	sf::String cabinetText("a", MyFont, 18);

	playfieldText.Move(10.f, 200.f);
	cabinetText.Move(10.f, 250.f);

	std::string sswitches;
	std::string scabinet;

	//kick coil 20
	kick_coil(20, 100);

	while(App.IsOpened()){
		App.Clear(sf::Color(0, 0, 200));
		switch_thread();

		sswitches = "Switch bits: " + char_to_bin_string(switches, 8);
		scabinet = "Cabinet bits: "  + char_to_bin_string(cabinet, 2);

		playfieldText.SetText(sswitches);
		cabinetText.SetText(scabinet);
		App.Draw(playfieldText);
		App.Draw(cabinetText);

		videokiller();
	};

	close(sPort);	//destroy serial connection on our way out.
	std::cout << "destroyed serial interface\n";
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
	App.Create(sf::VideoMode(1920, 1080, 32), "SFML Window", sf::Style::Fullscreen);
};

void switch_thread(void){
	sf::Sleep(0.008f);

	req_switches();

	read_switches(switches);

	req_cabinet();

	read_cabinet(cabinet);

	return;
};

void load_fonts(void){
	if (!MyFont.LoadFromFile("/usr/share/cups/fonts/FreeMono.ttf")){
	    std::cout << "\n!!!!!!!!!Failed font loading\n";
	};
};

std::string char_to_bin_string(unsigned char* charbytes, int nofbytes){
	std::string rstring;

	for(int i=(nofbytes -1); i >= 0; i--){
		if(bit7(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit6(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit5(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit4(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit3(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit2(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit1(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		if(bit0(charbytes[i])){
			rstring += "1";
		}
		else{
			rstring += "0";
		};

		rstring += " ";
	};

	return rstring;
};



