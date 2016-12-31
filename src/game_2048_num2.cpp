#include "game_2048_num2.hpp"

Game_2048_Num2::Game_2048_Num2(int height) :
	Game_2048(height)
{
	
}

unsigned long long Game_2048_Num2::random_value() const
{
	int mult = 1 + rand() % 2;
	int rdm = rand() % 4;
	int base;

	switch(rdm) {
	case 1:
		base = 3;
		break;
	case 2:
		base = 5;
		break;
	case 3:
		base = 7;
		break;
	default:
		base = 2;
		break;
	}
		
	return mult * base;
}
