#ifndef PLAYER_HPP_
#define PLAYER_HPP_

class Player{

	public:
		Player();

		void add_score(int points);


		unsigned int get_score(void);


	private:
		unsigned int score;


};


#endif /* PLAYER_HPP_ */
