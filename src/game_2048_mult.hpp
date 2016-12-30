#ifndef GAME_2048_MULT_HPP
#define GAME_2048_MULT_HPP

#include "game_2048.hpp"
#include <cmath>

class Game_2048_Mult : public virtual Game_2048 {
	/* Variant with x2 squares
	 */
public:
	Game_2048_Mult(int height);

protected:
	virtual Square_2048 random_square() const;
};


#endif
