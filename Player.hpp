#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player
{
public:	
	Player(int numberOfBalls);
	
	~Player();
	
	void incrementScore(int score);
	
	bool DEATH();
	
private:
	int score;
	
	int ballsLeft;
};

#endif //PLAYER_HPP
