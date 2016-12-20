#ifndef TAQUIN
#define TAQUIN

#include "game.hpp"
#include <cstdlib>
#include <ctime>


class Taquin : public Game<int> {
public:
	Taquin(int l, int h);

	virtual ~Taquin();

private:
	static const int caseVide = 0;

	// coordonnées de la case vide
	int pos_vide_l;

	int pos_vide_h;

	virtual void init();

	virtual bool is_over() const;

	virtual void move(Direction s);

	void remplir();

	void melanger();
};

#endif
