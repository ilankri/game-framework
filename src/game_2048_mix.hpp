#ifndef GAME_2048_MIX_HPP
#define GAME_2048_MIX_HPP

#include "game_2048_num.hpp"
#include "game_2048_neg.hpp"
#include <cmath>

class Game_2048_Mix : public Game_2048_Num, public Game_2048_Neg {
	/* Mix of variants
	 */
	
public:
	Game_2048_Mix(int height, int base = 2);

};


#endif
