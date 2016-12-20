#include "game.hpp"
#include "taquin.hpp"
#include "sokoban.hpp"
/* #include "jeu2048.hpp" */

int main()
{
	const int l = 10;
	const int h = 10;
	Game<CaseSok>* j = new Sokoban(l, h);
	j->jouerHumain();
	delete j;
	return 0;
}
