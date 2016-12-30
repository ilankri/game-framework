#include "game_2048_num.hpp"

Game_2048_Num::Game_2048_Num(int height, int base) :
	Game_2048(height), base(max(2,base))
{
	
}

unsigned long long Game_2048_Num::random_value() const
{
	return (1 + rand() % 2) * base;
}
