#include "game_2048_neg.hpp"

Game_2048_Neg::Game_2048_Neg(int height) :
	Game_2048(height)
{

}


Square_2048 Game_2048_Neg::random_square() const
{
	unsigned long long val = random_value();
	Action_2048 action;
	int sgn= rand() % 2;
	if (sgn)
		action = Action_2048::none;
	else action = Action_2048::neg;

	Square_2048 res(action, val);
	return res;
}
