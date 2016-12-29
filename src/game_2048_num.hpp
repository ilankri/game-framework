#ifndef GAME_2048_NUM_HPP
#define GAME_2048_NUM_HPP

#include "game_2048.hpp"

class Game_2048_Num : public Game_2048 {
	/* Variant with other numbers than powers of 2 */
public:
	Game_2048_Num(int height, long base=2);

private:
	const long base;
	
	virtual long random_value();
};

#endif
