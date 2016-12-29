#ifndef GAME_2048_NEG_HPP
#define GAME_2048_NEG_HPP

#include "game_2048.hpp"

class Game_2048_Neg : public Game_2048 {
	/* Variant with negative numbers */
public:
	Game_2048_Neg(int height, int width);

private:
	virtual Square_2048 random_square();
};

#endif