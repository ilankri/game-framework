#include "game_2048_neg.hpp"

Game_2048_Neg::Game_2048_Neg(int height, int width) :
	Game_2048(height, width)
{
	
}


Square_2048 Game_2048_Neg::random_square()
{
	int val = random_value();
	Square_2048_action action;
	int sgn= rand() % 2;
	if (sgn)
		action = Square_2048_action::none;
	else action = Square_2048_action::neg;
	
	Square_2048 res(action, val);
	return res;
}
