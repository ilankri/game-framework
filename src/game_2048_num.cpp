#include "game_2048_num.hpp"

Game_2048_Num::Game_2048_Num(int height, long base) :
	Game_2048(height), base(base)
{
	
}

long Game_2048_Num::random_value()
{
	return (1 + rand() % 2) * base;
}
