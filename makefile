pbcx : main.o AudioController.o BallDrain.o Player.o PlayerMonitor.o scon.o Switch.o SwitchHandler.o WikiMode.o LogController.o LightController.o VideoController.o SerialController.o
	g++ -o pbcx main.o AudioController.o BallDrain.o Player.o PlayerMonitor.o scon.o Switch.o SwitchHandler.o WikiMode.o LogController.o LightController.o VideoController.o SerialController.o -lrt -lpthread $(shell sdl-config --libs) $(shell sdl-config --cflags) -lSDL_ttf -lvlc -lSDL_mixer
	
main.o : main.cpp
	g++ -c main.cpp

BallDrain.o : BallDrain.cpp BallDrain.hpp
	g++ -c BallDrain.cpp

AudioController.o : AudioController.cpp AudioController.hpp	
	g++ -c AudioController.cpp
	
Player.o : Player.cpp Player.hpp
	g++ -c Player.cpp
	
PlayerMonitor.o : PlayerMonitor.cpp PlayerMonitor.hpp
	g++ -c PlayerMonitor.cpp
	
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
	
LightController.o : LightController.cpp LightController.hpp
	g++ -c LightController.cpp
	
LogController.o : LogController.cpp LogController.hpp
	g++ -c LogController.cpp
	
SerialController.o : SerialController.cpp SerialController.hpp
	g++ -c SerialController.cpp
	
VideoController.o : VideoController.cpp VideoController.hpp
	g++ -c VideoController.cpp
	
clean :
	rm pbcx main.o Game.o Player.o scon.o Switch.o SwitchHandler.o LogController.o SerialController.o VideoController.o AudioController.o
