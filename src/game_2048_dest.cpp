#include "game_2048_dest.hpp"

Game_2048_Dest::Game_2048_Dest(int height) :
	Game_2048(height)
{

}


Square_2048 Game_2048_Dest::random_square() const
{
	Action_2048 action;
	unsigned long long val;

	int random_action = rand() % 4;

	if (random_action == 0) {
		action = Action_2048::destroy;
		val = 0;
	}
	else {
		action = Action_2048::none;
		val = random_value();
	}

	return Square_2048(action, val);
}
