#include "player.hpp"

class player{

	public:
		void add_score(int points){
			score += points;
		};

		unsigned int get_score(void){
			return score;
		};

	private:
		unsigned int score;


};



