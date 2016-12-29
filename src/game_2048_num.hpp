#ifndef GAME_2048_NUM_HPP
#define GAME_2048_NUM_HPP

#include "game_2048.hpp"
#include <cmath>

class Game_2048_Num : virtual public Game_2048 {
	/* Variant with other numbers than powers of 2
	   The user can choose his base, and the board 
	   contains only numbers of this base
	 */
public:
	Game_2048_Num(int height, int base = 2);

protected:
	const long base;
	
	virtual long random_value();
};


#endif
