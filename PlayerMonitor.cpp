#include "PlayerMonitor.hpp"
#include "LogController.hpp"

PlayerMonitor* PlayerMonitor::pinstance = NULL;

PlayerMonitor* PlayerMonitor::instance()
{
	if(pinstance == NULL)
	{
		pinstance = new PlayerMonitor;
	}
	return pinstance;
}

PlayerMonitor::PlayerMonitor() : currentPlayer(NULL)
{
}

PlayerMonitor::~PlayerMonitor()
{
}

void PlayerMonitor::resetGame(int numberOfPlayers, int numberOfBalls)
{
	players.clear();
	for(int i = 0; i < numberOfPlayers; i++)
	{
		players.push_back(new Player(numberOfBalls));
	}
	currentPlayer = players.begin();
}

bool PlayerMonitor::changePlayer()
{
	currentPlayer++;
	if(currentPlayer == players.end())
	{
		currentPlayer = players.begin();
	}
}

void PlayerMonitor::incrementScore(int score)
{
	(*currentPlayer)->incrementScore(score);
}
