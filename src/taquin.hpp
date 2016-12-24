#ifndef TAQUIN_HPP
#define TAQUIN_HPP

#include "game.hpp"
#include <cstdlib>
#include <ctime>


class Taquin : public Game<int> {
public:
	Taquin(int h, int w);

	virtual ~Taquin();

private:
	static const int emptyCase = 0;

	// coordonnées de la case vide
	int pos_empty_w;

	int pos_empty_h;

	virtual void init();

	virtual bool is_over() const;

	virtual void move(Direction s);

	void fill();

	void mix();
};

#endif	/* not TAQUIN_HPP */
