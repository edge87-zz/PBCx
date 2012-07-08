pbcx : main.o audio.o Game.o Player.o scon.o Switch.o SwitchHandler.o WikiMode.o LogController.o SerialController.o VideoController.o
	g++ -o pbcx main.o audio.o Game.o Player.o scon.o Switch.o SwitchHandler.o WikiMode.o LogController.o SerialController.o VideoController.o -lrt -lpthread $(shell sdl-config --libs) $(shell sdl-config --cflags) -lSDL_ttf 
	
main.o : main.cpp
	g++ -c main.cpp
	
Game.o : Game.cpp Game.hpp
	g++ -c Game.cpp
	
Player.o : Player.cpp Player.hpp
	g++ -c Player.cpp
	
scon.o : scon.cpp scon.hpp
	g++ -c scon.cpp
	
Switch.o : Switch.cpp Switch.hpp
	g++ -c Switch.cpp
	
SwitchHandler.o : SwitchHandler.cpp SwitchHandler.hpp
	g++ -c SwitchHandler.cpp

Event.o : Event.cpp Event.hpp
	g++ -c Event.cpp
  
WikiMode.o : WikiMode.cpp WikiMode.hpp
	g++ -c WikiMode.cpp
	
LogController.o : LogController.cpp LogController.hpp
	g++ -c LogController.cpp
	
SerialController.o : SerialController.cpp SerialController.hpp
	g++ -c SerialController.cpp
	
VideoController.o : VideoController.cpp VideoController.hpp
	g++ -c VideoController.cpp
	
clean :
	rm pbcx main.o audio.o Game.o Player.o scon.o Switch.o SwitchHandler.o LogController.o SerialController.o VideoController.o
