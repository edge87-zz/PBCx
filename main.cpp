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
#include "sprite.hpp"

//Library (SFML) includes
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//function prototypes
void videokiller(void);
void read_switches_thread(void*);
void load_fonts(void);
std::string char_to_bin_string(unsigned char*, int);

//global variables
sf::RenderWindow App(sf::VideoMode(1920, 1080, 32), "Team Heck", sf::Style::Fullscreen);
unsigned char switches[8] = {(char)0};
unsigned char cabinet[2] = {(char)0};
//unsigned char test[8] = {(ch	ar)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255,(char)255};

//Mutex flags
sf::Mutex playfieldSwitchesM;
sf::Mutex cabinetSwitchesM;
sf::Mutex serialPortM;

//Fonts
sf::Font mono;
sf::Font solstice;

//Global Sprites
sf::Sprite sBackground;

//Video Stuff

int main (){
	App.Clear(sf::Color(0, 0, 200));
	App.Display();

	int sPort = -1;
	sPort = open_port();


	sf::Thread tReadSwitch(&read_switches_thread);

	sf::Image background;

	background.LoadFromFile("/home/teamheck/exec/media/image/background.png");
	sBackground.SetImage(background);
	sBackground.SetPosition(0.f, 0.f);
	App.Draw(sBackground);


	tReadSwitch.Launch();

	load_fonts();

	sf::String playfieldText("a", mono, 18);
	sf::String cabinetText("a", solstice, 18);

	playfieldText.Move(10.f, 950.f);
	cabinetText.Move(10.f, 1000.f);

	std::string sswitches;
	std::string scabinet;

	while(App.IsOpened()){
		App.Clear(sf::Color(0, 0, 200));

		sswitches = "Switch bits: " + char_to_bin_string(switches, 8);
		scabinet = "Cabinet bits: "  + char_to_bin_string(cabinet, 2);

		playfieldText.SetText(sswitches);
		cabinetText.SetText(scabinet);
		App.Draw(sBackground);
		App.Draw(playfieldText);
		App.Draw(cabinetText);

		videokiller();
	};

	//Destroy our Threads
	tReadSwitch.Terminate();

	//Destroy serial connection on our way out.
	close(sPort);

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

void read_switches_thread(void * none){
	sf::Sleep(2.0f);	//sleep because board has too stablize
	while(true){
		serialPortM.Lock();
		read_switches();
		serialPortM.Unlock();
	};
};

void load_fonts(void){
	if (!mono.LoadFromFile("/home/teamheck/exec/media/font/mono.ttf")){
	    std::cout << "Failed to load mono font\n";
	};

	if (!solstice.LoadFromFile("/home/teamheck/exec/media/font/solsticeofsuffering.ttf")){
	    std::cout << "Failed to load solstice font.\n";
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



