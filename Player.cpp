#include "Player.hpp"

Player::Player(int numberOfBalls)
{
	ballsLeft = numberOfBalls;
}

Player::~Player()
{
	
}

void Player::incrementScore(int score)
{
	score = score;
}
	
bool Player::DEATH()
{
	ballsLeft--;
	return (ballsLeft == 0);
}
