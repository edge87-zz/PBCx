#ifndef PLAYERMONITOR_HPP
#define PLAYERMONITOR_HPP

#include <vector>
#include "LogController.hpp"
#include "Player.hpp"

using namespace std;

class PlayerMonitor
{
public:
	static PlayerMonitor* instance();
	
	void resetGame(int numberOfPlayers, int numberOfBalls);
	
	bool changePlayer();
	
	void incrementScore(int score);
	
private:
	PlayerMonitor();

	~PlayerMonitor();

	static PlayerMonitor* pinstance;
	
	vector<Player*> players;
	
	vector<Player*>::iterator currentPlayer;
};

#endif //PLAYERMONITOR_HPP
