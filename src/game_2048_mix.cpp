#include "game_2048_mix.hpp"

Game_2048_Mix::Game_2048_Mix(int height, int base) :
	Game_2048(height) ,
	Game_2048_Num(height,base),
	Game_2048_Neg(height),
	Game_2048_Mult(height),
	Game_2048_Dest(height)
{
	
}

Square_2048 Game_2048_Mix::random_square() const
{
	Square_2048_action action;
        unsigned long long val;
        
        int random_action = rand() % 7;

	/* on réduit la probabilité des cases destroy pour éviter 
	   qu'elles tombent trop souvent */
	if (random_action == 0) {
		action = Square_2048_action::destroy;
		val = 0;
	}
	
        else if (random_action <= 2) {
                action = Square_2048_action::mult;
                val = 2;
        }
        else {
		if (random_action <= 4)
			action = Square_2048_action::neg;

		else
			action = Square_2048_action::none;
		
                val = random_value();
        }

        return Square_2048(action, val);

}
