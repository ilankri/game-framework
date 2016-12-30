#ifndef GAME_2048_MIX_HPP
#define GAME_2048_MIX_HPP

#include "game_2048_num.hpp"
#include "game_2048_neg.hpp"
#include "game_2048_mult.hpp"
#include <cmath>

class Game_2048_Mix : public Game_2048_Num,
		      public Game_2048_Neg,
		      public Game_2048_Mult
{
	/* Mix of variants
	 */

protected:
	virtual Square_2048 random_square() const;
	
public:
	Game_2048_Mix(int height, int base = 2);

};


#endif
