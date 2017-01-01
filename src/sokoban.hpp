#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include "game.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

enum class Square_Sokoban {empty, wall, pers, crate,
		target, crate_target, pers_target};

ostream& operator<<(ostream&, Square_Sokoban const&);

class Sokoban : public Game<Square_Sokoban> {
public:
	Sokoban(int h, int w, int nb_crates = -1);

	virtual ~Sokoban();

protected:

	/* minimal dimensions of board */
	static const int min_height;

	static const int min_width;

	/* number of crates */
	int nb_crates;

	/* current position of character */
	int pos_h;

	int pos_w;

	/* coordinates of top left corner of internal wall */
	int i_top_left;

	int j_top_left;

	/* coordinates of top right corner of internall wall */
	int i_top_right;

	int j_top_right;

	/* coordinates of bottom left corner of internal wall */
	int i_bottom_left;

	int j_bottom_left;

	/* coordinates of bottom right corner of internal wall */
	int i_bottom_right;

	int j_bottom_right;

	virtual void print_board(ostream& o = cout) const;

	virtual void init();

	/* These functions set walls on the board */
	virtual void set_walls();

	virtual void setExternalWalls();

	virtual void setInternalWalls();

	/* Set targets and crates in the board */
	virtual void set_targets_crates();

	/* check if the square with coordinates (h_c, l_c) is empty
	   and doesn't have any walls around it */
	virtual bool freeZone(int h_c, int l_c) const;

	/* check if the square with coordinates (h_c, l_c) is located
	   outside external wals */
	virtual bool outsideOfWalls(int h_c, int l_c) const;

	virtual void move(Direction s);

	/* set the character on the board at the beginning of the game */
	virtual void set_pers();

	virtual bool is_over() const;

	/* the game can be stuck if a crate can no longer be moved */
	virtual bool is_stuck() const;
};



#endif	/* not SOKOBAN_HPP */
