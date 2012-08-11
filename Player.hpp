#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player
{
public:	
	Player(int numberOfBalls);
	
	~Player();
	
	int getScore();
	
	void incrementScore(int score);
	
	bool DEATH();
	
private:
	int score;
	
	int ballsLeft;
};

#endif //PLAYER_HPP
