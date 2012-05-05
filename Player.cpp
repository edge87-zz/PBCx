#include "Player.hpp"

Player::Player(void){
	score = 0;
};

void Player::add_score(int points){
	score += points;
};

unsigned int Player::get_score(void){
	return score;
};









