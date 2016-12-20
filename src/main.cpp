#include "game.hpp"
#include "taquin.hpp"
#include "sokoban.hpp"
/* #include "jeu2048.hpp" */

int main()
{
	const int l = 4;
	const int h = 4;
	Game<int>* j = new Taquin(l, h);
	j->play();
	delete j;
	return 0;
}
