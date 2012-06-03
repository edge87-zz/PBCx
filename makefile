pbcx : main.o audio.o Game.o Player.o scon.o Switch.o SwitchHandler.o
	g++ -o pbcx -lrt -lpthread -L/usr/lib/i386-linux-gnu -lSDL -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT main.o audio.o Game.o Player.o scon.o Switch.o SwitchHandler.o
	
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
  
clean :
	rm pbcx main.o audio.o Game.o Player.o scon.o Switch.o SwitchHandler.o
