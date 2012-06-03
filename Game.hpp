#ifndef GAME_HPP_
#define GAME_HPP_

#include "SwitchObserver.hpp"
#include "Player.hpp"
#include <vector>

class Game : public SwitchObserver
{
public:

	// \Game Constructor
	Game(void);

	// \Game Destructor
	~Game();

	// \Starts the first ball. Adds +1 to ball, starts random music, etc.
	void ballStart();

	// \Handles starting the SAME player again on an extra ball, or ball save. Keeps modes going.
	void ballResume();

	// \Handles when the Ball Drains. Should Check for extra ball, clean up currnet modes.
	void ballDrain();

	// \When the game ends lets check if it was a high score and get the player's Name. ::FUTURE FEATURE:: Get Username from ID Card.
	// \If high score return true.
	bool highScore(unsigned int);

  void resetPlayers();
  
  virtual void notify(int switchNumber);
  
  void incrementScore(int scoreAddition);
private:  
  
  void nextPlayer();
  
	// \Player's Current Ball. Starts on zero when the ball is launched it goes to one.
	int ball;
  
  int m_numOfPlayers;
  
  std::vector<Player*>::iterator m_currentPlayer;
  
  std::vector<Player*> m_players;
};


#endif /* GAME_HPP_ */
