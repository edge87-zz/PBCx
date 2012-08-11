#include "Player.hpp"

Player::Player(int numberOfBalls)
{
	ballsLeft = numberOfBalls;
}

Player::~Player()
{
	
}

int Player::getScore()
{
	return score;
}

void Player::incrementScore(int thescore)
{
	score = thescore;
}
	
bool Player::DEATH()
{
	ballsLeft--;
	return (ballsLeft == 0);
}
