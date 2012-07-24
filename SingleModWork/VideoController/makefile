Video : main.o LogController.o VideoController.o 
	g++ -o Video main.o LogController.o VideoController.o -lpthread $(shell sdl-config --libs) $(shell sdl-config --cflags) -lSDL_ttf -lvlc
	
main.o : main.cpp
	g++ -c -g main.cpp
		
LogController.o : LogController.cpp LogController.hpp
	g++ -c  -g LogController.cpp
	
VideoController.o : VideoController.cpp VideoController.hpp
	g++ -c  -g VideoController.cpp
	
clean :
	rm Video main.o LogController.o VideoController.o
