#include "Game.hpp"

namespace
{
  const int BallDrain = 100; 
}

Game::Game(){
	ball = 0; // \ We set this to zero because when the game starts it will add the first ball.
  m_numOfPlayers = 1;
  resetPlayers();
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

void Game::resetPlayers()
{
  m_players.clear();
  for(int i = 0; i < m_numOfPlayers; i++)
  {
    m_players.push_back(new Player());
  }
}

bool Game::highScore(unsigned int score){



	return false;
};

void Game::incrementScore(int scoreAddition)
{
  (*m_currentPlayer)->add_score(scoreAddition);
}

void Game::nextPlayer()
{
  m_currentPlayer++;
  if(m_currentPlayer == m_players.end())
  {
    m_currentPlayer = m_players.begin();
  }
}
void Game::notify(int switchNumber)
{
  (*m_currentPlayer)->add_score(100);
  switch(switchNumber)
  {
    // ball drain stuff
    case BallDrain:
      ball++;
      nextPlayer();
      break;
    default:
      break;
  }
}
