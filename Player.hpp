#ifndef PLAYER_HPP_
#define PLAYER_HPP_

class Player{

	public:
		// \Constructor
		Player();

		// \Destructor
		~Player();

		// \Adds points to the players score
		void add_score(int points);

		// \Returns Player's Score
		unsigned int getScore(void);


	private:

		// \Player's Score
		unsigned int score;


};


#endif /* PLAYER_HPP_ */
