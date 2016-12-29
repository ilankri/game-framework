#include "game_2048_mix.hpp"

Game_2048_Mix::Game_2048_Mix(int height, int base) :
	Game_2048(height) ,
	Game_2048_Num(height,base),
	Game_2048_Neg(height)
{
	
}
