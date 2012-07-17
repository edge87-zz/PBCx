Video : main.o LogController.o VideoController.o 
	g++ -o Video main.o LogController.o VideoController.o -lpthread $(shell sdl-config --libs) $(shell sdl-config --cflags) -lSDL_ttf -lvlc
	
main.o : main.cpp
	g++ -c main.cpp
		
LogController.o : LogController.cpp LogController.hpp
	g++ -c LogController.cpp
	
VideoController.o : VideoController.cpp VideoController.hpp
	g++ -c VideoController.cpp
	
clean :
	rm Video main.o LogController.o VideoController.o