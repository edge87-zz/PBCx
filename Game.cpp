#include "Game.hpp"

Game::Game(){
	ball = 0; // \ We set this to zero because when the game starts it will add the first ball.
};

Game::~Game(){

};

void Game::ballStart(){
	ball += 1;	// \ Add 1 to the ball as we start.
};

void Game::ballResume(){
	//Play bonus held animation
	//Play Modes held animation

	//subtract an extra ball

};

void Game::ballDrain(){
	//Ball Save?
		//Play ball save animation
		//exit this method here and now do not jump to ballResume()

	//Check for extra ball
		//Jump to ballResume

	//End Current Modes

	//Calculate Bonus's

	bool highscore = false;

	// \ Check if this was our 3rd and final ball
	if(ball == 3 ){
		// \Check for high score
		//highscore = Game::highScore(//Player's High Score unsigned int goes here); // \Don't know where player object will be.

	};
};

bool Game::highScore(unsigned int score){



	return false;
};
