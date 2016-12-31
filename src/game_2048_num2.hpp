#ifndef GAME_2048_NUM2_HPP
#define GAME_2048_NUM2_HPP

#include "game_2048.hpp"
#include <cmath>

class Game_2048_Num2 : public virtual Game_2048 {
	/* Variant with other numbers than powers of 2
	   The board can contain at the same time numbers
	   2, 3, 5 ... */
public:
	Game_2048_Num2(int height);

protected:
	virtual unsigned long long random_value() const;
};


#endif
