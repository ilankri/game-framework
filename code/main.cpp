#include "Jeu.hpp"
#include "Taquin.hpp"
/* #include "Sokoban.hpp" */
/* #include "jeu2048.hpp" */

int main()
{
	const int l = 10;
	const int h = 10;
	Jeu<CaseSok>* j = new Sokoban<CaseSok>(l, h);
	j->jouerHumain();
	delete j;
	return 0;
}
