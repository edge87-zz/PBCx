#include "PlayerMonitor.hpp"
#include "LogController.hpp"
#include "VideoController.hpp"
#include <sstream>

using namespace std;

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
		VideoController::EnablePlayerScore(i + 1);
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
	stringstream ss;
	ss << (*currentPlayer)->getScore();
	cout << "Player " << currentPlayer - players.begin() << ": " << (*currentPlayer)->getScore() << endl;
	VideoController::UpdateScore((currentPlayer - players.begin())+1, ss.str());
}
