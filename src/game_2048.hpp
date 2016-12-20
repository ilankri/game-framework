#ifndef GAME_2048_HPP
#define GAME_2048_HPP

#include "game.hpp"
#include "square_2048.hpp"
/* #include <cstdlib> */
/* #include <ctime> */
/* #include <iostream> */

/* using namespace std; */

class Game_2048 : public Jeu<Square_2048> {
public:
	Game_2048(int l, int h);

	virtual ~Game_2048() {}

/* protected: */
/*	virtual void initialiser(); */

	/* virtual bool jeuTermine() const; */

	/* virtual void deplacer(Sens sens); */
};

#endif /* not GAME_2048_HPP */
