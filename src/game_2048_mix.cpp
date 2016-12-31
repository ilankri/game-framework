#include "game_2048_mix.hpp"

Game_2048_Mix::Game_2048_Mix(int height) :
	Game_2048(height) ,
	Game_2048_Num2(height),
	Game_2048_Neg(height),
	Game_2048_Mult(height),
	Game_2048_Dest(height)
{

}

Square_2048 Game_2048_Mix::random_square() const
{
	Action_2048 action;
	unsigned long long val;

	int random_action = rand() % 7;

	/* on réduit la probabilité des cases destroy pour éviter
	   qu'elles tombent trop souvent */
	if (random_action == 0) {
		action = Action_2048::destroy;
		val = 0;
	}

	else if (random_action <= 2) {
		action = Action_2048::mult;
		val = 2;
	}
	else {
		if (random_action <= 4)
			action = Action_2048::neg;

		else
			action = Action_2048::none;

		val = random_value();
	}

	return Square_2048(action, val);

}
