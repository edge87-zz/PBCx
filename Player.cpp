

#include "Player.hpp"

Player::Player(void){
	score = 0;
};

Player::~Player(){
	//nothing really to destroy or clean up
};

void Player::add_score(int points){
	score += points;
};

unsigned int Player::getScore(void){
	return score;
};









