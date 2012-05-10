pbcx : main.o audio.o Game.o Player.o scon.o Switch.o SwitchHandler.o
	gcc -o -lrt -lpthread pbcx main.o audio.o Game.o Player.o scon.o Switch.o SwitchHandler.o
	
main.o : main.cpp
	gcc -c main.cpp
	
Game.o : Game.cpp Game.hpp
	gcc -c Game.cpp
	
Player.o : Player.cpp Player.hpp
	gcc -c Player.cpp
	
scon.o : scon.cpp scon.hpp
	gcc -c scon.cpp
	
Switch.o : Switch.cpp Switch.hpp
	gcc -c Switch.cpp
	
SwitchHandler.o : SwitchHandler.cpp SwitchHandler.hpp
	gcc -c SwitchHandler.cpp

clean :
	rm pbcx main.o audio.o Game.o Player.o scon.o Switch.o SwitchHandler.o