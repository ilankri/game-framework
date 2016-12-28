#include "game.hpp"
#include "taquin.hpp"
#include "sokoban.hpp"
#include "game_2048.hpp"
#include "game_2048_num.hpp"
#include "game_2048_neg.hpp"

/* #include "jeu2048.hpp" */

int main()
{
	const int l = 4;
	const int h = 4;
	Game<Square_2048>* j = new Game_2048_Num(l, h);
	j->play();
	delete j;
	return 0;
}
