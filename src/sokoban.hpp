#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include "game.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

enum class CaseSok {empty, wall, pers, crate,
		target, crate_target, pers_target};

ostream& operator<<(ostream&, CaseSok const&);

class Sokoban : public Game<CaseSok> {
public:
	Sokoban(int h, int w, int nb_crates = -1);

	virtual ~Sokoban();

private:
	static const int min_height;

	static const int min_width;
	
	int nb_crates;

	int pos_h;

	int pos_w;

	int i_top_left;

	int j_top_left;

	int i_top_right;

	int j_top_right;

	int i_bottom_left;

	int j_bottom_left;

	int i_bottom_right;

	int j_bottom_right;

	virtual void print_board(ostream& o = cout) const;

	virtual void init();

	virtual void set_walls();

	virtual void setExternalWalls();

	virtual void setInternalWalls();

	virtual void set_targets_crates();

	virtual bool freeZone(int h_c, int l_c) const;

	virtual bool outsideOfWalls(int h_c, int l_c) const;

	virtual void move(Direction s);

	virtual void set_pers();

	virtual bool is_over() const;

	virtual bool is_stuck() const;
};



#endif	/* not SOKOBAN_HPP */
