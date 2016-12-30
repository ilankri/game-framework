#include "game_2048_mult.hpp"

Game_2048_Mult::Game_2048_Mult(int height) :
	Game_2048(height)
{

}

Square_2048 Game_2048_Mult::random_square() const
{
	Action_2048 action;
	unsigned long long val;

	int random_action = rand() % 2;

	if (random_action == 0) {
		action = Action_2048::mult;
		val = 2;
	}
	else {
		action = Action_2048::none;
		val = random_value();
	}

	return Square_2048(action, val);
}
