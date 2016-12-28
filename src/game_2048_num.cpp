#include "game_2048_num.hpp"

Game_2048_Num::Game_2048_Num(int height, int width) :
	Game_2048(height, width)
{
	
}

int Game_2048_Num::random_value()
{
	return 2 + rand() % 6;
}
