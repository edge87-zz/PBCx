pbcx : main.o AudioController.o BallDrain.o Player.o PlayerMonitor.o Switch.o SwitchHandler.o WikiMode.o LogController.o LightController.o VideoController.o SerialController.o
	g++ -o pbcx -g main.o AudioController.o BallDrain.o Player.o PlayerMonitor.o Switch.o SwitchHandler.o WikiMode.o LogController.o LightController.o VideoController.o SerialController.o -lrt -lpthread $(shell sdl-config --libs) $(shell sdl-config --cflags) -lSDL_ttf -lvlc -lSDL_mixer
	
main.o : main.cpp
	g++ -c -g main.cpp

BallDrain.o : BallDrain.cpp BallDrain.hpp
	g++ -c -g BallDrain.cpp

AudioController.o : AudioController.cpp AudioController.hpp	
	g++ -c -g AudioController.cpp
	
Player.o : Player.cpp Player.hpp
	g++ -c -g Player.cpp
	
PlayerMonitor.o : PlayerMonitor.cpp PlayerMonitor.hpp
	g++ -c -g PlayerMonitor.cpp
	
Switch.o : Switch.cpp Switch.hpp
	g++ -c -g Switch.cpp
	
SwitchHandler.o : SwitchHandler.cpp SwitchHandler.hpp
	g++ -c -g SwitchHandler.cpp

Event.o : Event.cpp Event.hpp
	g++ -c -g Event.cpp
  
WikiMode.o : WikiMode.cpp WikiMode.hpp
	g++ -c -g WikiMode.cpp
	
LightController.o : LightController.cpp LightController.hpp
	g++ -c -g LightController.cpp
	
LogController.o : LogController.cpp LogController.hpp
	g++ -c -g LogController.cpp
	
SerialController.o : SerialController.cpp SerialController.hpp
	g++ -c -g SerialController.cpp
	
VideoController.o : VideoController.cpp VideoController.hpp
	g++ -c -g VideoController.cpp
	
clean :
	rm pbcx main.o Player.o scon.o Switch.o SwitchHandler.o LogController.o SerialController.o VideoController.o AudioController.o
