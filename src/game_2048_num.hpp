#ifndef GAME_2048_NUM_HPP
#define GAME_2048_NUM_HPP

#include "game_2048.hpp"

class Game_2048_Num : public Game_2048 {
	/* Variant with other numbers than powers of 2 */
public:
	Game_2048_Num(int height, int width);

private:
	virtual int random_value();
};

#endif
