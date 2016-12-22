#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include "game.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

enum class CaseSok {vide, mur, pers, caisse, but, caisse_but, pers_but};

ostream& operator<<(ostream&, CaseSok const&);

class Sokoban : public Game<CaseSok> {
public:
	Sokoban(int h, int w, int nb_caisses = -1);

	virtual ~Sokoban();

private:
	int nb_caisses;

	int pos_h;

	int pos_l;

	int i_haut_gauche;

	int j_haut_gauche;

	int i_haut_droite;

	int j_haut_droite;

	int i_bas_gauche;

	int j_bas_gauche;

	int i_bas_droite;

	int j_bas_droite;

	/* virtual void print(ostream& o = cout) const; */

	virtual void init();

	virtual void placer_murs();

	virtual void placerMursExternes();

	virtual void placerMursInternes();

	virtual void placer_buts_caisses();

	virtual bool zoneLibre(int h_c, int l_c);

	virtual bool horsZoneMurs(int h_c, int l_c);

	virtual void move(Direction s);

	virtual void placer_pers();

	virtual bool is_over() const;

	virtual bool is_stuck() const;
};

#endif	/* not SOKOBAN_HPP */
