#include "game_2048_mult.hpp"

Game_2048_Mult::Game_2048_Mult(int height) :
	Game_2048(height)
{
	
}

Square_2048 Game_2048_Mult::random_square() const
{
	Square_2048_action action;
	unsigned long long val;
	
	int random_action = rand() % 2;

	if (random_action == 0) {
		action = Square_2048_action::mult;
		val = 2;
	}
	else {
		action = Square_2048_action::none;
		val = random_value();
	}

	return Square_2048(action, val);
}

